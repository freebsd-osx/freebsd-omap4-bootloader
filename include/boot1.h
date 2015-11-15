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

#ifndef _BOOT_H_
#define _BOOT_H_

#include <sys/types.h>
#include <machine/stdarg.h>

void mux_init(void);
void clock_init(void);

void serial_init(void);
int serial_putc(char c);

int printf(const char *fmt, ...);

void sdelay(unsigned long loops);
uint32_t wait_on(uint32_t mask, uint32_t value, uint32_t addr);

int get_omap_rev(void);

#define OMAP_4430_ES1_0		0x0B85202F
#define OMAP_4430_ES2_0		0x1B85202F
#define OMAP_4430_ES2_1		0x3B95C02F
#define OMAP_4430_ES2_2		0x4B95C02F
#define OMAP_4430_ES2_3		0x6B95C02F
#define OMAP_4460_ES1_0		0x0B94E02F
#define OMAP_4460_ES1_1		0x2B94E02F
#define OMAP_4470_ES1_0		0x0B97502F
#define OMAP_REV_INVALID	0x00000000

#endif /* !_BOOT_H_ */
