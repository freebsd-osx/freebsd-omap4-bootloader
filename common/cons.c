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

#include <common.h>
#include <ns16550.h>
//#include <omap4/omap4.h>

#define NS16550_CLK	(48000000)
#define BAUDRATE	115200

static ns16550_t console = (ns16550_t)0;

static int
calc_divisor(void)
{
	return (NS16550_CLK / 16 / BAUDRATE);
}

void
serial_init(void)
{
	int clock_divisor = calc_divisor();

	console = (ns16550_t)get_serial_console();
	ns16550_init(console, clock_divisor);

	return;
}

int
putchar(const char c)
{
	if (c == '\n')
		ns16550_putc(console, '\r');

	ns16550_putc(console, c);

	return (1);
}

void
puts(const char *s)
{
	while (*s) {
		putchar(*s++);
	}
}


int
getchar(void)
{
	return ns16550_getc(console);
}

int
tstc(void)
{
	return ns16550_tstc(console);
}

void
setbrg(void)
{
	int clock_divisor;

	clock_divisor = calc_divisor();
	ns16550_reinit(console, clock_divisor);
}
