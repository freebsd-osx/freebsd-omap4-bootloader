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

#include <sys/types.h>

#include <boot.h>
#include <io.h>

#include <omap4/hw.h>
#include <omap4/i2c.h>
#include <omap4/timer.h>

#include "util.h"

#define I2C_TIMEOUT	1000

static struct i2c *i2c_base;
static uint32_t i2c_speed;

static void
wait_for_bb(void)
{
	uint16_t status;
	int timeout = I2C_TIMEOUT;

	writew(0xffff, &i2c_base->stat);	/* clear current interruts... */
	while ((status = readw(&i2c_base->stat) &
	    I2C_STAT_BB) && timeout--) {
		writew(status, &i2c_base->stat);
		udelay(50000);
	}

	if (timeout <= 0) {
		debug("timed out in wait_for_bb: I2C_STAT=%x\n",
		       readw(&i2c_base->stat));
	}
	writew(0xffff, &i2c_base->stat);	/* clear delayed stuff */
}

static uint16_t
wait_for_pin(void)
{
	uint16_t status;
	int timeout = I2C_TIMEOUT;

	do {
		udelay(1000);
		status = readw(&i2c_base->stat);
	} while (!(status & (I2C_STAT_ROVR |
	    I2C_STAT_XUDF | I2C_STAT_XRDY |
	    I2C_STAT_RRDY | I2C_STAT_ARDY | I2C_STAT_NACK |
    	    I2C_STAT_AL)) && timeout--);

	if (timeout <= 0) {
		debug("timed out in wait_for_pin: I2C_STAT=%x\n",
		    readw(&i2c_base->stat));
		writew(0xffff, &i2c_base->stat);
	}
	return (status);
}

static void
flush_fifo(void)
{
	uint16_t status;

	while (1) {
		status = readw(&i2c_base->stat);
		if (status == I2C_STAT_RRDY) {
			readb(&i2c_base->data);
			writew(I2C_STAT_RRDY, &i2c_base->stat);
			udelay(1000);
		} else
			break;
	}
}

static int
i2c_setspeed(uint8_t speed)
{
	int sclh = 0;
	int psc = 0;
	int iclk = 0;

	psc = I2C_PSC_MAX;
	while (psc >= I2C_PSC_MIN) {
		iclk = I2C_IP_CLK / (psc + 1);
		switch (speed) {
		case OMAP_I2C_STANDARD:
			sclh = (iclk * 10 / (OMAP_I2C_STANDARD * 2));
			debug("standard\n");
			break;
		case OMAP_I2C_HIGH_SPEED:
			/* FALLTHROUGH */
		case OMAP_I2C_FAST_MODE:
			sclh = (iclk * 10 / (OMAP_I2C_FAST_MODE * 2));
			break;
		}
		debug("speed=%d SysClk=%d, iclk=%d, psc=0x%x[%d], sclh=0x%x[%d]\n",
		    speed, I2C_IP_CLK, iclk, psc, psc, sclh, sclh);

		if (sclh % 10) {
			sclh = -1;
		} else {
			sclh /= 10;
			sclh -= 7;
		}
		if (sclh >= 0) {
			break;
		}
		psc--;
	}

	/* Did not find an optimal config */
	if (psc < I2C_PSC_MIN) {
		debug("unable to set Prescalar for i2c_clock=%d I2C_IP_CLK=%d\n",
		    speed, I2C_IP_CLK);
		psc = 0;
		return (-1);

	}
	iclk = I2C_IP_CLK / (psc + 1);

	switch (speed) {
	case OMAP_I2C_STANDARD:
		sclh = (((iclk / (OMAP_I2C_STANDARD * 2)) - 7) &
		    I2C_SCLL_SCLL_M) << I2C_SCLL_SCLL;
		break;
	case OMAP_I2C_HIGH_SPEED:
		sclh = (((I2C_IP_CLK / (OMAP_I2C_HIGH_SPEED * 2)) - 7) &
		    I2C_SCLH_HSSCLL_M) << I2C_SCLL_HSSCLL;
		/* FALLTHROUGH */
	case OMAP_I2C_FAST_MODE:
		sclh |= (((iclk / (OMAP_I2C_FAST_MODE * 2)) - 7) &
		    I2C_SCLL_SCLL_M) << I2C_SCLL_SCLL;
		break;
	default:
		debug("error: wrong speed\n");
	}

	debug("speed=%d SysClk=%d, iclk=%d, psc=0x%x[%d], sclh=0x%x[%d]\n",
	    speed, I2C_IP_CLK, iclk, psc, psc, sclh, sclh);

	i2c_speed = speed;
	writew(0, &i2c_base->con);
	writew(psc, &i2c_base->psc);
	writew(sclh, &i2c_base->scll);
	writew(sclh, &i2c_base->sclh);
	writew(I2C_CON_I2C_EN, &i2c_base->con);

	return (0);
}

