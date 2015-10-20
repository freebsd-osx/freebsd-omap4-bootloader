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

#ifndef	_OMAP_DATA_H_
#define	_OMAP_DATA_H_

#include <sys/types.h>

#define NUM_SYS_CLKS	7

struct prcm_regs {
	/* cm1.ckgen */
	uint32_t cm_clksel_core;
	uint32_t cm_clksel_abe;
	uint32_t cm_dll_ctrl;
	uint32_t cm_clkmode_dpll_core;
	uint32_t cm_idlest_dpll_core;
	uint32_t cm_autoidle_dpll_core;
	uint32_t cm_clksel_dpll_core;
	uint32_t cm_div_m2_dpll_core;
	uint32_t cm_div_m3_dpll_core;
	uint32_t cm_div_h11_dpll_core;
	uint32_t cm_div_h12_dpll_core;
	uint32_t cm_div_h13_dpll_core;
	uint32_t cm_div_h14_dpll_core;
	uint32_t cm_div_h21_dpll_core;
	uint32_t cm_div_h24_dpll_core;
	uint32_t cm_ssc_deltamstep_dpll_core;
	uint32_t cm_ssc_modfreqdiv_dpll_core;
	uint32_t cm_emu_override_dpll_core;
	uint32_t cm_div_h22_dpllcore;
	uint32_t cm_div_h23_dpll_core;
	uint32_t cm_clkmode_dpll_mpu;
	uint32_t cm_idlest_dpll_mpu;
	uint32_t cm_autoidle_dpll_mpu;
	uint32_t cm_clksel_dpll_mpu;
	uint32_t cm_div_m2_dpll_mpu;
	uint32_t cm_ssc_deltamstep_dpll_mpu;
	uint32_t cm_ssc_modfreqdiv_dpll_mpu;
	uint32_t cm_bypclk_dpll_mpu;
	uint32_t cm_clkmode_dpll_iva;
	uint32_t cm_idlest_dpll_iva;
	uint32_t cm_autoidle_dpll_iva;
	uint32_t cm_clksel_dpll_iva;
	uint32_t cm_div_h11_dpll_iva;
	uint32_t cm_div_h12_dpll_iva;
	uint32_t cm_ssc_deltamstep_dpll_iva;
	uint32_t cm_ssc_modfreqdiv_dpll_iva;
	uint32_t cm_bypclk_dpll_iva;
	uint32_t cm_clkmode_dpll_abe;
	uint32_t cm_idlest_dpll_abe;
	uint32_t cm_autoidle_dpll_abe;
	uint32_t cm_clksel_dpll_abe;
	uint32_t cm_div_m2_dpll_abe;
	uint32_t cm_div_m3_dpll_abe;
	uint32_t cm_ssc_deltamstep_dpll_abe;
	uint32_t cm_ssc_modfreqdiv_dpll_abe;
	uint32_t cm_clkmode_dpll_ddrphy;
	uint32_t cm_idlest_dpll_ddrphy;
	uint32_t cm_autoidle_dpll_ddrphy;
	uint32_t cm_clksel_dpll_ddrphy;
	uint32_t cm_div_m2_dpll_ddrphy;
	uint32_t cm_div_h11_dpll_ddrphy;
	uint32_t cm_div_h12_dpll_ddrphy;
	uint32_t cm_div_h13_dpll_ddrphy;
	uint32_t cm_ssc_deltamstep_dpll_ddrphy;
	uint32_t cm_clkmode_dpll_dsp;
	uint32_t cm_shadow_freq_config1;
	uint32_t cm_clkmode_dpll_gmac;
	uint32_t cm_mpu_mpu_clkctrl;

	/* cm1.dsp */
	uint32_t cm_dsp_clkstctrl;
	uint32_t cm_dsp_dsp_clkctrl;

