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

#ifndef _OMAP4_PLATFORM_H_
#define _OMAP4_PLATFORM_H_

#include <sys/types.h>

#include <omap4/mux_omap4.h>

void hang(void);

void bypass_dpll(uint32_t const base);
extern const struct emif_regs emif_regs_elpida_200_mhz_2cs;
extern const struct emif_regs emif_regs_elpida_380_mhz_1cs;
extern const struct emif_regs emif_regs_elpida_400_mhz_1cs;
extern const struct emif_regs emif_regs_elpida_400_mhz_2cs;
struct omap_sysinfo {
	char *board_string;
};
extern const struct omap_sysinfo sysinfo;

void gpmc_init(void);
void watchdog_init(void);
uint32_t get_device_type(void);
//void do_set_mux(uint32_t base, struct pad_conf_entry const *array, int size);
void set_muxconf_regs_essential(void);
uint32_t wait_on_value(uint32_t, uint32_t, void *, uint32_t);
void sdelay(unsigned long);
void set_pl310_ctrl_reg(uint32_t val);
void setup_clocks_for_console(void);
void prcm_init(void);
void bypass_dpll(uint32_t const base);
void freq_update_core(void);
uint32_t get_sys_clk_freq(void);
uint32_t omap4_ddr_clk(void);
void cancel_out(uint32_t *num, uint32_t *den, uint32_t den_limit);
void sdram_init(void);
uint32_t omap_sdram_size(void);
uint32_t cortex_rev(void);
void save_omap_boot_params(void);
void omap_revision_init(void);
void omap_data_init(void);
void do_io_settings(void);
void sri2c_init(void);
void gpi2c_init(void);
int omap_vc_bypass_send_value(uint8_t sa, uint8_t reg_addr, uint8_t reg_data);
uint32_t warm_reset(void);
void force_emif_self_refresh(void);
void setup_warmreset_time(void);
int timer_init(void);
void __udelay(unsigned long usec);
void do_set_mux(uint32_t base, struct pad_conf_entry const *array, int size);

#endif /* !_OMAP4_PLATFORM_H_ */
