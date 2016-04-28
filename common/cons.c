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

#include <boot.h>
#include <io.h>

#define THR	0x00
#define RHR	0x00
#define DLL	0x00
#define IER	0x04
#define DLH	0x04
#define FCR	0x08
#define IIR	0x08
#define LCR	0x0C
#define MCR	0x10
#define LSR	0x14
#define MSR	0x18
#define SCR	0x1C
#define MDR1	0x20

#define WR(val, addr)	writeb(val, console + addr)
#define RD(addr)	readb(console + addr)

#define BAUDRATE	115200
#define SERIAL_CLK_HZ	48000000

extern unsigned console;

void
cons_init(void)
{
	unsigned divisor = SERIAL_CLK_HZ / 16 / BAUDRATE;

	WR(0x00, IER);
	WR(0x07, MDR1); /* disable */
	WR(0x83, LCR);  /* 8N1 + configure mode A */
	WR(divisor & 0xFF, DLL);
	WR(divisor >> 8, DLH);
	WR(0x03, LCR);  /* 8N1 */
	WR(0x03, MCR);  /* DTR, RTS */
	WR(0x07, FCR);  /* reset and enable FIFO */
	WR(0x00, MDR1); /* uart 16x mode */
}

static inline void
putc(char c)
{
	while (!(RD(LSR) & 0x20))
		;
	WR(c, THR);
}

int
putchar(char c)
{
	if (c == '\n')
		putc('\r');
	putc(c);
	return (1);
}

void
puts(const char *s)
{
	while (*s)
		putchar(*s++);
}

char
getc(void)
{
	while (!(RD(LSR) & 0x01))
		;
	return (RD(RHR));
}

int
tstc(void)
{
	return ((RD(LSR) & 0x01) != 0);
}