void
i2c_init(int8_t bus, int8_t speed)
{
	int timeout = I2C_TIMEOUT;

	if ((bus < 0) || (bus >= 4)) {
		debug("bad bus id - %d\n", bus);
		return;
	}

	if ((speed != OMAP_I2C_STANDARD) &&
	    (speed != OMAP_I2C_FAST_MODE) &&
	    (speed != OMAP_I2C_HIGH_SPEED)) {
		debug("invalid speed for i2c init - %d\n", speed);
		return;
	}

	if (bus == 3)
		i2c_base = (struct i2c *)I2C_BASE4;
	else if (bus == 2)
		i2c_base = (struct i2c *)I2C_BASE3;
	else if (bus == 1)
		i2c_base = (struct i2c *)I2C_BASE2;
	else
		i2c_base = (struct i2c *)I2C_BASE1;

	if (readw(&i2c_base->con) & I2C_CON_I2C_EN) {
		writew(0, &i2c_base->con);
		udelay(50000);
	}

	writew(I2C_SYSC_SRST, &i2c_base->sysc);	/* for ES2 after soft reset */
	udelay(1000);

	writew(I2C_CON_I2C_EN, &i2c_base->con);
	while (!(readw(&i2c_base->syss) & I2C_SYSS_RDONE) && timeout--) {
		if (timeout <= 0) {
			debug("error: Timeout in soft-reset\n");
			return;
		}
		udelay(1000);
	}

	if (i2c_setspeed(speed) != 0) {
		debug("error: failed to setup i2c bus-spped\n");
		return;
	}

	/* own address */
	writew(1, &i2c_base->oa);
	udelay(1000);
	flush_fifo();
	writew(0xffff, &i2c_base->stat);
	writew(0, &i2c_base->cnt);
}

static int
i2c_read_byte(uint8_t sa, uint8_t ra, uint8_t *value)
{
	int i2c_error = 0;
	uint16_t status;

	/* wait until bus not busy */
	wait_for_bb();

	/* one byte only */
	writew(1, &i2c_base->cnt);
	/* set slave address */
	writew(sa, &i2c_base->sa);
	/* no stop bit needed here */
	writew(I2C_CON_I2C_EN | ((i2c_speed == OMAP_I2C_HIGH_SPEED) ? 0x1 << 12 : 0) |
	    I2C_CON_MST | I2C_CON_STT | I2C_CON_TRX, &i2c_base->con);

	status = wait_for_pin();

	if (status & I2C_STAT_XRDY) {
		writeb(ra, &i2c_base->data);
		udelay(20000);
		if (readw(&i2c_base->stat) & I2C_STAT_NACK) {
			i2c_error = 1;
		}
	} else {
		i2c_error = 1;
	}

	if (!i2c_error) {
		int eout = 10;
		while (readw(&i2c_base->stat) ||
		    (readw(&i2c_base->con) & I2C_CON_MST)) {
			udelay(10000);
			/* Have to clear pending interrupt to clear I2C_STAT */
			writew(0xffff,&i2c_base->stat);
			if (--eout == 0) {
				break;
			}
		}

		/* set slave address */
		writew(sa, &i2c_base->sa);
		/* read one byte from slave */
		writew(1, &i2c_base->cnt);
		/* need stop bit here */
		writew(I2C_CON_I2C_EN | ((i2c_speed == OMAP_I2C_HIGH_SPEED) ?
		    0x1 << 12 : 0) | I2C_CON_MST | I2C_CON_STT |
		    I2C_CON_STP, &i2c_base->con);

		status = wait_for_pin();
		if (status & I2C_STAT_RRDY) {
			*value = readb(&i2c_base->data);
			udelay(20000);
		} else {
			i2c_error = 1;
		}

		if (!i2c_error) {
			int eout = 10;
			writew(I2C_CON_I2C_EN, &i2c_base->con);
			while (readw(&i2c_base->stat) ||
			    (readw(&i2c_base->con) & I2C_CON_MST)) {
				udelay(10000);
				writew(0xffff, &i2c_base->stat);
				if (!eout--) {
					break;
				}
			}
		}
	}

	flush_fifo();
	writew(0xffff, &i2c_base->stat);
	writew(0, &i2c_base->cnt);

	return (i2c_error);
}

