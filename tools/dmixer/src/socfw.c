/*

  This file is provided under a dual BSD/GPLv2 license.  When using or
  redistributing this file, you may do so under either license.

  GPL LICENSE SUMMARY

  Copyright(c) 2010-2011 Texas Instruments Incorporated,
  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
  The full GNU General Public License is included in this distribution
  in the file called LICENSE.GPL.

  BSD LICENSE

  Copyright(c) 2010-2011 Texas Instruments Incorporated,
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
    * Neither the name of Texas Instruments Incorporated nor the names of
      its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dlfcn.h>

#include "socfw.h"

struct soc_fw_priv {
	/* DAPM object */
	char *dapm_name;
	void *dapm_handle;
	struct soc_dapm_plugin *dapm_object;

	char *control_object;

	/* opaque vendor data */
	char *vendor_fw;
	char *vendor;

	/* out file */
	char *outfile;
	int out_fd;
};

static void usage(char *name)
{
	printf("usage: %s [options] outfile\n\n", name);

	printf("Add dapm			[-d dapm]\n");
	printf("Add controls			[-c controls]\n");
	printf("Add vendor firmware		[-vfw firmware]\n");
	printf("Add vendor coefficients 	[-vcf coefficients]\n");
	printf("Add vendor configuration	[-vcn config]\n");
	printf("Add vendor codec		[-vcd codec]\n");
	exit(0);
}

static void load_graph(struct soc_fw_priv *soc_fw)
{

	soc_fw->dapm_handle = dlopen(soc_fw->dapm_name, RTLD_LAZY);
	if (!soc_fw->dapm_handle) {
		printf("error: failed to open %s\n", soc_fw->dapm_name);
		exit(-EINVAL);
	}


	soc_fw->dapm_object = dlsym(soc_fw->dapm_handle, "dapm_plugin");
	if (!soc_fw->dapm_object) {
		printf("error: failed to get symbol\n");
		exit(-EINVAL);
	}

	printf("dapm: loaded %s\n", soc_fw->dapm_name);
	if (soc_fw->dapm_object->graph_count > 0)
		printf(" dapm: found graph with %d routes\n",
			soc_fw->dapm_object->graph_count);
	else
		printf(" dapm: no graph found\n");

	if (soc_fw->dapm_object->widget_count > 0)
		printf(" dapm: found %d widgets\n",
			soc_fw->dapm_object->widget_count);
	else
		printf(" dapm: no widgets found\n");

	if (soc_fw->dapm_object->kcontrol_count > 0)
		printf(" dapm: found %d controls\n",
			soc_fw->dapm_object->kcontrol_count);
	else
		printf(" dapm: no controls found\n");
}

int main(int argc, char *argv[])
{
	struct soc_fw_priv soc_fw;
	int i, err = 0, in_fd, out_fd, offset = 0;
	FILE *out_legacy_fd = NULL;
	uint32_t *buf_legacy;
	char *buf;
	
	if (argc < 4)
		usage(argv[0]);

	for (i = 1 ; i < argc; i++) {

		/* DAPM graph, widgets, pins etc */
		if (!strcmp("-d", argv[i])) {
			if (++i == argc)
				usage(argv[0]);
			soc_fw.dapm_name = argv[i];

			load_graph(&soc_fw);
			continue;
		}

		/* mixer controls */
		if (!strcmp("-c", argv[i])) {
			if (++i == argc)
				usage(argv[0]);
			//control_object = argv[i];
			continue;
		}

		/* vendor options */
		if (!strcmp("-vfw", argv[i])) {
			if (++i == argc)
				usage(argv[0]);
			//dapm_object = argv[i];
			continue;
		}
		if (!strcmp("-v", argv[i])) {
			if (++i == argc)
				usage(argv[0]);
			//dapm_object = argv[i];
			continue;
		}
		if (!strcmp("-v", argv[i])) {
			if (++i == argc)
				usage(argv[0]);
			//dapm_object = argv[i];
			continue;
		}

		/* none of the above so must be outfile */
		//outfile = argv[i];
	}
#if 0
	buf = malloc(MAX_FILE_SIZE);
	if (buf == NULL)
		return -ENOMEM;
	bzero(buf, MAX_FILE_SIZE);

	/* open output file */
	out_fd = open(argv[1], O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (out_fd < 0) {
		printf("failed to open %s err %d\n",
			argv[1], out_fd);
		err = out_fd;
		goto err_open1;
	}

	/* open output file for FW hexdump */
	if (argc == 3) {
		out_legacy_fd = fopen(argv[2], "w");
		if (out_legacy_fd == NULL) {
			printf("failed to open %s\n", argv[2]);
			return 0;
			goto err_open2;
		}
	}

	/* check if firmware file is already generated and just dump it again */
	if (*firmware == 0xabeabe00) {
		printf("Firmware already processed. Dumping binary firmware\n");
		goto dump;
	}

	hdr.firmware_version = ABE_FIRMWARE_VERSION;
	hdr.firmware_size = sizeof(firmware);
	hdr.coeff_version = ABE_COEFF_VERSION;
	offset = sizeof(hdr) + NUM_EQUALIZERS * sizeof(struct config);

	
dump:
	memcpy(buf + offset, firmware, sizeof(firmware));
	err = write(out_fd, buf, offset + sizeof(firmware));
	if (err <= 0)
		goto err_write;

	if (argc == 3) {
		buf_legacy = (uint32_t *)buf;
		for (i = 0; i < (offset + sizeof(firmware)) >> 2; i++)
			fprintf(out_legacy_fd, "0x%08x,\n", buf_legacy[i]);
	}

err_write:
	if (out_legacy_fd)
		fclose(out_legacy_fd);
err_open2:
	close (out_fd);
err_open1:
	free(buf);
#endif
	return err;
}
