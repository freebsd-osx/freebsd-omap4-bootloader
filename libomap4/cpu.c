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

#include <sys/types.h>

#include <boot.h>
#include <io.h>

#include <omap4/hw.h>

#define LOOP	2000
uint32_t
poll(uint32_t mask, uint32_t value, uint32_t addr)
{
	uint32_t i = 0, val;
	while (1) {
		++i;
		val = readl(addr) & mask;
		if (val == value)
			return (1);
		if (i == LOOP)
			return (0);
	}
	return (0);
}

void
sdelay(u_long loops)
{
	__asm__ volatile ("1:\n" "subs %0, %1, #1\n"
			  "bne 1b":"=r" (loops):"0"(loops));
}

uint32_t
get_omap_rev(void)
{
	uint32_t id;
	uint32_t rev;

	id = readl(CONTROL_ID_CODE);
	switch (id) {
	case 0x0B85202F:
		rev = OMAP4430_ES1_0;
		break;
	case 0x1B85202F:
		rev = OMAP4430_ES2_0;
		break;
	case 0x3B95C02F:
		rev = OMAP4430_ES2_1;
		break;
	case 0x4B95C02F:
		rev = OMAP4430_ES2_2;
		break;
	case 0x6B95C02F:
		rev = OMAP4430_ES2_3;
		break;
	case 0x0B94E02F:
		rev = OMAP4460_ES1_0;
		break;
	case 0x2B94E02F:
		rev = OMAP4460_ES1_1;
		break;
	case 0x0B97502F:
		rev = OMAP4470_ES1_0;
		break;
	default:
		rev = REV_INVALID;
		break;
	}
	return (rev);
}


void
reset_cpu(void)
{
	writel(PRM_RSTCTRL_RESET, PRM_RSTCTRL);
}

uint32_t
warm_reset(void)
{
	return (readl(PRM_RSTST) & PRM_RSTST_WARM_RESET_MASK);
}

uint32_t
get_sdram_banks(void)
{
	return 1;
}

uint32_t
get_sdram_start(void)
{
	return 0x80000000;
}

uint32_t
get_sdram_size(void)
{
	uint32_t section, size, addr, total_size = 0;
	uint32_t sdrc_addrspc;
	uint32_t sdrc_map;
	uint32_t i;
	for (i = 0; i < 4; i++) {
		section = readl(DMM_LISA_MAP + i * 4);
		addr = section & (0xff << 24);
		sdrc_addrspc = (section & (3 << 16)) >> 16;
		sdrc_map = (section & (3 << 8)) >> 8;

		if (0 == sdrc_map)
			continue;

		if (0 != sdrc_addrspc)
			continue;

		/* update SDRAM size */
		size = (section & (7 << 20)) >> 20;
		size = 1 << size;
		size *= 0x01000000; /* 16M */
		total_size += size;

	}
	return total_size;
}

void
watchdog_init(void)
{
	writel(WD_UNLOCK1, WD2_BASE + WSPR);
	while (readl(WD2_BASE + WWPS))
		;
	writel(WD_UNLOCK2, WD2_BASE + WSPR);
}
