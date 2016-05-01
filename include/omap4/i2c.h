/*-
 * Copyright (c) 2016
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

#ifndef _OMAP4_I2C_H_
#define _OMAP4_I2C_H_

#define I2C_SCLL_SCLL        (0)
#define I2C_SCLL_SCLL_M      (0xff)
#define I2C_SCLL_HSSCLL      (8)
#define I2C_SCLH_HSSCLL_M    (0xff)
#define I2C_SCLH_SCLH        (0)
#define I2C_SCLH_SCLH_M      (0xff)
#define I2C_SCLH_HSSCLH      (8)
#define I2C_SCLH_HSSCLH_M    (0xff)

#define OMAP_I2C_STANDARD          100
#define OMAP_I2C_FAST_MODE         400
#define OMAP_I2C_HIGH_SPEED        3400

#define SYSTEM_CLOCK_12       12000
#define SYSTEM_CLOCK_13       13000
#define SYSTEM_CLOCK_192      19200
#define SYSTEM_CLOCK_96       96000

#define I2C_IP_CLK SYSTEM_CLOCK_96
#define I2C_PSC_MAX          (0x0f)
#define I2C_PSC_MIN          (0x00)

#define	I2C_REG_IE		0x84
#define		I2C_IE_XDR		(1UL << 14)   /* Transmit draining interrupt */
#define		I2C_IE_RDR		(1UL << 13)   /* Receive draining interrupt */
#define		I2C_IE_AAS		(1UL << 9)    /* Addressed as Slave interrupt */
#define		I2C_IE_BF		(1UL << 8)    /* Bus Free interrupt */
#define		I2C_IE_AERR		(1UL << 7)    /* Access Error interrupt */
#define		I2C_IE_STC		(1UL << 6)    /* Start Condition interrupt */
#define		I2C_IE_GC		(1UL << 5)    /* General Call interrupt */
#define		I2C_IE_XRDY		(1UL << 4)    /* Transmit Data Ready interrupt */
#define		I2C_IE_RRDY		(1UL << 3)    /* Receive Data Ready interrupt */
#define		I2C_IE_ARDY		(1UL << 2)    /* Register Access Ready interrupt */
#define		I2C_IE_NACK		(1UL << 1)    /* No Acknowledgment interrupt */
#define		I2C_IE_AL		(1UL << 0)    /* Arbitration Lost interrupt */
#define	I2C_REG_STAT		0x88
#define		I2C_STAT_XDR		(1UL << 14)
#define		I2C_STAT_RDR		(1UL << 13)
#define		I2C_STAT_BB		(1UL << 12)
#define		I2C_STAT_ROVR		(1UL << 11)
#define		I2C_STAT_XUDF		(1UL << 10)
#define		I2C_STAT_AAS		(1UL << 9)
#define		I2C_STAT_BF		(1UL << 8)
#define		I2C_STAT_AERR		(1UL << 7)
#define		I2C_STAT_STC		(1UL << 6)
#define		I2C_STAT_GC		(1UL << 5)
#define		I2C_STAT_XRDY		(1UL << 4)
#define		I2C_STAT_RRDY		(1UL << 3)
#define		I2C_STAT_ARDY		(1UL << 2)
#define		I2C_STAT_NACK		(1UL << 1)
#define		I2C_STAT_AL		(1UL << 0)
#define	I2C_REG_SYSS		0x90
#define		I2C_SYSS_RDONE		(1UL << 0)
#define	I2C_REG_BUF		0x94
#define		I2C_BUF_RXFIFO_CLR	(1UL << 14)
#define		I2C_BUF_TXFIFO_CLR	(1UL << 6)
#define		I2C_BUF_RXTRSH_SHIFT	8
#define		I2C_BUF_TRSH_MASK	0x3f
#define	I2C_REG_CNT		0x98
#define	I2C_REG_DATA		0x9c
#define	I2C_REG_CON		0xa4
#define		I2C_CON_I2C_EN		(1UL << 15)
#define		I2C_CON_OPMODE_STD	(0UL << 12)
#define		I2C_CON_OPMODE_HS	(1UL << 12)
#define		I2C_CON_OPMODE_SCCB	(2UL << 12)
#define		I2C_CON_OPMODE_MASK	(3UL << 13)
#define		I2C_CON_I2C_STB		(1UL << 11)
#define		I2C_CON_MST		(1UL << 10)
#define		I2C_CON_TRX		(1UL << 9)
#define		I2C_CON_XSA		(1UL << 8)
#define		I2C_CON_XOA0		(1UL << 7)
#define		I2C_CON_XOA1		(1UL << 6)
#define		I2C_CON_XOA2		(1UL << 5)
#define		I2C_CON_XOA3		(1UL << 4)
#define		I2C_CON_STP		(1UL << 1)
#define		I2C_CON_STT		(1UL << 0)
#define	I2C_REG_OA0		0xa8
#define	I2C_REG_SA		0xac
#define	I2C_REG_PSC		0xb0
#define		I2C_PSC_MASK		0xff
#define	I2C_REG_SCLL		0xb4
#define		I2C_SCLL_MASK		0xff
#define		I2C_HSSCLL_SHIFT	8
#define	I2C_REG_SCLH		0xb8
#define		I2C_SCLH_MASK		0xff
#define		I2C_HSSCLH_SHIFT	8
#define	I2C_REG_SYSTEST		0xbc
#define	I2C_REG_BUFSTAT		0xc0
#define		I2C_BUFSTAT_FIFODEPTH_MASK	0x3
#define		I2C_BUFSTAT_FIFODEPTH_SHIFT	14
#define	I2C_REG_OA1		0xc4
#define	I2C_REG_OA2		0xc8
#define	I2C_REG_OA3		0xcc
#define	I2C_REG_ACTOA		0xd0
#define	I2C_REG_SBLOCK		0xd4

