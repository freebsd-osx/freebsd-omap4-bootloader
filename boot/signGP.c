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
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

unsigned char config_header[512] = {
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x43, 0x48, 0x53, 0x45,
	0x54, 0x54, 0x49, 0x4e, 0x47, 0x53, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xc1, 0xc0, 0xc0, 0xc0, 0x00, 0x01, 0x00, 0x00,
};

int
main(int argc, char *argv[])
{
	char ifname[FILENAME_MAX], ofname[FILENAME_MAX], ch;
	FILE *ifile, *ofile;
	unsigned long loadaddr, size;
	struct stat sinfo;
	int i;

	/* default settings */
	strcpy(ifname, "boot.bin");
	strcpy(ofname, "boot");
	loadaddr = 0x40300000;

	if ((argc == 2) || (argc == 3))
		strcpy(ifname, argv[1]);

	if (argc == 3)
		loadaddr = strtoul(argv[2], NULL, 16);


	ifile = fopen(ifname, "rb");
	if (ifile == NULL) {
		printf("can not open %s\n", ifname);
	}

	stat(ifname, &sinfo);
	size = sinfo.st_size;

	ofile = fopen(ofname, "wb");
	if (ofile == NULL) {
		fclose(ifile);
		printf("can not open %s\n", ofname);
		exit(0);
	}

	if (fwrite(&config_header, 1, 512, ofile) <= 0)
		printf("failed to write configuration header\n");
	if (fwrite(&size, 1, 4, ofile) <= 0)
		printf("failed to write file size\n");
	if (fwrite(&loadaddr, 1, 4, ofile) <= 0)
		printf("failed to write load address\n");

	for (i = 0; i < size; i++) {
		if (fread(&ch, 1, 1, ifile) <= 0)
			printf("failed to read a file\n");
		if (fwrite(&ch, 1, 1, ofile) <= 0)
			printf("failed to write to a file\n");
	}

	if (!fclose(ifile))
		printf("fclose %s\n", ifname);
	if (!fclose(ofile))
		printf("fclose %s\n", ofname);

	return (0);
}
