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

#include <mmc.h>
#include <console.h>
#include <omap4/mmc_protocol.h>

#define OMAP_MMC_MASTER_CLOCK   96000000

struct mmc_card mmc_cards[2];
struct omap_mmc mmcs[2];

int
mmc_board_init(struct omap_mmc *mmc)
{
	uint32_t value = 0;

	switch (mmc->slot) {
	case 0:
		/* SLOT-0 PBIAS config */
		value = CONTROL_PBIAS_LITE;
		CONTROL_PBIAS_LITE = value | (1 << 22) | (1 << 26);
		value = CONTROL_CONF_MMC1;
		CONTROL_CONF_MMC1  = value | (1 << 31) | (1 << 30)
					   | (1 << 27) | (1 << 26)
					   | (1 << 25);
		break;
	case 1:
		break;
	default:
		return (-1);
	}
	return (0);
}

static void
mmc_init_stream(struct omap_mmc *mmc)
{
	OMAP_HSMMC_CON(mmc->base) |= INIT_INITSTREAM;

	OMAP_HSMMC_CMD(mmc->base) = MMC_CMD0;
	while (1) {
		if ((OMAP_HSMMC_STAT(mmc->base) & CC_MASK))
			break;
	}
	OMAP_HSMMC_STAT(mmc->base) = CC_MASK;

	OMAP_HSMMC_CMD(mmc->base) = MMC_CMD0;
	while (1) {
		if ((OMAP_HSMMC_STAT(mmc->base) & CC_MASK))
			break;
	}

	OMAP_HSMMC_STAT(mmc->base) = OMAP_HSMMC_STAT(mmc->base);
	OMAP_HSMMC_CON(mmc->base) &= ~INIT_INITSTREAM;
}

static int
mmc_clock_config(struct omap_mmc *mmc, uint32_t iclk, unsigned short clk_div)
{
	uint32_t val;

	mmc_reg_out(OMAP_HSMMC_SYSCTL(mmc->base),
			(ICE_MASK | DTO_MASK | CEN_MASK),
			(ICE_STOP | DTO_15THDTO | CEN_DISABLE));

	switch (iclk) {
	case CLK_INITSEQ:
		val = MMC_INIT_SEQ_CLK / 2;
		break;
	case CLK_400KHZ:
		val = MMC_400kHz_CLK;
		break;
	case CLK_MISC:
		val = clk_div;
		break;
	default:
		return (-1);
	}
	mmc_reg_out(OMAP_HSMMC_SYSCTL(mmc->base), ICE_MASK | CLKD_MASK,
					(val << CLKD_OFFSET) | ICE_OSCILLATE);

	while (1) {
		if ((OMAP_HSMMC_SYSCTL(mmc->base) & ICS_MASK)
				!= ICS_NOTREADY)
			break;
	}

	OMAP_HSMMC_SYSCTL(mmc->base) |= CEN_ENABLE;
	return (0);
}

static int
mmc_init_setup(struct omap_mmc *mmc)
{
	uint32_t reg_val;

	mmc_board_init(mmc);

	OMAP_HSMMC_SYSCONFIG(mmc->base) |= MMC_SOFTRESET;
	while (1) {
		if ((OMAP_HSMMC_SYSSTATUS(mmc->base) & RESETDONE) != 0)
			break;
	}

	OMAP_HSMMC_SYSCTL(mmc->base) |= SOFTRESETALL;
	while (1) {
		if ((OMAP_HSMMC_SYSCTL(mmc->base) & SOFTRESETALL) == 0)
			break;
	}
	OMAP_HSMMC_HCTL(mmc->base) = DTW_1_BITMODE | SDBP_PWROFF | SDVS_3V0;
	OMAP_HSMMC_CAPA(mmc->base) |= VS30_3V0SUP | VS18_1V8SUP;

	reg_val = OMAP_HSMMC_CON(mmc->base) & RESERVED_MASK;

	OMAP_HSMMC_CON(mmc->base) = CTPL_MMC_SD | reg_val | WPP_ACTIVEHIGH
				    | CDP_ACTIVEHIGH | MIT_CTO | DW8_1_4BITMODE
				    | MODE_FUNC | STR_BLOCK | HR_NOHOSTRESP
				    | INIT_NOINIT | NOOPENDRAIN;

	mmc_clock_config(mmc, CLK_INITSEQ, 0);
	OMAP_HSMMC_HCTL(mmc->base) |= SDBP_PWRON;

	OMAP_HSMMC_IE(mmc->base) = 0x307f0033;

	mmc_init_stream(mmc);
	return (0);
}

