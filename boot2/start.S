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

#include <config.h>

.globl _start
_start:
	b	reset
	b	undefined_instruction
	b	software_interrupt
	b	prefetch_abort
	b	data_abort
	b	reserved
	b	irq
	b	fiq

	.align  5
undefined_instruction:
software_interrupt:
prefetch_abort:
data_abort:
reserved:
irq:
fiq:

1:
	b	1b

.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word _end

reset:
	/* Store the boot reason/device in scratchpad */
	bl	save_boot_params

	/* Set the cpu to SVC32 mode */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f	@ clear all mode bits
	orr	r0, r0, #0xd3	@ set SVC mode, disable FIQ and IRQ
	msr	cpsr, r0

	/* The mask ROM code should have PLL and others stable */
	bl	cpu_early_init
	bl	setup_sram_stack

clear_bss:
	ldr	r0, _bss_start		@ find start of bss segment
	ldr	r1, _bss_end		@ stop here
	mov 	r2, #0x00000000		@ clear value
clear_loop:
	str	r2, [r0]		@ clear BSS location
	cmp	r0, r1			@ are we at the end yet
	add	r0, r0, #4		@ increment clear index pointer
	bne	clear_loop		@ keep clearing till at end

	bl	main			@ jump to C code

/*
 * Setup CP15 registers (cache, MMU, TLBs). The I-cache is turned on.
 */
cpu_early_init:
	/* Invalidate L1 I/D */
        mov	r0, #0			@ set up for MCR
        mcr	p15, 0, r0, c8, c7, 0	@ invalidate TLBs
        mcr	p15, 0, r0, c7, c5, 0	@ invalidate icache
	mcr	p15, 0, r0, c7, c5, 6	@ invalidate BP array
	mcr	p15, 0, r0, c7, c10, 4	@ DSB
	mcr	p15, 0, r0, c7, c5, 4	@ ISB

	/* Disable MMU stuff and caches */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00000002	@ set bit 1 (--A-) Align
	orr	r0, r0, #0x00000800	@ set bit 11 (Z---) BTB
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-cache
	mcr	p15, 0, r0, c1, c0, 0
	mov	pc, lr

setup_sram_stack:
	/* Setup a temporary stack */
	ldr	sp, =SRAM_STACK
	bic	sp, sp, #7		@ 8-byte alignment for ABI compliance */
	mov	pc, lr

save_boot_params:
	/* Store the boot reason/device in scratchpad */
	ldr     r4, scratchpad
	ldr     r5, [r0, #0x8]          @ r5 <- value of boot device
	bic	r5, r5, #0xFFFFFF00	@ clear bits other than first byte
	str     r5, [r4]                @ store r5 in scratchpad reg

	/* Store the boot mode (raw/FAT) in scratchpad */
	ldr	r5, [r0, #0x4]		@ get the device descriptor ptr
	ldr	r5, [r5, #0x18]		@ get the pDeviceData ptr
	ldr	r5, [r5, #0x8]		@ get the boot mode
	str	r5, [r4, #0x4]		@ store boot mode in scratchpad + 4
	mov	pc, lr

scratchpad:
	.word 0x4A326000