	/* cm1.abe */
	uint32_t cm1_abe_clkstctrl;
	uint32_t cm1_abe_l4abe_clkctrl;
	uint32_t cm1_abe_aess_clkctrl;
	uint32_t cm1_abe_pdm_clkctrl;
	uint32_t cm1_abe_dmic_clkctrl;
	uint32_t cm1_abe_mcasp_clkctrl;
	uint32_t cm1_abe_mcbsp1_clkctrl;
	uint32_t cm1_abe_mcbsp2_clkctrl;
	uint32_t cm1_abe_mcbsp3_clkctrl;
	uint32_t cm1_abe_slimbus_clkctrl;
	uint32_t cm1_abe_timer5_clkctrl;
	uint32_t cm1_abe_timer6_clkctrl;
	uint32_t cm1_abe_timer7_clkctrl;
	uint32_t cm1_abe_timer8_clkctrl;
	uint32_t cm1_abe_wdt3_clkctrl;

	/* cm2.ckgen */
	uint32_t cm_clksel_mpu_m3_iss_root;
	uint32_t cm_clksel_usb_60mhz;
	uint32_t cm_scale_fclk;
	uint32_t cm_core_dvfs_perf1;
	uint32_t cm_core_dvfs_perf2;
	uint32_t cm_core_dvfs_perf3;
	uint32_t cm_core_dvfs_perf4;
	uint32_t cm_core_dvfs_current;
	uint32_t cm_iva_dvfs_perf_tesla;
	uint32_t cm_iva_dvfs_perf_ivahd;
	uint32_t cm_iva_dvfs_perf_abe;
	uint32_t cm_iva_dvfs_current;
	uint32_t cm_clkmode_dpll_per;
	uint32_t cm_idlest_dpll_per;
	uint32_t cm_autoidle_dpll_per;
	uint32_t cm_clksel_dpll_per;
	uint32_t cm_div_m2_dpll_per;
	uint32_t cm_div_m3_dpll_per;
	uint32_t cm_div_h11_dpll_per;
	uint32_t cm_div_h12_dpll_per;
	uint32_t cm_div_h13_dpll_per;
	uint32_t cm_div_h14_dpll_per;
	uint32_t cm_ssc_deltamstep_dpll_per;
	uint32_t cm_ssc_modfreqdiv_dpll_per;
	uint32_t cm_emu_override_dpll_per;
	uint32_t cm_clkmode_dpll_usb;
	uint32_t cm_idlest_dpll_usb;
	uint32_t cm_autoidle_dpll_usb;
	uint32_t cm_clksel_dpll_usb;
	uint32_t cm_div_m2_dpll_usb;
	uint32_t cm_ssc_deltamstep_dpll_usb;
	uint32_t cm_ssc_modfreqdiv_dpll_usb;
	uint32_t cm_clkdcoldo_dpll_usb;
	uint32_t cm_clkmode_dpll_pcie_ref;
	uint32_t cm_clkmode_apll_pcie;
	uint32_t cm_idlest_apll_pcie;
	uint32_t cm_div_m2_apll_pcie;
	uint32_t cm_clkvcoldo_apll_pcie;
	uint32_t cm_clkmode_dpll_unipro;
	uint32_t cm_idlest_dpll_unipro;
	uint32_t cm_autoidle_dpll_unipro;
	uint32_t cm_clksel_dpll_unipro;
	uint32_t cm_div_m2_dpll_unipro;
	uint32_t cm_ssc_deltamstep_dpll_unipro;
	uint32_t cm_ssc_modfreqdiv_dpll_unipro;
	uint32_t cm_coreaon_usb_phy_core_clkctrl;
	uint32_t cm_coreaon_usb_phy2_core_clkctrl;

