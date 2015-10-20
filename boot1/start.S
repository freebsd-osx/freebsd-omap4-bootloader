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

#include <omap4/omap4.h>

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

reset:
	/* Store the boot mode/device in scratchpad */
#	bl	save_boot_params

        mrs	r0, cpsr
        and	r1, r0, #0x1f		@ mask mode bits
        teq	r1, #0x1a		@ test for HYP mode
        bicne	r0, r0, #0x1f		@ clear all mode bits
        orrne	r0, r0, #0x13		@ set SVC mode
        orr	r0, r0, #0xc0		@ disable FIQ and IRQ
	msr	cpsr, r0

	/* The mask ROM code should have PLL and others stable */
	bl	cpu_init_cp15
	bl	lowlevel_init
#	bl	c_runtime_init

#	bl	main			@ jump to C code
1:
	b	1b

/*
 * Setup CP15 registers (cache, MMU, TLBs). The I-cache is turned on.
 */
cpu_init_cp15:
	/* Invalidate L1 I/D */
        mov	r0, #0			@ set up for MCR
        mcr	p15, 0, r0, c8, c7, 0	@ invalidate TLBs
        mcr	p15, 0, r0, c7, c5, 0	@ invalidate icache
	mcr	p15, 0, r0, c7, c5, 6	@ invalidate branch predictor array
	mcr	p15, 0, r0, c7, c10, 4	@ DSB
	mcr	p15, 0, r0, c7, c5, 4	@ ISB

	/* Disable MMU stuff and caches */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00000002	@ set bit 1 (--A-) Align
	orr	r0, r0, #0x00000800	@ set bit 11 (Z---) Program flow prediction
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-cache
	mcr	p15, 0, r0, c1, c0, 0
	mov	pc, lr

save_boot_params:
	/* Store the boot device in scratchpad */
	ldr     r4, =OMAP44XX_SCRATCH_BOOT_PARAMS
	ldr     r5, [r0, #0x8]		@ r5 <- value of boot device
	bic	r5, r5, #0xFFFFFF00	@ clear bits other than first byte
	str     r5, [r4]		@ store boot device in scratchpad reg

	/* Store the ch flags in scratchpad */
	ldr	r5, [r0, #0xA]		@ r5 <-vlaule of ch flags
	bic	r5, r5, #0xFFFFFF00	@ clear bits other than first byte
	str     r5, [r4, #0x4]		@ store ch flags in scratchpad reg

	/* Store the boot mode (raw/FAT) in scratchpad */
	ldr	r5, [r0, #0x4]		@ get the device descriptor ptr
	ldr	r5, [r5, #0x18]		@ get the pDeviceData ptr
	ldr	r5, [r5, #0x8]		@ get the boot mode
	str	r5, [r4, #0x8]		@ store boot mode in scratchpad + 8
	mov	pc, lr


