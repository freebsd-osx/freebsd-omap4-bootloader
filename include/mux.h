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

#ifndef _MUX_H_
#define _MUX_H_

#include <io.h>

/*
 * OFF_PD       - Off mode pull type down
 * OFF_PU       - Off mode pull type up
 * OFF_OUT_PTD  - Off Mode Mux low for OUT
 * OFF_OUT_PTU  - Off Mode Mux high for OUT
 * OFF_IN       - Off Mode Mux set to IN
 * OFF_OUT      - Off Mode Mux set to OUT
 * OFF_EN       - Off Mode Mux Enable
 * IEN          - Input Enable
 * IDIS         - Input Disable
 * PTD          - Pull type Down
 * PTU          - Pull type Up
 * DIS          - Pull type selection is inactive
 * EN           - Pull type selection is active
 * M0           - Mode 0
 */

#define OFF_PD          (0 << 12)
#define OFF_PU          (0 << 12)
#define OFF_OUT_PTD     (0 << 10)
#define OFF_OUT_PTU     (0 << 10)
#define OFF_IN          (0 << 10)
#define OFF_OUT         (0 << 10)
#define OFF_EN          (0 << 9)

#define IEN             (1 << 8)
#define IDIS            (0 << 8)
#define PTU             (3 << 3)
#define PTD             (1 << 3)
#define EN              (1 << 3)
#define DIS             (0 << 3)

#define M0              0
#define M1              1
#define M2              2
#define M3              3
#define M4              4
#define M5              5
#define M6              6
#define M7              7

#define OFF_IN_PD       0
#define OFF_IN_PU       0
#define OFF_OUT_PD      0
#define OFF_OUT_PU      0

//#define	set_core(OFFSET, VALUE)\
//	writew((VALUE), OMAP44XX_CTRL_PADCONF_CORE_BASE + (OFFSET));
//#define	set_wkup(OFFSET, VALUE)\
//	writew((VALUE), OMAP44XX_CTRL_PADCONF_WKUP_BASE + (OFFSET));

#define	mux(ADDR, VALUE)	writew((VALUE), (ADDR));

//#define	CP(x)	(CONTROL_PADCONF_##x)
//#define	WK(x)	(CONTROL_WKUP_##x)

#endif