	/* cm2.core */
	uint32_t cm_coreaon_bandgap_clkctrl;
	uint32_t cm_coreaon_io_srcomp_clkctrl;
	uint32_t cm_l3_1_clkstctrl;
	uint32_t cm_l3_1_dynamicdep;
	uint32_t cm_l3_1_l3_1_clkctrl;
	uint32_t cm_l3_2_clkstctrl;
	uint32_t cm_l3_2_dynamicdep;
	uint32_t cm_l3_2_l3_2_clkctrl;
	uint32_t cm_l3_gpmc_clkctrl;
	uint32_t cm_l3_2_ocmc_ram_clkctrl;
	uint32_t cm_mpu_m3_clkstctrl;
	uint32_t cm_mpu_m3_staticdep;
	uint32_t cm_mpu_m3_dynamicdep;
	uint32_t cm_mpu_m3_mpu_m3_clkctrl;
	uint32_t cm_sdma_clkstctrl;
	uint32_t cm_sdma_staticdep;
	uint32_t cm_sdma_dynamicdep;
	uint32_t cm_sdma_sdma_clkctrl;
	uint32_t cm_memif_clkstctrl;
	uint32_t cm_memif_dmm_clkctrl;
	uint32_t cm_memif_emif_fw_clkctrl;
	uint32_t cm_memif_emif_1_clkctrl;
	uint32_t cm_memif_emif_2_clkctrl;
	uint32_t cm_memif_dll_clkctrl;
	uint32_t cm_memif_emif_h1_clkctrl;
	uint32_t cm_memif_emif_h2_clkctrl;
	uint32_t cm_memif_dll_h_clkctrl;
	uint32_t cm_c2c_clkstctrl;
	uint32_t cm_c2c_staticdep;
	uint32_t cm_c2c_dynamicdep;
	uint32_t cm_c2c_sad2d_clkctrl;
	uint32_t cm_c2c_modem_icr_clkctrl;
	uint32_t cm_c2c_sad2d_fw_clkctrl;
	uint32_t cm_l4cfg_clkstctrl;
	uint32_t cm_l4cfg_dynamicdep;
	uint32_t cm_l4cfg_l4_cfg_clkctrl;
	uint32_t cm_l4cfg_hw_sem_clkctrl;
	uint32_t cm_l4cfg_mailbox_clkctrl;
	uint32_t cm_l4cfg_sar_rom_clkctrl;
	uint32_t cm_l3instr_clkstctrl;
	uint32_t cm_l3instr_l3_3_clkctrl;
	uint32_t cm_l3instr_l3_instr_clkctrl;
	uint32_t cm_l3instr_intrconn_wp1_clkctrl;

	/* cm2.ivahd */
	uint32_t cm_ivahd_clkstctrl;
	uint32_t cm_ivahd_ivahd_clkctrl;
	uint32_t cm_ivahd_sl2_clkctrl;

	/* cm2.cam */
	uint32_t cm_cam_clkstctrl;
	uint32_t cm_cam_iss_clkctrl;
	uint32_t cm_cam_fdif_clkctrl;
	uint32_t cm_cam_vip1_clkctrl;
	uint32_t cm_cam_vip2_clkctrl;
	uint32_t cm_cam_vip3_clkctrl;
	uint32_t cm_cam_lvdsrx_clkctrl;
	uint32_t cm_cam_csi1_clkctrl;
	uint32_t cm_cam_csi2_clkctrl;

	/* cm2.dss */
	uint32_t cm_dss_clkstctrl;
	uint32_t cm_dss_dss_clkctrl;

	/* cm2.sgx */
	uint32_t cm_sgx_clkstctrl;
	uint32_t cm_sgx_sgx_clkctrl;

	/* cm2.l3init */
	uint32_t cm_l3init_clkstctrl;

	/* cm2.l3init */
	uint32_t cm_l3init_hsmmc1_clkctrl;
	uint32_t cm_l3init_hsmmc2_clkctrl;
	uint32_t cm_l3init_hsi_clkctrl;
	uint32_t cm_l3init_hsusbhost_clkctrl;
	uint32_t cm_l3init_hsusbotg_clkctrl;
	uint32_t cm_l3init_hsusbtll_clkctrl;
	uint32_t cm_l3init_p1500_clkctrl;
	uint32_t cm_l3init_sata_clkctrl;
	uint32_t cm_l3init_fsusb_clkctrl;
	uint32_t cm_l3init_ocp2scp1_clkctrl;
	uint32_t cm_l3init_ocp2scp3_clkctrl;
	uint32_t cm_l3init_usb_otg_ss_clkctrl;

