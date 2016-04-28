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

#include <sys/types.h>

#include <io.h>
#include <omap4/hw.h>
#include <omap4/timer.h>

static struct gptimer *timer_base = (struct gptimer *)OMAP44XX_GPT2;
static u_long tbl;
static u_long lastinc;

#define TIMER_CLOCK		(V_SCLK / (2 << CONFIG_SYS_PTV))
#define TIMER_OVERFLOW_VAL	0xffffffff
#define TIMER_LOAD_VAL		0

#define CONFIG_WD_PERIOD	(10 * 1000 * 1000)	/* 10 seconds default */

void
timer_init(void)
{
	/* start the counter ticking up, reload value on overflow */
	writel(TIMER_LOAD_VAL, &timer_base->tldr);
	/* enable timer */
	writel((CONFIG_SYS_PTV << 2) | TCLR_PRE | TCLR_AR | TCLR_ST,
		&timer_base->tclr);

	/* reset time, capture current incrementer value time */
	lastinc = readl(&timer_base->tcrr) /
			(TIMER_CLOCK / CONFIG_SYS_HZ);
	tbl = 0;	/* start "advancing" time stamp from 0 */
}

u_long
get_timer_masked(void)
{
	/* current tick value */
	u_long now = readl(&timer_base->tcrr) / (TIMER_CLOCK / CONFIG_SYS_HZ);

	if (now >= lastinc) {	/* normal mode (non roll) */
		/* move stamp fordward with absoulte diff ticks */
		tbl += (now - lastinc);
	} else {	/* we have rollover of incrementer */
		tbl += ((TIMER_LOAD_VAL / (TIMER_CLOCK /
				CONFIG_SYS_HZ)) - lastinc) + now;
	}
	lastinc = now;
	return (tbl);
}

/*
 * timer without interrupts
 */
u_long
get_timer(u_long base)
{
	return (get_timer_masked() - base);
}

/* delay x useconds */
void
__udelay(u_long usec)
{
	long tmo = usec * (TIMER_CLOCK / 1000) / 1000;
	u_long now, last = readl(&timer_base->tcrr);

	while (tmo > 0) {
		now = readl(&timer_base->tcrr);
		if (last > now) /* count up timer overflow */
			tmo -= TIMER_OVERFLOW_VAL - last + now + 1;
		else
			tmo -= now - last;
		last = now;
	}
}

void
udelay(u_long usec)
{
	u_long kv;

	do {
		kv = usec > CONFIG_WD_PERIOD ? CONFIG_WD_PERIOD : usec;
		__udelay(kv);
		usec -= kv;
	} while (usec);
}

void
mdelay(u_long msec)
{
	while (msec--)
		udelay(1000);
}

uint64_t
get_ticks(void)
{
	return (get_timer(0));
}

u_long
get_tbclk(void)
{
	return (CONFIG_SYS_HZ);
}
