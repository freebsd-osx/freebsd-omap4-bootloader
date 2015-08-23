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


#ifndef _NS16550_H_
#define _NS16550_H_

#include <config.h>

#if (NS16550_REG_SIZE == 1)
struct ns16550 {
	unsigned char rbr;		/* 0 */
	unsigned char ier;		/* 1 */
	unsigned char fcr;		/* 2 */
	unsigned char lcr;		/* 3 */
	unsigned char mcr;		/* 4 */
	unsigned char lsr;		/* 5 */
	unsigned char msr;		/* 6 */
	unsigned char scr;		/* 7 */
} __attribute__ ((packed));
#elif (NS16550_REG_SIZE == 2)
struct ns16550 {
	unsigned short rbr;		/* 0 */
	unsigned short ier;		/* 1 */
	unsigned short fcr;		/* 2 */
	unsigned short lcr;		/* 3 */
	unsigned short mcr;		/* 4 */
	unsigned short lsr;		/* 5 */
	unsigned short msr;		/* 6 */
	unsigned short scr;		/* 7 */
} __attribute__ ((packed));
#elif (NS16550_REG_SIZE == 4)
struct ns16550 {
	unsigned long rbr;		/* 0 */
	unsigned long ier;		/* 1 */
	unsigned long fcr;		/* 2 */
	unsigned long lcr;		/* 3 */
	unsigned long mcr;		/* 4 */
	unsigned long lsr;		/* 5 */
	unsigned long msr;		/* 6 */
	unsigned long scr;		/* 7 */
} __attribute__ ((packed));
#elif (NS16550_REG_SIZE == -4)
struct ns16550 {
	unsigned char rbr;		/* 0 */
	int pad1:24;
	unsigned char ier;		/* 1 */
	int pad2:24;
	unsigned char fcr;		/* 2 */
	int pad3:24;
	unsigned char lcr;		/* 3 */
	int pad4:24;
	unsigned char mcr;		/* 4 */
	int pad5:24;
	unsigned char lsr;		/* 5 */
	int pad6:24;
	unsigned char msr;		/* 6 */
	int pad7:24;
	unsigned char scr;		/* 7 */
	int pad8:24;
	unsigned char mdr1;		/* mode select reset TL16C750*/
} __attribute__ ((packed));
#else
#error "Please define NS16550 registers size."
#endif

#define thr rbr
#define iir fcr
#define dll rbr
#define dlm ier

typedef volatile struct ns16550 *ns16550_t;

#define FCR_FIFO_EN     0x01		/* FIFO enable */
#define FCR_RXSR        0x02		/* Receiver soft reset */
#define FCR_TXSR        0x04		/* Transmitter soft reset */

#define MCR_DTR         0x01
#define MCR_RTS         0x02
#define MCR_DMA_EN      0x04
#define MCR_TX_DFR      0x08

#define LCR_WLS_MSK	0x03		/* character length slect mask */
#define LCR_WLS_5	0x00		/* 5 bit character length */
#define LCR_WLS_6	0x01		/* 6 bit character length */
#define LCR_WLS_7	0x02		/* 7 bit character length */
#define LCR_WLS_8	0x03		/* 8 bit character length */
#define LCR_STB		0x04		/* Number of stop Bits, off = 1, on = 1.5 or 2) */
#define LCR_PEN		0x08		/* Parity eneble */
#define LCR_EPS		0x10		/* Even Parity Select */
#define LCR_STKP	0x20		/* Stick Parity */
#define LCR_SBRK	0x40		/* Set Break */
#define LCR_BKSE	0x80		/* Bank select enable */

#define LSR_DR		0x01		/* Data ready */
#define LSR_OE		0x02		/* Overrun */
#define LSR_PE		0x04		/* Parity error */
#define LSR_FE		0x08		/* Framing error */
#define LSR_BI		0x10		/* Break */
#define LSR_THRE	0x20		/* Xmit holding register empty */
#define LSR_TEMT	0x40		/* Xmitter empty */
#define LSR_ERR		0x80		/* Error */

#define LCR_8N1		0x03		/* 8 bits, no parity, 1 stop-bit */

void ns16550_init(ns16550_t uart, int baud_divisor);
void ns16550_reinit(ns16550_t uart, int baud_divisor);
void ns16550_putc(ns16550_t uart, char c);
char ns16550_getc(ns16550_t uart);
int ns16550_tstc(ns16550_t uart);

#endif
