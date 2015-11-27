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

#ifndef _IO_H_
#define _IO_H_

#define readb(a)	(*((volatile unsigned char *) (a)))
#define writeb(v, a)	(*((volatile unsigned char *) (a)) = (v))

#define readw(a)	(*((volatile unsigned short *) (a)))
#define writew(v, a)	(*((volatile unsigned short *) (a)) = (v))

#define readl(a)	(*((volatile unsigned int *) (a)))
#define writel(v, a)	(*((volatile unsigned int *) (a)) = (v))

#define clrbits(addr, clear) \
	writel((readl(addr) & ~(clear)), (addr))

#define setbits(addr, set) \
	writel((readl(addr) | (set)), (addr))

#define clrsetbits(addr, clear, set) \
	writel((readl(addr) & ~(clear)) | (set), (addr))

int		gpio_direction_input(unsigned gpio);
int		gpio_set_value(unsigned gpio, int enable);
unsigned	gpio_get_value(unsigned gpio);

#endif /* !_IO_H_ */
