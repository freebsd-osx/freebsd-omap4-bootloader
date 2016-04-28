/*-
 * Copyright (c) 2016
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/types.h>

#include <boot.h>

#include "util.h"
#include "cons.h"
#include "crc32.h"
#include "syscall.h"
#include "api_public.h"

extern int stack_base;

typedef	int (*cfp_t)(va_list argp);
static int calls_no;

void
set_mr(struct sys_info *si, unsigned long start, unsigned long size,
    int flags)
{
	int i;

	if (!si->mr || !size || (flags == 0))
		return;

	/* find free slot */
	for (i = 0; i < si->mr_no; i++)
		if (si->mr[i].flags == 0) {
			/* insert new mem region */
			si->mr[i].start = start;
			si->mr[i].size = size;
			si->mr[i].flags = flags;
			return;
		}
}

static int
get_sys_info(struct sys_info *si)
{
	int i;

	for (i = 0; i < get_sdram_banks(); i++)
		set_mr(si, get_sdram_start(), get_sdram_size(), MR_ATTR_DRAM);

	return (1);
}

static int
syscall_getc(va_list ap)
{
	int *c;

	if ((c = (int *)va_arg(ap, u_int32_t)) == NULL)
		return (API_EINVAL);

	*c = getc();
	return (0);
}

static int
syscall_tstc(va_list ap)
{
	int *t;

	if ((t = (int *)va_arg(ap, u_int32_t)) == NULL)
		return (API_EINVAL);

	*t = tstc();
	return (0);
}

static int
syscall_putc(va_list ap)
{
	char *c;

	if ((c = (char *)va_arg(ap, u_int32_t)) == NULL)
		return (API_EINVAL);

	putchar(*c);
	return (0);
}


static int
syscall_puts(va_list ap)
{
	char *s;

	if ((s = (char *)va_arg(ap, u_int32_t)) == NULL)
		return (API_EINVAL);

	puts(s);
	return (0);
}

static int
syscall_reset(va_list ap)
{
	reset_cpu();

	/* not reached */
	return (0);
}

static int
syscall_get_sys_info(va_list ap)
{
	struct sys_info *si;

	si = (struct sys_info *)va_arg(ap, u_int32_t);
	if (si == NULL)
		return (API_ENOMEM);

	return ((get_sys_info(si)) ? 0 : API_ENODEV);
}

static int
syscall_udelay(va_list ap)
{
	unsigned long *d;

	if ((d = (unsigned long *)va_arg(ap, u_int32_t)) == NULL)
		return (API_EINVAL);

	udelay(*d);
	return (0);
}

static int
syscall_get_timer(va_list ap)
{
	unsigned long *base, *cur;

	cur = (unsigned long *)va_arg(ap, u_int32_t);
	if (cur == NULL)
		return (API_EINVAL);

	base = (unsigned long *)va_arg(ap, u_int32_t);
	if (base == NULL)
		return (API_EINVAL);

	*cur = get_timer(*base);
	return (0);
}

static int
syscall_dev_enum(va_list ap)
{
	struct device_info *di;
	static int count = 0;

	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return (API_EINVAL);

	if (count != 0) {
		di->cookie = NULL;
		return (API_ENODEV);
	}

	di->cookie = (void *)get_storage();
	di->type = DEV_TYP_STOR | DT_STOR_MMC;
	di->di_stor.block_count = get_storage()->size;
	di->di_stor.block_size = 512;

	++count;
	return (0);
}

static int
syscall_dev_open(va_list ap)
{
	struct device_info *di;
	int err = 0;

	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return (API_EINVAL);

	if (di->state == DEV_STA_OPEN)
		return (API_EBUSY);

	if (di->cookie == NULL)
		return (API_ENODEV);

	if (di->type & DEV_TYP_STOR)
		err = 0;
	else
		err = (API_ENODEV);

	if (!err)
		di->state = DEV_STA_OPEN;

	return (err);
}

static int
syscall_dev_close(va_list ap)
{
	struct device_info *di;
	int err = 0;

	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return (API_EINVAL);

	if (di->state == DEV_STA_CLOSED)
		return (0);

	if (di->cookie == NULL)
		return (API_ENODEV);

	if (di->type & DEV_TYP_STOR)
		err = 0;
	else
		err = (API_ENODEV);

	if (!err)
		di->state = DEV_STA_CLOSED;

	return err;
}

static int
syscall_dev_read(va_list ap)
{
	struct device_info *di;
	void *buf;
	lbasize_t *len_stor, *act_len_stor;
	lbastart_t *start;

	di = (struct device_info *)va_arg(ap, u_int32_t);
	if (di == NULL)
		return (API_EINVAL);

	if (di->cookie == NULL)
		return (API_ENODEV);

	buf = (void *)va_arg(ap, u_int32_t);
	if (buf == NULL)
		return (API_EINVAL);

	if (di->type & DEV_TYP_STOR) {
		len_stor = (lbasize_t *)va_arg(ap, u_int32_t);
		if (!len_stor)
			return (API_EINVAL);
		if (*len_stor <= 0)
			return (API_EINVAL);

		start = (lbastart_t *)va_arg(ap, u_int32_t);

		act_len_stor = (lbasize_t *)va_arg(ap, u_int32_t);
		if (!act_len_stor)
			return (API_EINVAL);

		*act_len_stor = ((struct storage *)di->cookie)->read(buf, *start, *len_stor);
	} else
		return (API_ENODEV);

	return (0);
}

static cfp_t calls_table[API_MAXCALL] = { NULL, };

int
syscall(int call, int *retval, ...)
{
	va_list	ap;
	int rv;

	if (call < 0 || call >= calls_no) {
		debug("invalid call #%d\n", call);
		return (0);
	}

	if (calls_table[call] == NULL) {
		debug("syscall #%d does not have a handler\n", call);
		return (0);
	}

	va_start(ap, retval);
	rv = calls_table[call](ap);
	if (retval != NULL)
		*retval = rv;

	return (1);
}

void
syscall_init(void)
{
	struct api_signature *sig = NULL;

	calls_table[API_RSVD] = NULL;
	calls_table[API_GETC] = &syscall_getc;
	calls_table[API_PUTC] = &syscall_putc;
	calls_table[API_TSTC] = &syscall_tstc;
	calls_table[API_PUTS] = &syscall_puts;
	calls_table[API_RESET] = &syscall_reset;
	calls_table[API_GET_SYS_INFO] = &syscall_get_sys_info;
	calls_table[API_UDELAY] = &syscall_udelay;
	calls_table[API_GET_TIMER] = &syscall_get_timer;
	calls_table[API_DEV_ENUM] = &syscall_dev_enum;
	calls_table[API_DEV_OPEN] = &syscall_dev_open;
	calls_table[API_DEV_CLOSE] = &syscall_dev_close;
	calls_table[API_DEV_READ] = &syscall_dev_read;
	calls_table[API_DEV_WRITE] = NULL;
	calls_table[API_ENV_ENUM] = NULL;
	calls_table[API_ENV_GET] = NULL;
	calls_table[API_ENV_SET] = NULL;
	calls_no = API_MAXCALL;

	sig = (struct api_signature *)(stack_base + 0x100000);
	debug("syscall sig @ 0x%x\n", sig);

	memcpy(sig->magic, API_SIG_MAGIC, 8);
	sig->version = API_SIG_VERSION;
	sig->syscall = &syscall;
	sig->checksum = 0;
	sig->checksum = crc32((void *)sig, sizeof(struct api_signature));
	debug("syscall entry: 0x%x\n", sig->syscall);
}
