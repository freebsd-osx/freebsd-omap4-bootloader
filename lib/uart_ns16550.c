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

#include <ns16550.h>

#define MCR	(MCR_DTR | MCR_RTS)			/* RTS/DTR */
#define FCR	(FCR_FIFO_EN | FCR_RXSR | FCR_TXSR)	/* Clear & enable FIFOs */

void
ns16550_init(ns16550_t uart, int baud_divisor)
{
	uart->ier = 0x00;	/* disable all interrupts */
	uart->mdr1 = 0x7;	/* mode select reset TL16C750*/
	uart->lcr = LCR_BKSE | LCR_8N1;
	uart->dll = baud_divisor & 0xff;
	uart->dlm = (baud_divisor >> 8) & 0xff;
	uart->lcr = LCR_8N1;
	uart->mcr = MCR;
	uart->fcr = FCR;
	uart->mdr1 = 0;	/* select uart mode */
}

void
ns16550_reinit(ns16550_t uart, int baud_divisor)
{
	uart->ier = 0x00;
	uart->lcr = LCR_BKSE;
	uart->dll = baud_divisor & 0xff;
	uart->dlm = (baud_divisor >> 8) & 0xff;
	uart->lcr = LCR_8N1;
	uart->mcr = MCR;
	uart->fcr = FCR;
}

void
ns16550_putc(ns16550_t uart, char c)
{
	while ((uart->lsr & LSR_THRE) == 0);
	uart->thr = c;
}

char
ns16550_getc(ns16550_t uart)
{
	while ((uart->lsr & LSR_DR) == 0);
	return (uart->rbr);
}

int
ns16550_tstc(ns16550_t uart)
{
	return ((uart->lsr & LSR_DR) != 0);
}
