/*-
 * Copyright (c) 2015
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
#include <sys/gpt.h>

#include <machine/elf.h>

#include <boot1.h>

#include "drv.h"
#include "util.h"
#include "gpt.h"

#define PATH_LOADER	"/boot/ubldr"

extern char bootprog_name[];
extern char bootprog_rev[];
extern char bootprog_date[];
extern char bootprog_maker[];

static const uuid_t freebsd_ufs_uuid = GPT_ENT_TYPE_FREEBSD_UFS;
static struct dsk dsk;
static char kname[1024];

static int dskread(void *, daddr_t, unsigned);

#include "ufsread.c"

static struct dmadat _dmadat;

static void
load(void)
{
	Elf32_Ehdr eh;
	ufs_ino_t ino;

	if ((ino = lookup(kname)) == 0) {
		printf("File %s not found\n", kname);
		return;
	}
	if (fsread(ino, &eh, sizeof(eh)) != sizeof(eh)) {
		printf("Can't read elf header\n");
		return;
	}
	if (!IS_ELF(eh)) {
		printf("Not an ELF file\n");
		return;
	}
	printf("success\n");
}

static int
gptinit(void)
{
	if (gptread(&freebsd_ufs_uuid, &dsk, dmadat->secbuf) == -1) {
		printf("%s: unable to load GPT\n", BOOTPROG);
		return (-1);
	}
	if (gptfind(&freebsd_ufs_uuid, &dsk, dsk.part) == -1) {
		printf("%s: no UFS partition was found\n", BOOTPROG);
		return (-1);
	}
	dsk_meta = 0;
	return (0);
}

static int
dskread(void *buf, daddr_t lba, unsigned nblk)
{

	return drvread(&dsk, buf, lba + dsk.start, nblk);
}

int
main(void)
{
	printf("%s Revision %s\n", bootprog_name, bootprog_rev);
	printf("(%s, %s)\n", bootprog_maker, bootprog_date);

	dsk.part = -1;
	dsk.start = 0;

	dmadat = &_dmadat;

	if (gptinit())
		return (-1);
	if (*kname == '\0')
		strcpy(kname, PATH_LOADER);

	load();

	return (0);
}
