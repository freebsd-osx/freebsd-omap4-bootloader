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

#ifndef _BOOT_H_
#define _BOOT_H_

#include <sys/types.h>

#include <machine/stdarg.h>

#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define debug(fmt, args...) do { printf("%s(): "fmt, __func__, ##args); } while (0)
#else
#define debug(fmt, args...)
#endif

#define OMAP4430_ES1_0	0x44300100
#define OMAP4430_ES2_0	0x44300200
#define OMAP4430_ES2_1	0x44300210
#define OMAP4430_ES2_2	0x44300220
#define OMAP4430_ES2_3	0x44300230
#define OMAP4460_ES1_0	0x44600100
#define OMAP4460_ES1_1	0x44600110
#define OMAP4470_ES1_0	0x44700100
#define REV_INVALID	0x00000000

void	mux_init(void);
void	clock_init(void);
void	scale_vcores(void);
void	timer_init(void);
void	sdram_init(void);
void	cons_init(void);
void	storage_init(void);
void	watchdog_init(void);

void		sdelay(unsigned long loops);
void		udelay(unsigned long usec);
unsigned long	get_timer(unsigned long base);
uint32_t	poll(uint32_t mask, uint32_t value, uint32_t addr);

/* structure for ddr timings */
struct ddr_regs {
	uint32_t config_init;
	uint32_t config;
	uint32_t tim1;
	uint32_t tim2;
	uint32_t tim3;
	uint32_t phy_ctrl_1;
	uint32_t ref_ctrl;
	uint32_t zq_config;
	uint8_t mr1;
	uint8_t mr2;
};

void	enable_uart_clocks(void);
void	ddr_init(const struct ddr_regs *ddr1, const struct ddr_regs *ddr2);
void	configure_core_dpll_no_lock(void);
void	lock_core_dpll_shadow(void);
void	force_emif_self_refresh(void);

uint32_t	get_omap_rev(void);
uint32_t	get_sdram_banks(void);
uint32_t	get_sdram_start(void);
uint32_t	get_sdram_size(void);
uint32_t	warm_reset(void);
void		reset_cpu(void);

int	mmc_init(int slot);
u_long	mmc_read(u_long *dst, u_long start, unsigned size);
u_long	mmc_bread(u_long *dst, u_long start, unsigned nblk);
int	mmc_write(u_long *src, u_long start, unsigned size);
uint32_t	mmc_size(void);

struct storage {
	u_long size;
	u_long (*read)(u_long *dst, u_long start, unsigned nblk);
	int (*write)(u_long *src, u_long start, unsigned size);
};

struct storage *get_storage(void);

#endif /* !_BOOT_H_ */
