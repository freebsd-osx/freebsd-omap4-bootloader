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

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

struct chsettings {
	uint32_t section_key;
	uint8_t valid;
	uint8_t version;
	uint16_t reserved;
	uint32_t flags;
} __attribute__ ((__packed__));

struct gp_header {
	uint32_t size;
	uint32_t load_addr;
} __attribute__ ((__packed__));

struct ch_toc {
	uint32_t section_offset;
	uint32_t section_size;
	uint8_t unused[12];
	uint8_t section_name[12];
} __attribute__ ((__packed__));

struct chram {
	/* CHRAM */
	uint32_t section_key_chr;
	uint8_t section_disable_chr;
	uint8_t pad_chr[3];
	/* EMIF1 */
	uint32_t config_emif1;
	uint32_t refresh_emif1;
	uint32_t tim1_emif1;
	uint32_t tim2_emif1;
	uint32_t tim3_emif1;
	uint32_t pwrControl_emif1;
	uint32_t phy_cntr1_emif1;
	uint32_t phy_cntr2_emif1;
	uint8_t modereg1_emif1;
	uint8_t modereg2_emif1;
	uint8_t modereg3_emif1;
	uint8_t pad_emif1;
	/* EMIF2 */
	uint32_t config_emif2;
	uint32_t refresh_emif2;
	uint32_t tim1_emif2;
	uint32_t tim2_emif2;
	uint32_t tim3_emif2;
	uint32_t pwrControl_emif2;
	uint32_t phy_cntr1_emif2;
	uint32_t phy_cntr2_emif2;
	uint8_t modereg1_emif2;
	uint8_t modereg2_emif2;
	uint8_t modereg3_emif2;
	uint8_t pad_emif2;

	uint32_t dmm_lisa_map;
	uint8_t flags;
	uint8_t pad[3];
} __attribute__ ((__packed__));


struct ch_chsettings_chram {
	struct ch_toc toc_chsettings;
	struct ch_toc toc_chram;
	struct ch_toc toc_terminator;
	struct chsettings section_chsettings;
	struct chram section_chram;
	uint8_t padding1[512 -
		    (sizeof(struct ch_toc) * 3 +
		     sizeof(struct chsettings) + sizeof(struct chram))];
	/* struct gp_header gpheader; */
} __attribute__ ((__packed__));

struct ch_chsettings_nochram {
	struct ch_toc toc_chsettings;
	struct ch_toc toc_terminator;
	struct chsettings section_chsettings;
	uint8_t padding1[512 -
		    (sizeof(struct ch_toc) * 2 +
		     sizeof(struct chsettings))];
	/* struct gp_header gpheader; */
} __attribute__ ((__packed__));

static struct ch_chsettings_nochram config_header
	__attribute__((section(".config_header"))) = {
	/* CHSETTINGS TOC */
	{(sizeof(struct ch_toc)) * 2,
	 sizeof(struct chsettings),
	 "",
	 {"CHSETTINGS"}
	 },
	/* toc terminator */
	{0xFFFFFFFF,
	 0xFFFFFFFF,
	 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	  0xFF},
	 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	  0xFF}
	 },
	/* CHSETTINGS section */
	{
	 0xC0C0C0C1,
	 0,
	 1,
	 0,
	 0},
	""
};

#define err(...) do { int save_errno = errno; \
                      fprintf(stderr, __VA_ARGS__); \
                      errno = save_errno; \
                    } while (0);
#define pdie(func, ...) do { perror(func); exit(1); } while (0);

int main(int argc, char *argv[])
{
	int	i;
	char	ifname[FILENAME_MAX], ofname[FILENAME_MAX], ch;
	FILE	*ifile, *ofile;
	unsigned long	loadaddr, len;
	struct stat	sinfo;
	int ch_add = 1;


	/* Default to boot0.bin and 0x40300000. */
	strcpy(ifname, "boot1.bin");
	loadaddr = 0x40300000;

	if ((argc == 2) || (argc == 3) || (argc == 4))
		strcpy(ifname, argv[1]);

	if ((argc == 3) || (argc == 4))
		loadaddr = strtoul(argv[2], NULL, 16);

	if (argc == 4)
		ch_add = strtoul(argv[3], NULL, 16);

	/* Form the output file name. */
	strcpy(ofname, "MLO");

	/* Open the input file. */
	ifile = fopen(ifname, "rb");
	if (ifile == NULL) {
		err("Cannot open %s\n", ifname);
		pdie("fopen");
	}

	/* Get file length. */
	stat(ifname, &sinfo);
	len = sinfo.st_size;

	/* Open the output file and write it. */
	ofile = fopen(ofname, "wb");
	if (ofile == NULL) {
		fclose(ifile);
		err("Cannot open %s\n", ofname);
		pdie("fopen");
	}

	if (ch_add)
		if (fwrite(&config_header, 1, 512, ofile) <= 0)
			pdie("fwrite");

	if (fwrite(&len, 1, 4, ofile) <= 0)
		pdie("fwrite");
	if (fwrite(&loadaddr, 1, 4, ofile) <= 0)
		pdie("fwrite");
	for (i = 0; i < len; i++) {
		if (fread(&ch, 1, 1, ifile) <= 0)
		    pdie("fread");
		if (fwrite(&ch, 1, 1, ofile) <= 0)
		    pdie("fwrite");
	}

	if (!fclose(ifile))
		printf("fclose %s\n", ifname);
	if (!fclose(ofile))
		printf("fclose %s\n", ofname);

	return 0;
}
