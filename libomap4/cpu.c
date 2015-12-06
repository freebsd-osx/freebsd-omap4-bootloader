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

#include <boot1.h>
#include <io.h>
#include <omap4/hw.h>

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

uint32_t
warm_reset(void)
{
	return (readl(PRM_RSTST) & PRM_RSTST_WARM_RESET_MASK);
}

void
control_io_interface()
{
	uint32_t lpddr2io;
	uint32_t rev;

	rev = get_omap_rev();
	if (rev == OMAP4430_ES1_0)
		lpddr2io = 0x1c1c1c1c;
	else if (rev == OMAP4430_ES2_0)
		lpddr2io = 0x9e9e9e9e;
	else
		lpddr2io = 0x7c7c7c7c;

	writel(lpddr2io, CONTROL_LPDDR2IO1_0);
	writel(lpddr2io, CONTROL_LPDDR2IO1_1);
	writel(lpddr2io & ~(3 << 17), CONTROL_LPDDR2IO1_2);
	writel(0xa0888c0f, CONTROL_LPDDR2IO1_3);

	writel(lpddr2io, CONTROL_LPDDR2IO2_0);
	writel(lpddr2io, CONTROL_LPDDR2IO2_1);
	writel(lpddr2io & ~(3 << 17), CONTROL_LPDDR2IO2_2);
	writel(0xa0888c0f, CONTROL_LPDDR2IO2_3);

	if (!(readl(CONTROL_STD_FUSE_OPP_BGAP) & 0xffff)) {
		writel(0x0401040f, CONTROL_LDOSRAM_IVA_VOLTAGE_CTRL);
		writel(0x0401040f, CONTROL_LDOSRAM_MPU_VOLTAGE_CTRL);
		writel(0x0401040f, CONTROL_LDOSRAM_CORE_VOLTAGE_CTRL);
	}

	if (!readl(CONTROL_EFUSE_1))
		writel(0x1c4d0110, CONTROL_EFUSE_1);

	if ((rev <OMAP4460_ES1_0) || !readl(CONTROL_EFUSE_2))
		writel(0x99084000, CONTROL_EFUSE_2);
}