static int
mmc_send_cmd(uint32_t base, uint32_t cmd, uint32_t arg, uint32_t *response)
{
	uint32_t mmc_stat;
	uint32_t cmd_index = cmd >> 24;

	while (1) {
		if ((OMAP_HSMMC_PSTATE(base) & DATI_MASK) != DATI_CMDDIS)
			break;
	}

	OMAP_HSMMC_STAT(base) = 0xFFFFFFFF;
	OMAP_HSMMC_ARG(base) = arg;
	if (cmd_index == 0x19) { /* CMD25: Multi block write */
		OMAP_HSMMC_CMD(base) = cmd | CMD_TYPE_NORMAL | CICE_NOCHECK
				| CCCE_NOCHECK | MSBS | BCE
				| ACEN_DISABLE | DE_DISABLE;
	} else if (cmd_index == 0xC) {
		OMAP_HSMMC_CMD(base) = cmd | 0x3 << 22 | CICE_NOCHECK
				| CCCE_NOCHECK | ACEN_DISABLE
				| BCE_DISABLE | DE_DISABLE;
	} else {
		OMAP_HSMMC_BLK(base) = BLEN_512BYTESLEN | NBLK_STPCNT;
		OMAP_HSMMC_CMD(base) = cmd | CMD_TYPE_NORMAL | CICE_NOCHECK
				| CCCE_NOCHECK | MSBS_SGLEBLK | ACEN_DISABLE
				| BCE_DISABLE | DE_DISABLE;
	}

	while (1) {
		do {
			mmc_stat = OMAP_HSMMC_STAT(base);
		} while (mmc_stat == 0);

		if ((mmc_stat & ERRI_MASK) != 0)
			return (mmc_stat);


		if (mmc_stat & CC_MASK) {
			OMAP_HSMMC_STAT(base) = CC_MASK;
			response[0] = OMAP_HSMMC_RSP10(base);
			if ((cmd & RSP_TYPE_MASK) == RSP_TYPE_LGHT136) {
				response[1] = OMAP_HSMMC_RSP32(base);
				response[2] = OMAP_HSMMC_RSP54(base);
				response[3] = OMAP_HSMMC_RSP76(base);
			}
			break;
		}
	}
	return (0);
}

static int
mmc_read_data(uint32_t base, uint32_t *output_buf)
{
	uint32_t mmc_stat;
	uint32_t read_count = 0;

	/*
	 * Start Polled Read
	 */
	while (1) {
		do {
			mmc_stat = OMAP_HSMMC_STAT(base);
		} while (mmc_stat == 0);

		if ((mmc_stat & ERRI_MASK) != 0)
			return (mmc_stat);

		if (mmc_stat & BRR_MASK) {
			uint32_t k;

			OMAP_HSMMC_STAT(base) |= BRR_MASK;
			for (k = 0; k < MMCSD_SECTOR_SIZE / 4; k++) {
				*output_buf = OMAP_HSMMC_DATA(base);
				output_buf++;
				read_count += 4;
			}
		}

		if (mmc_stat & BWR_MASK)
			OMAP_HSMMC_STAT(base) |= BWR_MASK;

		if (mmc_stat & TC_MASK) {
			OMAP_HSMMC_STAT(base) |= TC_MASK;
			break;
		}
	}
	return (0);
}

