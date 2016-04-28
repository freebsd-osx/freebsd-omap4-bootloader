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

#include <boot.h>
#include <io.h>
#include <mmc.h>

#include <omap4/hw.h>
#include <omap4/mmchs.h>
#include <omap4/timer.h>

#include "util.h"

#define MAX_RETRY_MS	1000
#define OMAP_MMC_MASTER_CLOCK   96000000

static struct mmc mmc;

static int
mmc_vmmc_pbias_config(void)
{
	uint32_t value = 0;

        value = readl(CONTROL_PBIASLITE);
        value = value | (1 << 22) | (1 << 26);
        writel(value, CONTROL_PBIASLITE);

        value = readl(CONTROL_CONF_MMC1);
        value = value | (1 << 31) | (1 << 30) | (1 << 27) |
			(1 << 26) | (1 << 25);
        writel(value, CONTROL_CONF_MMC1);

	return (0);
}

static void
mmc_init_stream(struct mmchs *mmc_base)
{
	u_long start;

	writel(readl(&mmc_base->con) | INIT_INITSTREAM, &mmc_base->con);

	writel(MMC_CMD0, &mmc_base->cmd);
	start = get_timer(0);
	while (!(readl(&mmc_base->stat) & CC_MASK)) {
		if (get_timer(0) - start > MAX_RETRY_MS) {
			printf("%s: timedout waiting for cc!\n", __func__);
			return;
		}
	}

	writel(CC_MASK, &mmc_base->stat);
	writel(MMC_CMD0, &mmc_base->cmd);
	start = get_timer(0);
	while (!(readl(&mmc_base->stat) & CC_MASK)) {
		if (get_timer(0) - start > MAX_RETRY_MS) {
			printf("%s: timedout waiting for cc!\n", __func__);
			return;
		}
	}
	writel(readl(&mmc_base->con) & ~INIT_INITSTREAM, &mmc_base->con);
}