#define	I2C_REG_REVNB_LO	0x00
#define	I2C_REG_REVNB_HI	0x04
#define	I2C_REG_SYSC		0x10
#define		I2C_SYSC_SRST	(1UL << 1)
#define	I2C_REG_STATUS_RAW	0x24
#define	I2C_REG_STATUS		0x28
#define	I2C_REG_IRQENABLE_SET	0x2C
#define	I2C_REG_IRQENABLE_CLR	0x30

#define	I2C_CLK			96000000UL	/* 96MHz */
#define	I2C_ICLK		12000000UL	/* 12MHz */

struct i2c {
	unsigned short revnb_lo;	/* 0x00 */
	unsigned short res1;
	unsigned short revnb_hi;	/* 0x04 */
	unsigned short res2[5];
	unsigned short sysc;		/* 0x10 */
	unsigned short res3[9];
	unsigned short irqstatus_raw;	/* 0x24 */
	unsigned short res4;
	unsigned short irqstatus;	/* 0x28 */
	unsigned short res5;
	unsigned short irqenable_set;	/* 0x2c */
	unsigned short res6;
	unsigned short irqenable_clr;	/* 0x30 */
	unsigned short res7;
	unsigned short we;		/* 0x34 */
	unsigned short res8;
	unsigned short dmarxenable_set;	/* 0x38 */
	unsigned short res9;
	unsigned short dmatxenable_set;	/* 0x3c */
	unsigned short res10;
	unsigned short dmarxenable_clr;	/* 0x40 */
	unsigned short res11;
	unsigned short dmatxenable_clr;	/* 0x44 */
	unsigned short res12;
	unsigned short dmarxwake_en;	/* 0x48 */
	unsigned short res13;
	unsigned short dmatxwake_en;	/* 0x4c */
	unsigned short res14[27];
	unsigned short ie;		/* 0x84 */
	unsigned short res15;
	unsigned short stat;		/* 0x88 */
	unsigned short res16[3];
	unsigned short syss;		/* 0x90 */
	unsigned short res17;
	unsigned short buf;		/* 0x94 */
	unsigned short res18;
	unsigned short cnt;		/* 0x98 */
	unsigned short res19;
	unsigned short data;		/* 0x9c */
	unsigned short res20[3];
	unsigned short con;		/* 0xa4 */
	unsigned short res21;
	unsigned short oa;		/* 0xa8 */
	unsigned short res22;
	unsigned short sa;		/* 0xac */
	unsigned short res23;
	unsigned short psc;		/* 0xb0 */
	unsigned short res24;
	unsigned short scll;		/* 0xb4 */
	unsigned short res26;
	unsigned short sclh;		/* 0xb8 */
	unsigned short res27;
	unsigned short systest;		/* 0xbC */
	unsigned short res28;
	unsigned short bufstat;		/* 0xc0 */
	unsigned short res29;
	unsigned short oa1;		/* 0xc4 */
	unsigned short res30;
	unsigned short oa2;		/* 0xc8 */
	unsigned short res31;
	unsigned short oa3;		/* 0xcc */
	unsigned short res32;
	unsigned short actoa;		/* 0xd0 */
	unsigned short res33;
	unsigned short sblock;		/* 0xd4 */
};

#endif /* !_OMAP4_I2C_H_ */