static int
mmc_detect_card(struct mmc_card *mmc_card, struct omap_mmc *mmc)
{
	int err;
	uint32_t argument = 0;
	uint32_t ocr_value = 0;
	uint32_t ocr_recvd = 0;
	uint32_t ret_cmd41 = 0;
	uint32_t hcs_val = 0;
	uint32_t resp[4];
	unsigned short retry_cnt = 2000;

	/* Set to Initialization Clock */
	err = mmc_clock_config(mmc, CLK_400KHZ, 0);
	if (err)
		return (err);

	mmc_card->rca = MMC_RELATIVE_CARD_ADDRESS;
	argument = 0x00000000;

	switch (mmc->slot) {
	case 0:
		ocr_value = (0x1FF << 15);
		break;
	case 1:
		ocr_value = 0x80;
		break;
	default:
		printf("mmc_detect_card:Invalid Slot\n");
	}

	err = mmc_send_cmd(mmc->base, MMC_CMD0, argument, resp);
	if (err)
		return (err);

	argument = SD_CMD8_CHECK_PATTERN | SD_CMD8_2_7_3_6_V_RANGE;
	err = mmc_send_cmd(mmc->base, MMC_SDCMD8, argument, resp);
	hcs_val = (err == 0) ?
			MMC_OCR_REG_HOST_CAPACITY_SUPPORT_SECTOR :
			MMC_OCR_REG_HOST_CAPACITY_SUPPORT_BYTE;

	argument = 0x0000 << 16;
	err = mmc_send_cmd(mmc->base, MMC_CMD55, argument, resp);
	if (!err) {
		mmc_card->card_type = SD_CARD;
		ocr_value |= hcs_val;
		ret_cmd41 = MMC_ACMD41;
	} else {
		mmc_card->card_type = MMC_CARD;
		ocr_value |= MMC_OCR_REG_ACCESS_MODE_SECTOR;
		ret_cmd41 = MMC_CMD1;
		OMAP_HSMMC_CON(mmc->base) &= ~OD;
		OMAP_HSMMC_CON(mmc->base) |= OPENDRAIN;
	}

	argument = ocr_value;
	err = mmc_send_cmd(mmc->base, ret_cmd41, argument, resp);
	if (err)
		return (err);

	ocr_recvd = ((mmc_resp_r3 *) resp)->ocr;

	while (!(ocr_recvd & (0x1 << 31)) && (retry_cnt > 0)) {
		retry_cnt--;
		if (mmc_card->card_type == SD_CARD) {
			argument = 0x0000 << 16;
			err = mmc_send_cmd(mmc->base, MMC_CMD55, argument, resp);
		}

		argument = ocr_value;
		err = mmc_send_cmd(mmc->base, ret_cmd41, argument, resp);
		if (err)
			return (err);
		ocr_recvd = ((mmc_resp_r3 *)resp)->ocr;
	}

	if (!(ocr_recvd & (0x1 << 31)))
		return (-1);

	if (mmc_card->card_type == MMC_CARD) {
		if ((ocr_recvd & MMC_OCR_REG_ACCESS_MODE_MASK) ==
				MMC_OCR_REG_ACCESS_MODE_SECTOR) {
			mmc_card->mode = SECTOR_MODE;
		} else {
			mmc_card->mode = BYTE_MODE;
		}

		ocr_recvd &= ~MMC_OCR_REG_ACCESS_MODE_MASK;
	} else {
		if ((ocr_recvd & MMC_OCR_REG_HOST_CAPACITY_SUPPORT_MASK)
		    == MMC_OCR_REG_HOST_CAPACITY_SUPPORT_SECTOR) {
			mmc_card->mode = SECTOR_MODE;
		} else {
			mmc_card->mode = BYTE_MODE;
		}
		ocr_recvd &= ~MMC_OCR_REG_HOST_CAPACITY_SUPPORT_MASK;
	}

	ocr_recvd &= ~(0x1 << 31);
	if (!(ocr_recvd & ocr_value))
		return (-1);

	err = mmc_send_cmd(mmc->base, MMC_CMD2, argument, resp);
	if (err)
		return (err);

	if (mmc_card->card_type == MMC_CARD) {
		argument = mmc_card->rca << 16;
		err = mmc_send_cmd(mmc->base, MMC_CMD3, argument, resp);
		if (err)
			return (err);
	} else {
		argument = 0x00000000;
		err = mmc_send_cmd(mmc->base, MMC_SDCMD3, argument, resp);
		if (err)
			return (err);

		mmc_card->rca = ((mmc_resp_r6 *)resp)->newpublishedrca;
	}

	OMAP_HSMMC_CON(mmc->base) &= ~OD;
	OMAP_HSMMC_CON(mmc->base) |= NOOPENDRAIN;
	return (0);
}

