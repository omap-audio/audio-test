/*
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
#include <stdarg.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dlfcn.h>

#include "abegen.h"

static int abe_dlopen_fw(const char *fw_version)
{
	void *plugin_handle;
	struct abe_firmware *fw;
	int ret, fd;

	fprintf(stdout, "FW: loading %s\n", fw_version);

	/* load the plugin */
	plugin_handle = dlopen(fw_version, RTLD_LAZY);
	if (!plugin_handle) {
		fprintf(stderr, "error: failed to open %s: %s\n", fw_version,
			dlerror());
		return -EINVAL;
	}

	fw = dlsym(plugin_handle, "fw");
	if (!fw) {
		fprintf(stderr, "error: failed to get symbol. %s\n",
			dlerror());
		dlclose(plugin_handle);
		return -EINVAL;
	}

	/* dump some plugin info */
	fprintf(stdout, "FW: loaded %d bytes\n", fw->size);
	
	/* save data to FW file */
	fd = open("omap_abe_fw", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0) {
		fprintf(stderr, "failed to open %s err %d\n", "omap_abe_fw", fd);
		ret = fd;
		goto out;
	}

	ret = write(fd, fw->text, fw->size * 4);
	close(fd);

out:
	dlclose(plugin_handle);
	return ret;
}

static int abe_dlopen_tasks(const char *fw_version)
{
	void *plugin_handle;
	struct abe_firmware *fw;
	int ret, fd;

	fprintf(stdout, "Tasks: loading %s\n", fw_version);

	/* load the plugin */
	plugin_handle = dlopen(fw_version, RTLD_LAZY);
	if (!plugin_handle) {
		fprintf(stderr, "error: failed to open %s: %s\n", fw_version,
			dlerror());
		return -EINVAL;
	}

	fw = dlsym(plugin_handle, "fw");
	if (!fw) {
		fprintf(stderr, "error: failed to get symbol. %s\n",
			dlerror());
		dlclose(plugin_handle);
		return -EINVAL;
	}

	/* dump some plugin info */
	fprintf(stdout, "FW: loaded %d bytes\n", fw->size);
	
	/* save data to FW file */
	fd = open("omap_abe_tasks", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0) {
		fprintf(stderr, "failed to open %s err %d\n", "omap_abe_tasks", fd);
		ret = fd;
		goto out;
	}

	ret = write(fd, fw->text, fw->size * 4);
	close(fd);

out:
	dlclose(plugin_handle);
	return ret;
}

static void usage(char *name)
{
	fprintf(stdout, "usage: %s [options]\n\n", name);

	fprintf(stdout, "Create firmware		[-f version]\n");
	fprintf(stdout, "Create tasks			[-t version]\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	int i, ret;
	
	if (argc < 2)
		usage(argv[0]);

	for (i = 1 ; i < argc - 1; i++) {

		/* FW */
		if (!strcmp("-f", argv[i])) {
			if (++i == argc)
				usage(argv[0]);

			abe_dlopen_fw(argv[i]);
			continue;
		}

		/* Tasks */
		if (!strcmp("-t", argv[i])) {
			if (++i == argc)
				usage(argv[0]);

			abe_dlopen_tasks(argv[i]);
			continue;
		}
	}

	return 0;
}
