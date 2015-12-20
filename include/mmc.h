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

#ifndef _MMC_H_
#define _MMC_H_

#include <sys/types.h>

#define MMC_AC_CMD_RCA_MASK     (unsigned int)(0xffff << 16)
#define MMC_BC_CMD_DSR_MASK     (unsigned int)(0xffff << 16)
#define MMC_DSR_DEFAULT         (0x0404)
#define SD_CMD8_CHECK_PATTERN	(0xaa)
#define SD_CMD8_2_7_3_6_V_RANGE	(0x01 << 8)

#define EXT_CSD_CMD_SET_NORMAL		(1<<0)
#define EXT_CSD_HS_TIMING		185
#define MMC_SWITCH_MODE_WRITE_BYTE	0x03
#define EXT_CSD_BUS_WIDTH		183
#define MMC_BUS_WIDTH_8			3
#define EXT_CSD_BUS_WIDTH_8		2

#define MMC_OCR_REG_ACCESS_MODE_MASK			(0x3 << 29)
#define MMC_OCR_REG_ACCESS_MODE_BYTE    		(0x0 << 29)
#define MMC_OCR_REG_ACCESS_MODE_SECTOR  		(0x2 << 29)

#define MMC_OCR_REG_HOST_CAPACITY_SUPPORT_MASK		(0x1 << 30)
#define MMC_OCR_REG_HOST_CAPACITY_SUPPORT_BYTE		(0x0 << 30)
#define MMC_OCR_REG_HOST_CAPACITY_SUPPORT_SECTOR	(0x1 << 30)

#define MMC_SD2_CSD_C_SIZE_LSB_MASK         (0xffff)
#define MMC_SD2_CSD_C_SIZE_MSB_MASK         (0x003f)
#define MMC_SD2_CSD_C_SIZE_MSB_OFFSET       (16)
#define MMC_CSD_C_SIZE_LSB_MASK             (0x0003)
#define MMC_CSD_C_SIZE_MSB_MASK             (0x03ff)
#define MMC_CSD_C_SIZE_MSB_OFFSET           (2)

#define MMC_CSD_TRAN_SPEED_UNIT_MASK        (0x07 << 0)
#define MMC_CSD_TRAN_SPEED_FACTOR_MASK      (0x0f << 3)
#define MMC_CSD_TRAN_SPEED_UNIT_100MHZ      (0x3 << 0)
#define MMC_CSD_TRAN_SPEED_FACTOR_1_0       (0x01 << 3)
#define MMC_CSD_TRAN_SPEED_FACTOR_8_0       (0x0f << 3)

#define MMC_READY_FOR_DATA (0x01 << 8)

struct mmc {
	struct mmchs *host;
	uint32_t slot;
	uint32_t type;
	uint32_t version;
	uint32_t mode;
	uint32_t size;
	uint32_t rca;
};

struct mmc_csd {
	unsigned not_used:1;
	unsigned crc:7;
	unsigned ecc:2;
	unsigned file_format:2;
	unsigned tmp_write_protect:1;
	unsigned perm_write_protect:1;
	unsigned copy:1;
	unsigned file_format_grp:1;
	unsigned content_prot_app:1;
	unsigned reserved_1:4;
	unsigned write_bl_partial:1;
	unsigned write_bl_len:4;
	unsigned r2w_factor:3;
	unsigned default_ecc:2;
	unsigned wp_grp_enable:1;
	unsigned wp_grp_size:5;
	unsigned erase_grp_mult:5;
	unsigned erase_grp_size:5;
	unsigned c_size_mult:3;
	unsigned vdd_w_curr_max:3;
	unsigned vdd_w_curr_min:3;
	unsigned vdd_r_curr_max:3;
	unsigned vdd_r_curr_min:3;
	unsigned c_size_lsb:2;
	unsigned c_size_msb:10;
	unsigned reserved_2:2;
	unsigned dsr_imp:1;
	unsigned read_blk_misalign:1;
	unsigned write_blk_misalign:1;
	unsigned read_bl_partial:1;
	unsigned read_bl_len:4;
	unsigned ccc:12;
	unsigned tran_speed:8;
	unsigned nsac:8;
	unsigned taac:8;
	unsigned reserved_3:2;
	unsigned spec_vers:4;
	unsigned csd_structure:2;
};

/* csd for sd2.0 */
struct mmc_sd2_csd {
	unsigned not_used:1;
	unsigned crc:7;
	unsigned reserved_1:2;
	unsigned file_format:2;
	unsigned tmp_write_protect:1;
	unsigned perm_write_protect:1;
	unsigned copy:1;
	unsigned file_format_grp:1;
	unsigned reserved_2:5;
	unsigned write_bl_partial:1;
	unsigned write_bl_len:4;
	unsigned r2w_factor:3;
	unsigned reserved_3:2;
	unsigned wp_grp_enable:1;
	unsigned wp_grp_size:7;
	unsigned sector_size:7;
	unsigned erase_blk_len:1;
	unsigned reserved_4:1;
	unsigned c_size_lsb:16;
	unsigned c_size_msb:6;
	unsigned reserved_5:6;
	unsigned dsr_imp:1;
	unsigned read_blk_misalign:1;
	unsigned write_blk_misalign:1;
	unsigned read_bl_partial:1;
	unsigned read_bl_len:4;
	unsigned ccc:12;
	unsigned tran_speed:8;
	unsigned nsac:8;
	unsigned taac:8;
	unsigned reserved_6:6;
	unsigned csd_structure:2;
};

/* extended csd - 512 bytes long */
struct mmc_extended_csd {
	unsigned char reserved_1[181];
	unsigned char erasedmemorycontent;
	unsigned char reserved_2;
	unsigned char buswidthmode;
	unsigned char reserved_3;
	unsigned char highspeedinterfacetiming;
	unsigned char reserved_4;
	unsigned char powerclass;
	unsigned char reserved_5;
	unsigned char commandsetrevision;
	unsigned char reserved_6;
	unsigned char commandset;
	unsigned char extendedcsdrevision;
	unsigned char reserved_7;
	unsigned char csdstructureversion;
	unsigned char reserved_8;
	unsigned char cardtype;
	unsigned char reserved_9[3];
	unsigned char powerclass_52mhz_1_95v;
	unsigned char powerclass_26mhz_1_95v;
	unsigned char powerclass_52mhz_3_6v;
	unsigned char powerclass_26mhz_3_6v;
	unsigned char reserved_10;
	unsigned char minreadperf_4b_26mhz;
	unsigned char minwriteperf_4b_26mhz;
	unsigned char minreadperf_8b_26mhz_4b_52mhz;
	unsigned char minwriteperf_8b_26mhz_4b_52mhz;
	unsigned char minreadperf_8b_52mhz;
	unsigned char minwriteperf_8b_52mhz;
	unsigned char reserved_11;
	unsigned int sectorcount;
	unsigned char reserved_12[288];
	unsigned char supportedcommandsets;
	unsigned char reserved_13[7];
};

/* mmc sd responce */
struct mmc_resp_r3 {
	unsigned int ocr;
};

struct mmc_resp_r6 {
	unsigned short cardstatus;
	unsigned short newpublishedrca;
};

static const unsigned int tran_exp[] = {
	10000, 100000, 1000000, 10000000,
	0,     0,      0,       0
};

static const unsigned char tran_mant[] = {
	0,      10,     12,     13,     15,     20,     25,     30,
	35,     40,     45,     50,     55,     60,     70,     80,
};

#endif /* !_MMC_H_ */