static int
mmc_read_cardsize(uint32_t base, struct mmc_card *mmc_dev_data, mmc_csd_reg_t *cur_csd)
{
	mmc_extended_csd_reg_t ext_csd;
	uint32_t size, count, blk_len, blk_no, card_size, argument;
	int err;
	uint32_t resp[4];

	if (mmc_dev_data->mode == SECTOR_MODE) {
		if (mmc_dev_data->card_type == SD_CARD) {
			card_size = (((mmc_sd2_csd_reg_t *) cur_csd)->c_size_lsb
				& MMC_SD2_CSD_C_SIZE_LSB_MASK)
				| ((((mmc_sd2_csd_reg_t *) cur_csd)->c_size_msb
				& MMC_SD2_CSD_C_SIZE_MSB_MASK)
				<< MMC_SD2_CSD_C_SIZE_MSB_OFFSET);
			mmc_dev_data->size = (card_size + 1) * 1024;
			if (mmc_dev_data->size == 0)
				return (0);
		} else {
			argument = 0x00000000;
			err = mmc_send_cmd(base, MMC_CMD8, argument, resp);
			if (err)
				return (err);
			err = mmc_read_data(base, (uint32_t *)&ext_csd);
			if (err)
				return (err);
			mmc_dev_data->size = ext_csd.sectorcount;

			if (mmc_dev_data->size == 0)
				mmc_dev_data->size = 8388608;
		}
	} else {
		if (cur_csd->c_size_mult >= 8)
			return (-1);

		if (cur_csd->read_bl_len >= 12)
			return (-1);

		/* Compute size */
		count = 1 << (cur_csd->c_size_mult + 2);
		card_size = (cur_csd->c_size_lsb & MMC_CSD_C_SIZE_LSB_MASK)
				| ((cur_csd->c_size_msb & MMC_CSD_C_SIZE_MSB_MASK)
			  	<< MMC_CSD_C_SIZE_MSB_OFFSET);
		blk_no = (card_size + 1) * count;
		blk_len = 1 << cur_csd->read_bl_len;
		size = blk_no * blk_len;
		mmc_dev_data->size = size / MMCSD_SECTOR_SIZE;
		if (mmc_dev_data->size == 0)
			return (-1);
	}
	return (0);
}

int
omap_mmc_read_sect(uint32_t start_sec, uint32_t nbytes, struct omap_mmc *mmc,
		struct mmc_card *mmc_card, uint32_t *output_buf)
{
	int err;
	uint32_t argument;
	uint32_t resp[4];
	uint32_t num_sec_val = (nbytes + (MMCSD_SECTOR_SIZE - 1))
				/ MMCSD_SECTOR_SIZE;
	uint32_t sec_inc_val;

	if (num_sec_val == 0) {
		printf("mmc read: Invalid size\n");
		return (-1);
	}
	if (mmc_card->mode == SECTOR_MODE) {
		argument = start_sec;
		sec_inc_val = 1;
	} else {
		argument = start_sec * MMCSD_SECTOR_SIZE;
		sec_inc_val = MMCSD_SECTOR_SIZE;
	}
	while (num_sec_val) {
		err = mmc_send_cmd(mmc->base, MMC_CMD17, argument, resp);
		if (err)
			return (err);


		err = mmc_read_data(mmc->base, output_buf);
		if (err)
			return (err);

		output_buf += (MMCSD_SECTOR_SIZE / 4);
		argument += sec_inc_val;
		num_sec_val--;
	}
	return (0);
}

int
configure_controller(struct omap_mmc *mmc, int slot)
{
	int ret = 0;

	mmc->slot = slot;
	switch (slot) {
	case 0:
		mmc->base = OMAP_HSMMC1_BASE;
		break;
	case 1:
		mmc->base = OMAP_HSMMC2_BASE;
		break;
	default:
		printf("MMC on SLOT=%d not Supported\n", slot);
		ret = 1;
	}
	return (ret);
}