	uint32_t prm_irqstatus_mpu_2;

	/* cm2.l4per */
	uint32_t cm_l4per_clkstctrl;
	uint32_t cm_l4per_dynamicdep;
	uint32_t cm_l4per_adc_clkctrl;
	uint32_t cm_l4per_gptimer10_clkctrl;
	uint32_t cm_l4per_gptimer11_clkctrl;
	uint32_t cm_l4per_gptimer2_clkctrl;
	uint32_t cm_l4per_gptimer3_clkctrl;
	uint32_t cm_l4per_gptimer4_clkctrl;
	uint32_t cm_l4per_gptimer9_clkctrl;
	uint32_t cm_l4per_elm_clkctrl;
	uint32_t cm_l4per_gpio2_clkctrl;
	uint32_t cm_l4per_gpio3_clkctrl;
	uint32_t cm_l4per_gpio4_clkctrl;
	uint32_t cm_l4per_gpio5_clkctrl;
	uint32_t cm_l4per_gpio6_clkctrl;
	uint32_t cm_l4per_hdq1w_clkctrl;
	uint32_t cm_l4per_hecc1_clkctrl;
	uint32_t cm_l4per_hecc2_clkctrl;
	uint32_t cm_l4per_i2c1_clkctrl;
	uint32_t cm_l4per_i2c2_clkctrl;
	uint32_t cm_l4per_i2c3_clkctrl;
	uint32_t cm_l4per_i2c4_clkctrl;
	uint32_t cm_l4per_l4per_clkctrl;
	uint32_t cm_l4per_mcasp2_clkctrl;
	uint32_t cm_l4per_mcasp3_clkctrl;
	uint32_t cm_l4per_mgate_clkctrl;
	uint32_t cm_l4per_mcspi1_clkctrl;
	uint32_t cm_l4per_mcspi2_clkctrl;
	uint32_t cm_l4per_mcspi3_clkctrl;
	uint32_t cm_l4per_mcspi4_clkctrl;
	uint32_t cm_l4per_gpio7_clkctrl;
	uint32_t cm_l4per_gpio8_clkctrl;
	uint32_t cm_l4per_mmcsd3_clkctrl;
	uint32_t cm_l4per_mmcsd4_clkctrl;
	uint32_t cm_l4per_msprohg_clkctrl;
	uint32_t cm_l4per_slimbus2_clkctrl;
	uint32_t cm_l4per_qspi_clkctrl;
	uint32_t cm_l4per_uart1_clkctrl;
	uint32_t cm_l4per_uart2_clkctrl;
	uint32_t cm_l4per_uart3_clkctrl;
	uint32_t cm_l4per_uart4_clkctrl;
	uint32_t cm_l4per_mmcsd5_clkctrl;
	uint32_t cm_l4per_i2c5_clkctrl;
	uint32_t cm_l4per_uart5_clkctrl;
	uint32_t cm_l4per_uart6_clkctrl;
	uint32_t cm_l4sec_clkstctrl;
	uint32_t cm_l4sec_staticdep;
	uint32_t cm_l4sec_dynamicdep;
	uint32_t cm_l4sec_aes1_clkctrl;
	uint32_t cm_l4sec_aes2_clkctrl;
	uint32_t cm_l4sec_des3des_clkctrl;
	uint32_t cm_l4sec_pkaeip29_clkctrl;
	uint32_t cm_l4sec_rng_clkctrl;
	uint32_t cm_l4sec_sha2md51_clkctrl;
	uint32_t cm_l4sec_cryptodma_clkctrl;

