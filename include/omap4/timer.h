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

#ifndef _OMAP4_TIMER_H_
#define _OMAP4_TIMER_H_

#define	CONFIG_SYS_HZ	1000

#define V_OSCK		19200000	/* Clock output from T2 */
#define V_SCLK		V_OSCK

#define TCLR_ST		(0x1 << 0)
#define TCLR_AR		(0x1 << 1)
#define TCLR_PRE	(0x1 << 5)

#define CONFIG_SYS_PTV		2	/* Divisor: 2^(PTV+1) => 8 */

struct gptimer {
	uint32_t tidr;		/* 0x00 r */
	uint8_t res[0xc];
	uint32_t tiocp_cfg;	/* 0x10 rw */
	uint32_t tistat;	/* 0x14 r */
	uint32_t tisr;		/* 0x18 rw */
	uint32_t tier;		/* 0x1c rw */
	uint32_t twer;		/* 0x20 rw */
	uint32_t tclr;		/* 0x24 rw */
	uint32_t tcrr;		/* 0x28 rw */
	uint32_t tldr;		/* 0x2c rw */
	uint32_t ttgr;		/* 0x30 rw */
	uint32_t twpc;		/* 0x34 r */
	uint32_t tmar;		/* 0x38 rw */
	uint32_t tcar1;		/* 0x3c r */
	uint32_t tcicr;		/* 0x40 rw */
	uint32_t tcar2;		/* 0x44 r */
};

#endif /* _OMAP4_TIMER_H_ */