static int
configure_mmc(struct mmc_card *mmc_card, struct omap_mmc *mmc)
{
	int ret;
	uint32_t argument;
	uint32_t resp[4];
	uint32_t trans_fact, trans_unit, retries = 2;
	uint32_t max_dtr;
	int dsor;
	mmc_csd_reg_t card_csd;
	unsigned char trans_speed;

	ret = mmc_init_setup(mmc);
	if (ret)
		return (ret);


	do {
		ret = mmc_detect_card(mmc_card, mmc);
		retries--;
	} while ((retries > 0) && (ret));

	argument = mmc_card->rca << 16;
	ret = mmc_send_cmd(mmc->base, MMC_CMD9, argument, resp);
	if (ret)
		return (ret);

	((uint32_t *)&card_csd)[3] = resp[3];
	((uint32_t *)&card_csd)[2] = resp[2];
	((uint32_t *)&card_csd)[1] = resp[1];
	((uint32_t *)&card_csd)[0] = resp[0];

	if (mmc_card->card_type == MMC_CARD)
		mmc_card->version = card_csd.spec_vers;

	trans_speed = card_csd.tran_speed;
	ret = mmc_send_cmd(mmc->base, MMC_CMD4, MMC_DSR_DEFAULT << 16, resp);
	if (ret)
		return (ret);

	trans_unit = trans_speed & MMC_CSD_TRAN_SPEED_UNIT_MASK;
	trans_fact = trans_speed & MMC_CSD_TRAN_SPEED_FACTOR_MASK;

	if (trans_unit > MMC_CSD_TRAN_SPEED_UNIT_100MHZ)
		return (-1);

	if ((trans_fact < MMC_CSD_TRAN_SPEED_FACTOR_1_0)
			|| (trans_fact > MMC_CSD_TRAN_SPEED_FACTOR_8_0))
		return (-1);

	trans_unit >>= 0;
	trans_fact >>= 3;

	max_dtr = tran_exp[trans_unit] * tran_mant[trans_fact];
	dsor = OMAP_MMC_MASTER_CLOCK / max_dtr;

	if (OMAP_MMC_MASTER_CLOCK / dsor > max_dtr)
		dsor++;

	ret = mmc_clock_config(mmc, CLK_MISC, dsor);
	if (ret)
		return (ret);

	argument = mmc_card->rca << 16;
	ret = mmc_send_cmd(mmc->base, MMC_CMD7_SELECT, argument, resp);
	if (ret)
		return (ret);

	if (mmc->slot == 1) {
		/* Switch eMMC on OMAP4 to HS timing */
		argument = (MMC_SWITCH_MODE_WRITE_BYTE << 24)
				| (EXT_CSD_HS_TIMING << 16) | (1 << 8)
				| EXT_CSD_CMD_SET_NORMAL;
		ret = mmc_send_cmd(mmc->base, MMC_CMD6, argument, resp);
		if (ret)
			return (ret);

		/* Switch the clock to 48MHz */
		ret = mmc_clock_config(mmc, CLK_MISC, 2);
		if (ret)
			return (ret);
	}

	/* Configure the block length to 512 bytes */
	argument = MMCSD_SECTOR_SIZE;
	ret = mmc_send_cmd(mmc->base, MMC_CMD16, argument, resp);
	if (ret)
		return (ret);

	/* get the card size in sectors */
	ret = mmc_read_cardsize(mmc->base, mmc_card, &card_csd);
	if (ret)
		return (ret);

	if (mmc->slot == 1) {
		/* Switch the eMMC on OMAP4 to 8-bit mode */
		argument = (MMC_SWITCH_MODE_WRITE_BYTE << 24)
			| (EXT_CSD_BUS_WIDTH << 16) | (EXT_CSD_BUS_WIDTH_8 << 8)
			| EXT_CSD_CMD_SET_NORMAL;
		ret = mmc_send_cmd(mmc->base, MMC_CMD6, argument, resp);
		if (ret)
			return (ret);

		OMAP_HSMMC_CON(mmc->base) |= (1 << 5);
	}

	return (0);
}

static unsigned long
mmc_bread(int slot, u_long blknr, u_long blkcnt, u_long *dst)
{
	unsigned long ret;

	ret = (unsigned long)omap_mmc_read_sect(blknr, (blkcnt * MMCSD_SECTOR_SIZE),
			&mmcs[slot], &mmc_cards[slot], (uint32_t *)dst);
	return (ret);
}

int
mmc_init(int slot)
{
	int ret = 0;
	switch (slot) {
	case 0:
		configure_controller(&mmcs[slot], slot);
		ret = configure_mmc(&mmc_cards[slot], &mmcs[slot]);
		break;
	case 1:
		configure_controller(&mmcs[slot], slot);
		ret = configure_mmc(&mmc_cards[slot], &mmcs[slot]);
		break;
	default:
		printf("mmc_init:mmc slot is not supported%d\n", slot);
		return (-1);
	}

	return (0);
}

int
mmc_read(int slot, uint32_t src, unsigned char *dst, int size)
{
	int ret;

	ret = omap_mmc_read_sect(src, size, &mmcs[slot],
			&mmc_cards[slot], (uint32_t *)dst);
	return (ret);
}