	/* l4 wkup regs */
	uint32_t cm_abe_pll_ref_clksel;
	uint32_t cm_sys_clksel;
	uint32_t cm_abe_pll_sys_clksel;
	uint32_t cm_wkup_clkstctrl;
	uint32_t cm_wkup_l4wkup_clkctrl;
	uint32_t cm_wkup_wdtimer1_clkctrl;
	uint32_t cm_wkup_wdtimer2_clkctrl;
	uint32_t cm_wkup_gpio1_clkctrl;
	uint32_t cm_wkup_gptimer1_clkctrl;
	uint32_t cm_wkup_gptimer12_clkctrl;
	uint32_t cm_wkup_synctimer_clkctrl;
	uint32_t cm_wkup_usim_clkctrl;
	uint32_t cm_wkup_sarram_clkctrl;
	uint32_t cm_wkup_keyboard_clkctrl;
	uint32_t cm_wkup_rtc_clkctrl;
	uint32_t cm_wkup_bandgap_clkctrl;
	uint32_t cm_wkupaon_scrm_clkctrl;
	uint32_t cm_wkupaon_io_srcomp_clkctrl;
	uint32_t prm_rstctrl;
	uint32_t prm_rstst;
	uint32_t prm_rsttime;
	uint32_t prm_vc_val_bypass;
	uint32_t prm_vc_cfg_i2c_mode;
	uint32_t prm_vc_cfg_i2c_clk;
	uint32_t prm_abbldo_mpu_setup;
	uint32_t prm_abbldo_mpu_ctrl;

	uint32_t cm_div_m4_dpll_core;
	uint32_t cm_div_m5_dpll_core;
	uint32_t cm_div_m6_dpll_core;
	uint32_t cm_div_m7_dpll_core;
	uint32_t cm_div_m4_dpll_iva;
	uint32_t cm_div_m5_dpll_iva;
	uint32_t cm_div_m4_dpll_ddrphy;
	uint32_t cm_div_m5_dpll_ddrphy;
	uint32_t cm_div_m6_dpll_ddrphy;
	uint32_t cm_div_m4_dpll_per;
	uint32_t cm_div_m5_dpll_per;
	uint32_t cm_div_m6_dpll_per;
	uint32_t cm_div_m7_dpll_per;
	uint32_t cm_l3instr_intrconn_wp1_clkct;
	uint32_t cm_l3init_usbphy_clkctrl;
	uint32_t cm_l4per_mcbsp4_clkctrl;
	uint32_t prm_vc_cfg_channel;

	/* SCRM stuff, used by some boards */
	uint32_t scrm_auxclk0;
	uint32_t scrm_auxclk1;

	/* GMAC Clk Ctrl */
	uint32_t cm_gmac_gmac_clkctrl;
	uint32_t cm_gmac_clkstctrl;
};

