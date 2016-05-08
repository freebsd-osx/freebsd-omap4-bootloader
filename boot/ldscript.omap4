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

MEMORY { .sram : ORIGIN = 0x40300000, LENGTH = (0x4030C000 - 0x40300000) }
MEMORY { .sdram : ORIGIN = 0x80a00000, LENGTH = 0x80000 }

ENTRY(_start)
SECTIONS {
	.text : { *(.text*) } >.sram

	. = ALIGN(4);
	.got : { *(.got*) } >.sram

	. = ALIGN(4);
	.rodata : { *(.rodata*) } >.sram

	. = ALIGN(4);
	.data : { *(.data*) } >.sram

	.bss :
	{
		. = ALIGN(4);
		PROVIDE (__bss_start = .);
		*(.bss*)
		. = ALIGN(4);
		PROVIDE (__bss_end = .);
	} >.sdram

	/DISCARD/ : { *(.ARM.exidx*) }
}