static int
mmc_clock_config(struct mmchs *mmc_base, uint32_t iclk, unsigned short clk_div)
{
	uint32_t val;
	u_long start;

	mmc_reg_out(&mmc_base->sysctl,
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
	mmc_reg_out(&mmc_base->sysctl, ICE_MASK | CLKD_MASK,
	    (val << CLKD_OFFSET) | ICE_OSCILLATE);

	start = get_timer(0);
	while ((readl(&mmc_base->sysctl) & ICS_MASK) == ICS_NOTREADY) {
		if (get_timer(0) - start > MAX_RETRY_MS) {
			printf("%s: timedout waiting for ics!\n", __func__);
			return (-1);
		}
	}

	writel(readl(&mmc_base->sysctl) | CEN_ENABLE, &mmc_base->sysctl);
	return (0);
}

static int
mmc_hw_init(struct mmchs *mmc_base)
{
	uint32_t reg_val;
	u_long start;

	if (mmc.slot == 0)
		mmc_vmmc_pbias_config();

	writel(readl(&mmc_base->sysconfig) | SOFTRESET, &mmc_base->sysconfig);
	start = get_timer(0);
	while ((readl(&mmc_base->sysstatus) & RESETDONE) == 0) {
		if (get_timer(0) - start > MAX_RETRY_MS) {
			printf("%s: timedout waiting for resetdone\n", __func__);
			return (-1);
		}
	}

	writel(readl(&mmc_base->sysctl) | SOFTRESETALL, &mmc_base->sysctl);
	start = get_timer(0);
	while ((readl(&mmc_base->sysctl) & SOFTRESETALL) != 0) {
		if (get_timer(0) - start > MAX_RETRY_MS) {
			printf("%s: timedout waiting for softresetall\n", __func__);
			return (-1);
		}
	}
	writel(DTW_1_BITMODE | SDBP_PWROFF | SDVS_3V0, &mmc_base->hctl);
	writel(readl(&mmc_base->capa) | VS30_3V0SUP | VS18_1V8SUP, &mmc_base->capa);

	reg_val = readl(&mmc_base->con) & RESERVED_MASK;

	writel(reg_val | CTPL_MMC_SD | WPP_ACTIVEHIGH | CDP_ACTIVEHIGH |
	    MIT_CTO | DW8_1_4BITMODE | MODE_FUNC | STR_BLOCK |
	    HR_NOHOSTRESP | INIT_NOINIT | NOOPENDRAIN, &mmc_base->con);

	mmc_clock_config(mmc_base, CLK_INITSEQ, 0);
	writel(readl(&mmc_base->hctl) | SDBP_PWRON, &mmc_base->hctl);

	writel(IE_BADA | IE_CERR | IE_DEB | IE_DCRC | IE_DTO | IE_CIE |
	    IE_CEB | IE_CCRC | IE_CTO | IE_BRR | IE_BWR | IE_TC | IE_CC,
	    &mmc_base->ie);

	mmc_init_stream(mmc_base);
	return (0);
}

static int
mmc_send_cmd(struct mmchs *mmc_base, uint32_t cmd, uint32_t arg, uint32_t *resp)
{
	uint32_t mmc_stat;
	uint32_t cmd_index = cmd >> 24;
	u_long start;

	start = get_timer(0);
	while ((readl(&mmc_base->pstate) & DATI_MASK) == DATI_CMDDIS) {
		if (get_timer(0) - start > MAX_RETRY_MS) {
			printf("%s: timedout waiting for dati!\n", __func__);
			return (-1);
		}
	}

	writel(0xffffffff, &mmc_base->stat);
	writel(arg, &mmc_base->arg);
	if (cmd_index == 0x19) { /* CMD25: Multi block write */
		writel(cmd | CMD_TYPE_NORMAL | CICE_NOCHECK |
		    CCCE_NOCHECK | MSBS_MULTIBLK | BCE_ENABLE |
		    ACEN_DISABLE | DE_DISABLE,
		    &mmc_base->cmd);
	} else if (cmd_index == 0xC) {
		writel(cmd | 0x3 << 22 | CICE_NOCHECK | CCCE_NOCHECK |
		    ACEN_DISABLE | BCE_DISABLE | DE_DISABLE,
		    &mmc_base->cmd);
	} else {
		writel(BLEN_512BYTESLEN | NBLK_STPCNT, &mmc_base->blk);
		writel(cmd | CMD_TYPE_NORMAL | CICE_NOCHECK |
		   CCCE_NOCHECK | MSBS_SGLEBLK | ACEN_DISABLE |
		   BCE_DISABLE | DE_DISABLE, &mmc_base->cmd);
	}

	while (1) {
		start = get_timer(0);
		do {
			mmc_stat = readl(&mmc_base->stat);
			if (get_timer(0) - start > MAX_RETRY_MS) {
				printf("%s : timeout: No status update\n", __func__);
				return (-1);
			}
		} while (mmc_stat == 0);

		if ((mmc_stat & ERRI_MASK) != 0)
			return (mmc_stat);


		if (mmc_stat & CC_MASK) {
			writel(CC_MASK, &mmc_base->stat);
			resp[0] = readl(&mmc_base->rsp10);
			if ((cmd & RSP_TYPE_MASK) == RSP_TYPE_LGHT136) {
				resp[1] = readl(&mmc_base->rsp32);
				resp[2] = readl(&mmc_base->rsp54);
				resp[3] = readl(&mmc_base->rsp76);
			}
			break;
		}
	}
	return (0);
}

static int
mmc_read_data(struct mmchs *mmc_base, u_long *buf)
{
	uint32_t mmc_stat;
	uint32_t count = 0;

	while (1) {
		u_long start = get_timer(0);
		do {
			mmc_stat = readl(&mmc_base->stat);
			if (get_timer(0) - start > MAX_RETRY_MS) {
				printf("%s: timedout waiting for status!\n", __func__);
				return (-1);
			}
		} while (mmc_stat == 0);

		if ((mmc_stat & ERRI_MASK) != 0)
			return (mmc_stat);

		if (mmc_stat & BRR_MASK) {
			uint32_t k;

			writel(readl(&mmc_base->stat) | BRR_MASK, &mmc_base->stat);
			for (k = 0; k < MMCSD_SECTOR_SIZE / 4; k++) {
				*buf = readl(&mmc_base->data);
				buf++;
				count += 4;
			}
		}

		if (mmc_stat & BWR_MASK)
			writel(readl(&mmc_base->stat) | BWR_MASK, &mmc_base->stat);

		if (mmc_stat & TC_MASK) {
			writel(readl(&mmc_base->stat) | TC_MASK, &mmc_base->stat);
			break;
		}
	}
	return (0);
}

static int
write_data(struct mmchs *mmc_base, u_long *src)
{
	uint32_t mmc_stat;
	int count = 0;
	u_long start;

	/*
	 * Start Polled Write
	 */
	while (1) {
		start = get_timer(0);
		do {
			mmc_stat = readl(&mmc_base->stat);
			if (get_timer(0) - start > MAX_RETRY_MS) {
				printf("%s: timedout waiting for status!\n",
				    __func__);
				return (-1);
			}
		} while (mmc_stat == 0);

		if ((mmc_stat & ERRI_MASK) != 0) {
			printf("mmc write error %08x\n", mmc_stat);
			return (-1);
		}

		if (mmc_stat & BWR_MASK) {
			uint32_t k;

			writel(readl(&mmc_base->stat) | BWR_MASK, &mmc_base->stat);
			for (k = 0; k < MMCSD_SECTOR_SIZE / 4; k++) {
				writel(*src, &mmc_base->data);
				src++;
			}
			count++;
		}

		if (mmc_stat & BRR_MASK)
			writel(readl(&mmc_base->stat) | BRR_MASK, &mmc_base->stat);

		if (mmc_stat & TC_MASK) {
			writel(readl(&mmc_base->stat) | TC_MASK, &mmc_base->stat);
			break;
		}
	}
	return (count);
}

static int
mmc_detect_card(struct mmchs *mmc_base)
{
	int err;
	uint32_t arg = 0;
	uint32_t ocr_value = 0;
	uint32_t ocr_recvd = 0;
	uint32_t ret_cmd41 = 0;
	uint32_t hcs_val = 0;
	uint32_t resp[4];
	unsigned short retry_cnt = 2000;

	err = mmc_clock_config(mmc_base, CLK_400KHZ, 0);
	if (err)
		return (err);

	mmc.rca = MMC_RELATIVE_CARD_ADDRESS;
	arg = 0x00000000;

	switch (mmc.slot) {
	case 0:
		ocr_value = (0x1FF << 15);
		break;
	case 1:
		ocr_value = 0x80;
		break;
	default:
		printf("mmc_detect_card: invalid slot\n");
	}

	err = mmc_send_cmd(mmc_base, MMC_CMD0, arg, resp);
	if (err)
		return (err);

	arg = SD_CMD8_CHECK_PATTERN | SD_CMD8_2_7_3_6_V_RANGE;
	err = mmc_send_cmd(mmc_base, MMC_SDCMD8, arg, resp);
	hcs_val = (err == 0) ?
	    MMC_OCR_REG_HOST_CAPACITY_SUPPORT_SECTOR :
	    MMC_OCR_REG_HOST_CAPACITY_SUPPORT_BYTE;

	arg = 0x0000 << 16;
	err = mmc_send_cmd(mmc_base, MMC_CMD55, arg, resp);
	if (!err) {
		mmc.type = SD_CARD;
		ocr_value |= hcs_val;
		ret_cmd41 = MMC_ACMD41;
	} else {
		mmc.type = MMC_CARD;
		ocr_value |= MMC_OCR_REG_ACCESS_MODE_SECTOR;
		ret_cmd41 = MMC_CMD1;
		writel(readl(&mmc_base->con) & ~OD, &mmc_base->con);
		writel(readl(&mmc_base->con) & OPENDRAIN, &mmc_base->con);
	}

	arg = ocr_value;
	err = mmc_send_cmd(mmc_base, ret_cmd41, arg, resp);
	if (err)
		return (err);

	ocr_recvd = ((struct mmc_resp_r3 *)resp)->ocr;

	while (!(ocr_recvd & (0x1 << 31)) && (retry_cnt > 0)) {
		retry_cnt--;
		if (mmc.type == SD_CARD) {
			arg = 0x0000 << 16;
			err = mmc_send_cmd(mmc_base, MMC_CMD55, arg, resp);
		}

		arg = ocr_value;
		err = mmc_send_cmd(mmc_base, ret_cmd41, arg, resp);
		if (err)
			return (err);
		ocr_recvd = ((struct mmc_resp_r3 *)resp)->ocr;
	}

	if (!(ocr_recvd & (0x1 << 31)))
		return (-1);

	if (mmc.type == MMC_CARD) {
		if ((ocr_recvd & MMC_OCR_REG_ACCESS_MODE_MASK) ==
		    MMC_OCR_REG_ACCESS_MODE_SECTOR) {
			mmc.mode = SECTOR_MODE;
		} else {
			mmc.mode = BYTE_MODE;
		}

		ocr_recvd &= ~MMC_OCR_REG_ACCESS_MODE_MASK;
	} else {
		if ((ocr_recvd & MMC_OCR_REG_HOST_CAPACITY_SUPPORT_MASK) ==
		    MMC_OCR_REG_HOST_CAPACITY_SUPPORT_SECTOR) {
			mmc.mode = SECTOR_MODE;
		} else {
			mmc.mode = BYTE_MODE;
		}
		ocr_recvd &= ~MMC_OCR_REG_HOST_CAPACITY_SUPPORT_MASK;
	}

	ocr_recvd &= ~(0x1 << 31);
	if (!(ocr_recvd & ocr_value))
		return (-1);

	err = mmc_send_cmd(mmc_base, MMC_CMD2, arg, resp);
	if (err)
		return (err);

	if (mmc.type == MMC_CARD) {
		arg = mmc.rca << 16;
		err = mmc_send_cmd(mmc_base, MMC_CMD3, arg, resp);
		if (err)
			return (err);
	} else {
		arg = 0x00000000;
		err = mmc_send_cmd(mmc_base, MMC_SDCMD3, arg, resp);
		if (err)
			return (err);

		mmc.rca = ((struct mmc_resp_r6 *)resp)->newpublishedrca;
	}

	writel(readl(&mmc_base->con) & ~OD, &mmc_base->con);
	writel(readl(&mmc_base->con) | NOOPENDRAIN, &mmc_base->con);
	return (0);
}

static int
mmc_read_cardsize(struct mmchs *mmc_base, struct mmc_csd *csd)
{
	struct mmc_extended_csd ext_csd;
	uint32_t size, count, blk_len, blk_no, card_size, arg;
	int err;
	uint32_t resp[4];

	if (mmc.mode == SECTOR_MODE) {
		if (mmc.type == SD_CARD) {
			card_size = (((struct mmc_sd2_csd *)csd)->c_size_lsb &
			    MMC_SD2_CSD_C_SIZE_LSB_MASK) |
			    ((((struct mmc_sd2_csd *)csd)->c_size_msb &
			    MMC_SD2_CSD_C_SIZE_MSB_MASK) << MMC_SD2_CSD_C_SIZE_MSB_OFFSET);
			mmc.size = (card_size + 1) * 1024;
			if (mmc.size == 0)
				return (0);
		} else {
			arg = 0x00000000;
			err = mmc_send_cmd(mmc_base, MMC_CMD8, arg, resp);
			if (err)
				return (err);
			err = mmc_read_data(mmc_base, (u_long *)&ext_csd);
			if (err)
				return (err);
			mmc.size = ext_csd.sectorcount;

			if (mmc.size == 0)
				mmc.size = 8388608;
		}
	} else {
		if (csd->c_size_mult >= 8)
			return (-1);

		if (csd->read_bl_len >= 12)
			return (-1);

		/* Compute size */
		count = 1 << (csd->c_size_mult + 2);
		card_size = (csd->c_size_lsb & MMC_CSD_C_SIZE_LSB_MASK) |
		    ((csd->c_size_msb & MMC_CSD_C_SIZE_MSB_MASK) <<
		    MMC_CSD_C_SIZE_MSB_OFFSET);
		blk_no = (card_size + 1) * count;
		blk_len = 1 << csd->read_bl_len;
		size = blk_no * blk_len;
		mmc.size = size / MMCSD_SECTOR_SIZE;
		if (mmc.size == 0)
			return (-1);
	}
	return (0);
}

static int
read_sector(struct mmchs *mmc_base, u_long *buf, u_long start, unsigned nbytes)
{
	int err;
	uint32_t arg;
	uint32_t resp[4];
	uint32_t nsectors = (nbytes + (MMCSD_SECTOR_SIZE - 1)) /
	    MMCSD_SECTOR_SIZE;
	uint32_t sector_inc;

	if (nsectors == 0) {
		printf("%s: invalid size\n", __func__);
		return (-1);
	}
	if (mmc.mode == SECTOR_MODE) {
		arg = start;
		sector_inc = 1;
	} else {
		arg = start * MMCSD_SECTOR_SIZE;
		sector_inc = MMCSD_SECTOR_SIZE;
	}
	while (nsectors) {
		err = mmc_send_cmd(mmc_base, MMC_CMD17, arg, resp);
		if (err)
			return (err);

		err = mmc_read_data(mmc_base, buf);
		if (err)
			return (err);

		buf += (MMCSD_SECTOR_SIZE / 4);
		arg += sector_inc;
		nsectors--;
	}
	return (arg - start);
}

static int
write_sector(struct mmchs *mmc_base, u_long *src, u_long start, uint32_t nbytes)
{
	uint8_t err;
	uint32_t arg;
	uint32_t resp[4];
	uint32_t nsectors = 0;
	uint32_t sector_inc;
	uint32_t blkcnt;
	int r;

	nsectors = (nbytes + (MMCSD_SECTOR_SIZE - 1)) / MMCSD_SECTOR_SIZE;
	if (nsectors == 0) {
		printf("mmc write: invalid size\n");
		return (-1);
	}

	if (mmc.mode == SECTOR_MODE) {
		arg = start;
		sector_inc = 1;
	} else {
		arg = start * MMCSD_SECTOR_SIZE;
		sector_inc = MMCSD_SECTOR_SIZE;
	}

	while (nsectors) {
		if (nsectors > 0xFFFF)
			/* Max number of blocks per cmd */
			blkcnt = 0xFFFF;
		else
			blkcnt = nsectors;

		/* check for Multi Block */
		if (blkcnt > 1) {
			if (mmc.slot == 1) {
				err = mmc_send_cmd(mmc_base, MMC_CMD23,
				    blkcnt, resp);
				if (err)
					return (err);
			}
			writel(BLEN_512BYTESLEN | (blkcnt << 16), &mmc_base->blk);
			err = mmc_send_cmd(mmc_base, MMC_CMD25, arg, resp);
			if (err)
				return (err);
		} else {
			err = mmc_send_cmd(mmc_base, MMC_CMD24, arg, resp);
			if (err)
				return (err);
		}
		r = write_data(mmc_base, src);
		if (r < 0)
			return (-1);
		blkcnt = r;

		if (mmc.slot == 0) {
			if (blkcnt > 1) {
				err = mmc_send_cmd(mmc_base, MMC_CMD12, 0, resp);
				if (err) {
					printf("MMC_CMD12 failed 0x%x\n", err);
					return (err);
				}
			}
			while (1){
				arg = mmc.rca << 16;
				err = mmc_send_cmd(mmc_base,
				    MMC_CMD13, arg, resp);
				if (err){
					printf("MMC_CMD13 Failed. Try again \n");
					udelay(100000);
					continue;
				}
				if (resp[0] & MMC_READY_FOR_DATA)
					break;
				else {
					printf("Card not ready for data yet.. waiting..");
					udelay(100000);
				}
			}
		}

		src += (MMCSD_SECTOR_SIZE / 4) * blkcnt;
		arg += sector_inc * blkcnt;
		nsectors -= blkcnt;
	}
	return (0);
}

static int
erase_sector(struct mmchs *mmc_base, uint32_t start, int size)
{
	int err;
	uint32_t arg;
	uint32_t nsectors;
	uint32_t sector_inc;
	uint32_t resp[4];
	uint32_t mmc_stat;
	uint32_t blkcnt;

	if ((start / MMCSD_SECTOR_SIZE) > mmc.size ||
	    ((start + size) / MMCSD_SECTOR_SIZE) > mmc.size) {
		printf("mmc erase: erase to Sector is\n"
		   "out of card range\n");
		return (-1);
	}
	nsectors = (size+ (MMCSD_SECTOR_SIZE - 1)) / MMCSD_SECTOR_SIZE;
	if (mmc.mode == SECTOR_MODE) {
		arg = start;
		sector_inc = 1;
	} else {
		arg = start * MMCSD_SECTOR_SIZE;
		sector_inc = MMCSD_SECTOR_SIZE;
	}
	while (nsectors) {
		if (nsectors > 0xFFFF)
			blkcnt = 0xFFFF;
		else
			blkcnt = nsectors;

		/* check for Multi Block */
		if (blkcnt > 1) {
			writel(BLEN_512BYTESLEN | (blkcnt << 16), &mmc_base->blk);
			err = mmc_send_cmd(mmc_base, MMC_CMD25, arg, resp);
			if (err)
				return (err);

		} else {
			err = mmc_send_cmd(mmc_base, MMC_CMD24, arg, resp);
			if (err)
				return (err);
		}
		while (1) {
			u_long begin = get_timer(0);
			do {
				mmc_stat = readl(&mmc_base->stat);
				if (get_timer(0) - begin > MAX_RETRY_MS) {
					printf("%s: timedout waiting for status!\n",
					    __func__);
					return (-1);
				}
			} while (mmc_stat == 0);

			if ((mmc_stat & ERRI_MASK) != 0)
				return (mmc_stat);

			if (mmc_stat & BWR_MASK) {
				uint32_t k;

				writel(readl(&mmc_base->stat) | BWR_MASK, &mmc_base->stat);
				for (k = 0; k < MMCSD_SECTOR_SIZE / 4; k++) {
					writel(0xffffffff, &mmc_base->data);
				}
			}

			if (mmc_stat & BRR_MASK)
				writel(readl(&mmc_base->stat) | BRR_MASK, &mmc_base->stat);

			if (mmc_stat & TC_MASK) {
				writel(readl(&mmc_base->stat) | TC_MASK, &mmc_base->stat);
				break;
			}
		}

		if (blkcnt > 1) {
			err = mmc_send_cmd(mmc_base, MMC_CMD12, 0, resp);

			if (err) {
				printf("MMC_CMD12 failed 0x%x\n", err);
				return (err);
			}
		}

		arg += sector_inc * blkcnt;
		nsectors -= blkcnt;
	}
	return (0);
}

static int
mmc_config(struct mmchs *mmc_base)
{
	int ret;
	uint32_t arg;
	uint32_t resp[4];
	uint32_t trans_fact, trans_unit, retries = 2;
	uint32_t max_dtr;
	int dsor;
	struct mmc_csd csd;
	uint8_t trans_speed;

	ret = mmc_hw_init(mmc_base);
	if (ret)
		return (ret);

	do {
		ret = mmc_detect_card(mmc.host);
		--retries;
	} while ((retries > 0) && (ret));

	arg = mmc.rca << 16;
	ret = mmc_send_cmd(mmc_base, MMC_CMD9, arg, resp);

	if (ret)
		return (ret);

	((uint32_t *)&csd)[3] = resp[3];
	((uint32_t *)&csd)[2] = resp[2];
	((uint32_t *)&csd)[1] = resp[1];
	((uint32_t *)&csd)[0] = resp[0];

	if (mmc.type == MMC_CARD)
		mmc.version = csd.spec_vers;

	trans_speed = csd.tran_speed;
	ret = mmc_send_cmd(mmc_base, MMC_CMD4, MMC_DSR_DEFAULT << 16, resp);
	if (ret)
		return (ret);

	trans_unit = trans_speed & MMC_CSD_TRAN_SPEED_UNIT_MASK;
	trans_fact = trans_speed & MMC_CSD_TRAN_SPEED_FACTOR_MASK;

	if (trans_unit > MMC_CSD_TRAN_SPEED_UNIT_100MHZ)
		return (-1);

	if ((trans_fact < MMC_CSD_TRAN_SPEED_FACTOR_1_0) ||
	    (trans_fact > MMC_CSD_TRAN_SPEED_FACTOR_8_0))
		return (-1);

	trans_unit >>= 0;
	trans_fact >>= 3;

	max_dtr = tran_exp[trans_unit] * tran_mant[trans_fact];
	dsor = OMAP_MMC_MASTER_CLOCK / max_dtr;

	if (OMAP_MMC_MASTER_CLOCK / dsor > max_dtr)
		dsor++;

	ret = mmc_clock_config(mmc_base, CLK_MISC, dsor);
	if (ret)
		return (ret);

	arg = mmc.rca << 16;
	ret = mmc_send_cmd(mmc_base, MMC_CMD7_SELECT, arg, resp);
	if (ret)
		return (ret);

	if (mmc.slot == 1) {
		/* Switch eMMC on OMAP4 to HS timing */
		arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
			(EXT_CSD_HS_TIMING << 16) |
			(1 << 8) |
			EXT_CSD_CMD_SET_NORMAL;
		ret = mmc_send_cmd(mmc_base, MMC_CMD6, arg, resp);
		if (ret)
			return (ret);

		/* Switch the clock to 48MHz */
		ret = mmc_clock_config(mmc_base, CLK_MISC, 2);
		if (ret)
			return (ret);
	}

	/* Configure the block length to 512 bytes */
	arg = MMCSD_SECTOR_SIZE;
	ret = mmc_send_cmd(mmc_base, MMC_CMD16, arg, resp);
	if (ret)
		return (ret);

	/* get the card size in sectors */
	ret = mmc_read_cardsize(mmc_base, &csd);
	if (ret)
		return (ret);

	if (mmc.slot == 1) {
		/* Switch the eMMC on OMAP4 to 8-bit mode */
		arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
		    (EXT_CSD_BUS_WIDTH << 16) |
		    (EXT_CSD_BUS_WIDTH_8 << 8) |
		    EXT_CSD_CMD_SET_NORMAL;
		ret = mmc_send_cmd(mmc_base, MMC_CMD6, arg, resp);
		if (ret)
			return (ret);

		writel(readl(&mmc_base->con) | (1 << 5), &mmc_base->con);
	}

	return (0);
}

int
mmc_init(int slot)
{
	int ret;

	switch (slot) {
	case 0:
		mmc.host = (struct mmchs *)OMAP_HSMMC1_BASE;
		break;
	case 1:
		mmc.host = (struct mmchs *)OMAP_HSMMC2_BASE;
		break;
	default:
		printf("slot%d is not Supported\n", slot);
		return (-1);
	}

	mmc.slot = slot;
	ret = mmc_config(mmc.host);

	return (0);
}

u_long
mmc_read(u_long *dst, u_long start, unsigned size)
{
	u_long ret;

	ret = read_sector(mmc.host, dst, start, size);
	return (ret);
}

u_long
mmc_bread(u_long *dst, u_long start, unsigned nblk)
{
	u_long ret;

	ret = read_sector(mmc.host, dst, start,
	    (nblk * MMCSD_SECTOR_SIZE));
	return (ret);
}

int
mmc_write(u_long *src, u_long start, unsigned size)
{
	int ret;

	ret = write_sector(mmc.host, src, start, size);
	return (ret);
}

int
mmc_erase(u_long start, unsigned size)
{
	int ret;

	ret = erase_sector(mmc.host, start, size);
	return (ret);
}

uint32_t
mmc_size(void)
{
	return (mmc.size);
}