struct omap_sys_ctrl_regs {
	uint32_t control_status;
	uint32_t control_core_mac_id_0_lo;
	uint32_t control_core_mac_id_0_hi;
	uint32_t control_core_mac_id_1_lo;
	uint32_t control_core_mac_id_1_hi;
	uint32_t control_std_fuse_opp_vdd_mpu_2;
	uint32_t control_phy_power_usb;
	uint32_t control_core_mmr_lock1;
	uint32_t control_core_mmr_lock2;
	uint32_t control_core_mmr_lock3;
	uint32_t control_core_mmr_lock4;
	uint32_t control_core_mmr_lock5;
	uint32_t control_core_control_io1;
	uint32_t control_core_control_io2;
	uint32_t control_id_code;
	uint32_t control_std_fuse_opp_bgap;
	uint32_t control_ldosram_iva_voltage_ctrl;
	uint32_t control_ldosram_mpu_voltage_ctrl;
	uint32_t control_ldosram_core_voltage_ctrl;
	uint32_t control_usbotghs_ctrl;
	uint32_t control_phy_power_sata;
	uint32_t control_padconf_core_base;
	uint32_t control_paconf_global;
	uint32_t control_paconf_mode;
	uint32_t control_smart1io_padconf_0;
	uint32_t control_smart1io_padconf_1;
	uint32_t control_smart1io_padconf_2;
	uint32_t control_smart2io_padconf_0;
	uint32_t control_smart2io_padconf_1;
	uint32_t control_smart2io_padconf_2;
	uint32_t control_smart3io_padconf_0;
	uint32_t control_smart3io_padconf_1;
	uint32_t control_pbias;
	uint32_t control_i2c_0;
	uint32_t control_camera_rx;
	uint32_t control_hdmi_tx_phy;
	uint32_t control_uniportm;
	uint32_t control_dsiphy;
	uint32_t control_mcbsplp;
	uint32_t control_usb2phycore;
	uint32_t control_hdmi_1;
	uint32_t control_hsi;
	uint32_t control_ddr3ch1_0;
	uint32_t control_ddr3ch2_0;
	uint32_t control_ddrch1_0;
	uint32_t control_ddrch1_1;
	uint32_t control_ddrch2_0;
	uint32_t control_ddrch2_1;
	uint32_t control_lpddr2ch1_0;
	uint32_t control_lpddr2ch1_1;
	uint32_t control_ddrio_0;
	uint32_t control_ddrio_1;
	uint32_t control_ddrio_2;
	uint32_t control_ddr_control_ext_0;
	uint32_t control_lpddr2io1_0;
	uint32_t control_lpddr2io1_1;
	uint32_t control_lpddr2io1_2;
	uint32_t control_lpddr2io1_3;
	uint32_t control_lpddr2io2_0;
	uint32_t control_lpddr2io2_1;
	uint32_t control_lpddr2io2_2;
	uint32_t control_lpddr2io2_3;
	uint32_t control_hyst_1;
	uint32_t control_usbb_hsic_control;
	uint32_t control_c2c;
	uint32_t control_core_control_spare_rw;
	uint32_t control_core_control_spare_r;
	uint32_t control_core_control_spare_r_c0;
	uint32_t control_srcomp_north_side;
	uint32_t control_srcomp_south_side;
	uint32_t control_srcomp_east_side;
	uint32_t control_srcomp_west_side;
	uint32_t control_srcomp_code_latch;
	uint32_t control_pbiaslite;
	uint32_t control_port_emif1_sdram_config;
	uint32_t control_port_emif1_lpddr2_nvm_config;
	uint32_t control_port_emif2_sdram_config;
	uint32_t control_emif1_sdram_config_ext;
	uint32_t control_emif2_sdram_config_ext;
	uint32_t control_wkup_ldovbb_mpu_voltage_ctrl;
	uint32_t control_smart1nopmio_padconf_0;
	uint32_t control_smart1nopmio_padconf_1;
	uint32_t control_padconf_mode;
	uint32_t control_xtal_oscillator;
	uint32_t control_i2c_2;
	uint32_t control_ckobuffer;
	uint32_t control_wkup_control_spare_rw;
	uint32_t control_wkup_control_spare_r;
	uint32_t control_wkup_control_spare_r_c0;
	uint32_t control_srcomp_east_side_wkup;
	uint32_t control_efuse_1;
	uint32_t control_efuse_2;
	uint32_t control_efuse_3;
	uint32_t control_efuse_4;
	uint32_t control_efuse_5;
	uint32_t control_efuse_6;
	uint32_t control_efuse_7;
	uint32_t control_efuse_8;
	uint32_t control_efuse_9;
	uint32_t control_efuse_10;
	uint32_t control_efuse_11;
	uint32_t control_efuse_12;
	uint32_t control_efuse_13;
	uint32_t control_padconf_wkup_base;
};

struct dpll_params {
	uint32_t m;
	uint32_t n;
	int8_t m2;
	int8_t m3;
	int8_t m4_h11;
	int8_t m5_h12;
	int8_t m6_h13;
	int8_t m7_h14;
	int8_t h21;
	int8_t h22;
	int8_t h23;
	int8_t h24;
};

struct dpll_regs {
	uint32_t cm_clkmode_dpll;
	uint32_t cm_idlest_dpll;
	uint32_t cm_autoidle_dpll;
	uint32_t cm_clksel_dpll;
	uint32_t cm_div_m2_dpll;
	uint32_t cm_div_m3_dpll;
	uint32_t cm_div_m4_h11_dpll;
	uint32_t cm_div_m5_h12_dpll;
	uint32_t cm_div_m6_h13_dpll;
	uint32_t cm_div_m7_h14_dpll;
	uint32_t reserved[2];
	uint32_t cm_div_h21_dpll;
	uint32_t cm_div_h22_dpll;
	uint32_t cm_div_h23_dpll;
	uint32_t cm_div_h24_dpll;
};