static int
i2c_write_byte(uint8_t sa, uint8_t ra, uint8_t value)
{
	int i2c_error = 0;
	uint16_t status;

	wait_for_bb();

	/* two bytes */
	writew(2, &i2c_base->cnt);
	/* set slave address */
	writew(sa, &i2c_base->sa);
	/* stop bit needed here */
	writew(I2C_CON_I2C_EN | ((i2c_speed == OMAP_I2C_HIGH_SPEED) ? 0x1 << 12 : 0) |
	    I2C_CON_MST | I2C_CON_STT | I2C_CON_TRX | I2C_CON_STP, &i2c_base->con);

	/* wait until state change */
	status = wait_for_pin();

	if (status & I2C_STAT_XRDY) {
		/* send out 1 byte */
		writeb(ra, &i2c_base->data);
		writew(I2C_STAT_XRDY, &i2c_base->stat);
		status = wait_for_pin();
		if ((status & I2C_STAT_XRDY)) {
			/* send out next 1 byte */
			writeb(value, &i2c_base->data);
			writew(I2C_STAT_XRDY, &i2c_base->stat);
		} else {
			i2c_error = 1;
		}
		/* must have enough delay to allow BB bit to go low */
		udelay(50000);
		if (readw(&i2c_base->stat) & I2C_STAT_NACK) {
			i2c_error = 1;
		}
	} else {
		i2c_error = 1;
	}

	if (!i2c_error) {
		int eout = 200;

		writew(I2C_CON_I2C_EN, &i2c_base->con);
		while ((status = readw(&i2c_base->stat)) ||
		    (readw(&i2c_base->con) & I2C_CON_MST)) {
			udelay(1000);
			/* have to read to clear intrrupt */
			writew(0xffff, &i2c_base->stat);
			if (--eout == 0)
				break;
		}
	}

	flush_fifo();
	writew(0xffff, &i2c_base->stat);
	writew(0, &i2c_base->cnt);

	return (i2c_error);
}

int
i2c_read(uint8_t chip, uint32_t addr, int alen, uint8_t *buffer, int len)
{
	int i;

	if (alen > 1) {
		debug("addr len %d not supported\n", alen);
		return (-1);
	}

	if (addr + len > 256) {
		debug("address out of range\n");
		return (-1);
	}

	for (i = 0; i < len; i++) {
		if (i2c_read_byte(chip, addr + i, &buffer[i])) {
			debug("I/O error\n");
			return (-1);
		}
	}

	return (0);
}

int
i2c_write(uint8_t chip, uint32_t addr, int alen, uint8_t *buffer, int len)
{
	int i;

	if (alen > 1) {
		debug("addr len %d not supported\n", alen);
		return (-1);
	}

	if (addr + len > 256) {
		debug("address out of range\n");
		return (-1);
	}

	for (i = 0; i < len; i++) {
		if (i2c_write_byte(chip, addr + i, buffer[i])) {
			debug("I/O error\n");
			return (-1);
		}
	}

	return (0);
}