struct dplls {
	const struct dpll_params *mpu;
	const struct dpll_params *core;
	const struct dpll_params *per;
	const struct dpll_params *abe;
	const struct dpll_params *iva;
	const struct dpll_params *usb;
	const struct dpll_params *ddr;
	const struct dpll_params *gmac;
};

struct pmic_data {
	uint32_t base_offset;
	uint32_t step;
	uint32_t start_code;
	unsigned gpio;
	int gpio_en;
	uint32_t i2c_slave_addr;
	void (*pmic_bus_init)(void);
	int (*pmic_write)(uint8_t sa, uint8_t reg_addr, uint8_t reg_data);
};

/**
 * struct volts_efuse_data - efuse definition for voltage
 * @reg:	register address for efuse
 * @reg_bits:	Number of bits in a register address, mandatory.
 */
struct volts_efuse_data {
	uint32_t reg;
	uint8_t reg_bits;
};

struct volts {
	uint32_t value;
	uint32_t addr;
	struct volts_efuse_data efuse;
	struct pmic_data *pmic;
};

struct vcores_data {
	struct volts mpu;
	struct volts core;
	struct volts mm;
	struct volts gpu;
	struct volts eve;
	struct volts iva;
};

extern struct prcm_regs const **prcm;
extern struct prcm_regs const omap4_prcm;
extern struct dplls const **dplls_data;
extern struct vcores_data const **omap_vcores;
extern const uint32_t sys_clk_array[8];
extern struct omap_sys_ctrl_regs const **ctrl;
extern struct omap_sys_ctrl_regs const omap4_ctrl;

const struct dpll_params *get_mpu_dpll_params(struct dplls const *);
const struct dpll_params *get_core_dpll_params(struct dplls const *);
const struct dpll_params *get_per_dpll_params(struct dplls const *);
const struct dpll_params *get_iva_dpll_params(struct dplls const *);
const struct dpll_params *get_usb_dpll_params(struct dplls const *);
const struct dpll_params *get_abe_dpll_params(struct dplls const *);

void do_enable_clocks(uint32_t const *clk_domains,
		      uint32_t const *clk_modules_hw_auto,
		      uint32_t const *clk_modules_explicit_en,
		      uint8_t wait_for_enable);

void setup_post_dividers(uint32_t const base,
			const struct dpll_params *params);
uint32_t omap_ddr_clk(void);
uint32_t get_sys_clk_index(void);
void enable_basic_clocks(void);
void enable_basic_uboot_clocks(void);
void scale_vcores(struct vcores_data const *);
uint32_t get_offset_code(uint32_t volt_offset, struct pmic_data *pmic);
void do_scale_vcore(uint32_t vcore_reg, uint32_t volt_mv, struct pmic_data *pmic);
void abb_setup(uint32_t fuse, uint32_t ldovbb, uint32_t setup, uint32_t control,
	       uint32_t txdone, uint32_t txdone_mask, uint32_t opp);
int8_t abb_setup_ldovbb(uint32_t fuse, uint32_t ldovbb);

void usb_fake_mac_from_die_id(uint32_t *id);

static inline uint32_t
omap_revision(void)
{
	extern uint32_t *const omap_rev;
	return *omap_rev;
}

#define OMAP44xx	0x44000000

static inline uint8_t
is_omap44xx(void)
{
	extern uint32_t *const omap_rev;
	return (*omap_rev & 0xFF000000) == OMAP44xx;
};

#define OMAP54xx	0x54000000

static inline uint8_t
is_omap54xx(void)
{
	extern uint32_t *const omap_rev;
	return ((*omap_rev & 0xFF000000) == OMAP54xx);
}

#define DRA7XX		0x07000000

static inline uint8_t is_dra7xx(void)
{
	extern uint32_t *const omap_rev;
	return ((*omap_rev & 0xFF000000) == DRA7XX);
}

#endif /* !_OMAP_DATA_H_ */
