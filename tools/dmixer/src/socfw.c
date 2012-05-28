/*

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
	char *plugin_name;
	void *plugin_handle;
	struct soc_dapm_plugin *dapm_object;

	/* opaque vendor data */
	int vendor_fd;
	char *vendor_name;

	/* out file */
	int out_fd;
};

static void usage(char *name)
{
	fprintf(stdout, "usage: %s [options] outfile\n\n", name);

	fprintf(stdout, "Add plugin data		[-p plugin]\n");
	fprintf(stdout, "Add controls			[-c controls]\n");
	fprintf(stdout, "Add vendor firmware		[-vfw firmware]\n");
	fprintf(stdout, "Add vendor coefficients 	[-vcf coefficients]\n");
	fprintf(stdout, "Add vendor configuration	[-vcn config]\n");
	fprintf(stdout, "Add vendor codec		[-vcd codec]\n");
	exit(0);
}

static void import_mixer(struct soc_fw_priv *soc_fw,
	const struct snd_kcontrol_new *kcontrol)
{
	struct snd_soc_file_kcontrol kc;
	struct snd_soc_file_mixer_control mc;
	struct soc_mixer_control *mixer =
		(struct soc_mixer_control *)kcontrol->private_value;
	size_t bytes;

	memset(&kc, 0, sizeof(kc));
	memset(&mc, 0, sizeof(mc));

	kc.type = SND_SOC_FILE_MIXER_VALUE;
	kc.count = 1;
	strncpy(mc.name, kcontrol->name, SND_SOC_FILE_TEXT_SIZE);
	mc.min = mixer->min;
	mc.max = mixer->max;
	mc.platform_max = mixer->platform_max;
	mc.reg = mixer->reg;
	mc.rreg = mixer->rreg;
	mc.shift = mixer->shift;
	mc.rshift = mixer->rshift;
	mc.invert = mixer->invert;

	fprintf(stdout, " mixer: \"%s\" R1/2 0x%x/0x%x shift L/R %d/%d\n", mc.name,
		mc.reg, mc.rreg, mc.shift, mc.rshift);

	bytes = write(soc_fw->out_fd, &kc, sizeof(kc));
	if (bytes != sizeof(kc)) {
		fprintf(stderr, "error: can't write mixer %lu\n", bytes);
		exit(-bytes);
	}
	bytes = write(soc_fw->out_fd, &mc, sizeof(mc));
	if (bytes != sizeof(mc)) {
		fprintf(stderr, "error: can't write mixer %lu\n", bytes);
		exit(-bytes);
	}
}

static void import_enum_control_data(struct soc_fw_priv *soc_fw, int count,
	struct snd_soc_file_enum_control *ec, struct soc_enum *menum)
{
	int i;

	if (menum->values) {
		for (i = 0; i < count; i++) {
			ec->values[i] = menum->values[i];
		}
	} else {
		for (i = 0; i < count; i++) {
			strncpy(ec->texts[i], menum->texts[i], SND_SOC_FILE_TEXT_SIZE);
		}
	}
}

static void import_enum_control(struct soc_fw_priv *soc_fw,
	const struct snd_kcontrol_new *kcontrol)
{
	struct snd_soc_file_kcontrol kc;
	struct snd_soc_file_enum_control ec;
	struct soc_enum *menum =
		(struct soc_enum *)kcontrol->private_value;
	size_t bytes;

	memset(&kc, 0, sizeof(kc));
	memset(&ec, 0, sizeof(ec));

	kc.type = SND_SOC_FILE_MIXER_ENUM;
	kc.count = kcontrol->count;

	if (kcontrol->count >= SND_SOC_FILE_NUM_TEXTS) {
		fprintf(stderr, "error: too many enum values %d\n",
			kcontrol->count);
		exit(-EINVAL);
	}

	strncpy(ec.name, kcontrol->name, SND_SOC_FILE_TEXT_SIZE);
	ec.mask = menum->mask;
	ec.max = menum->max;
	ec.reg = menum->reg;
	ec.reg2 = menum->reg2;
	ec.shift_l = menum->shift_l;
	ec.shift_r = menum->shift_r;

	fprintf(stdout, " enum: \"%s\" R1/2 0x%x/0x%x shift L/R %d/%d\n", ec.name,
		ec.reg, ec.reg2, ec.shift_l, ec.shift_r);

	import_enum_control_data(soc_fw, kcontrol->count, &ec, menum);

	bytes = write(soc_fw->out_fd, &kc, sizeof(kc));
	if (bytes != sizeof(kc)) {
		fprintf(stderr, "error: can't write mixer %lu\n", bytes);
		exit(-bytes);
	}
	bytes = write(soc_fw->out_fd, &ec, sizeof(ec));
	if (bytes != sizeof(ec)) {
		fprintf(stderr, "error: can't write mixer %lu\n", bytes);
		exit(-bytes);
	}
}

static void import_controls(struct soc_fw_priv *soc_fw)
{
	struct snd_soc_file_hdr hdr;
	int i, mixers = 0, enums = 0;
	size_t bytes;

	memset(&hdr, 0, sizeof(hdr));

	hdr.magic = SND_SOC_FILE_MAGIC;
	hdr.type = SND_SOC_FILE_MIXER;

	for (i = 0; i < soc_fw->dapm_object->kcontrol_count; i++) {
		const struct snd_kcontrol_new *kn =
			&soc_fw->dapm_object->kcontrols[i];
		hdr.size += sizeof(struct snd_soc_file_kcontrol);

		switch (kn->iface) {
		case SOC_MIXER_IO_VOLSW:
		case SOC_MIXER_IO_VOLSW_SX:
		case SOC_MIXER_IO_VOLSW_S8:
		case SOC_MIXER_IO_VOLSW_XR_SX:
		case SOC_MIXER_IO_VOLSW_EXT:
			hdr.size += sizeof(struct snd_soc_file_mixer_control);
			mixers++;
			break;
		case SOC_MIXER_IO_ENUM:
		case SOC_MIXER_IO_ENUM_EXT:
			hdr.size += sizeof(struct snd_soc_file_enum_control);
			enums++;
			break;
		case SOC_MIXER_IO_BYTES:
		case SOC_MIXER_IO_BOOL:
		default:
			fprintf(stderr, "error: mixer type %d not supported atm\n",
				kn->iface);
			exit(-EINVAL);
		}
	}
	fprintf(stdout, "kcontrols: %d mixers %d enums %d size %lu bytes\n",
		mixers + enums, mixers, enums, hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write kcontrol header %lu\n", bytes);
		exit(-bytes);
	}

	for (i = 0; i < soc_fw->dapm_object->kcontrol_count; i++) {
		const struct snd_kcontrol_new *kn =
			&soc_fw->dapm_object->kcontrols[i];

		switch (kn->iface) {
		case SOC_MIXER_IO_VOLSW:
		case SOC_MIXER_IO_VOLSW_SX:
		case SOC_MIXER_IO_VOLSW_S8:
		case SOC_MIXER_IO_VOLSW_XR_SX:
		case SOC_MIXER_IO_VOLSW_EXT:
			import_mixer(soc_fw, kn);
			break;
		case SOC_MIXER_IO_ENUM:
		case SOC_MIXER_IO_ENUM_EXT:
			import_enum_control(soc_fw, kn);
			break;
		case SOC_MIXER_IO_BYTES:
		case SOC_MIXER_IO_BOOL:
		default:
			fprintf(stderr, "error: mixer type %d not supported atm\n",
				kn->iface);
			exit(-EINVAL);
		}
	}
}

static void import_dapm_widgets_controls(struct soc_fw_priv *soc_fw, int count,
	const struct snd_kcontrol_new *kn)
{
	struct snd_soc_file_hdr hdr;
	int i;

	for (i = 0; i < count; i++) {

		switch (kn->iface) {
		case SOC_MIXER_IO_VOLSW:
		case SOC_MIXER_IO_VOLSW_SX:
		case SOC_MIXER_IO_VOLSW_S8:
		case SOC_MIXER_IO_VOLSW_XR_SX:
		case SOC_MIXER_IO_VOLSW_EXT:
			import_mixer(soc_fw, kn);
			break;
		case SOC_MIXER_IO_ENUM:
		case SOC_MIXER_IO_ENUM_EXT:
			import_enum_control(soc_fw, kn);
			break;
		case SOC_MIXER_IO_BYTES:
		case SOC_MIXER_IO_BOOL:
		default:
			fprintf(stderr, "error: widget mixer type %d not supported atm\n",
				kn->iface);
			exit(-EINVAL);
		}
		kn++;
	}
}

static void import_dapm_widgets(struct soc_fw_priv *soc_fw)
{
	struct snd_soc_file_dapm_widget widget;
	struct snd_soc_file_hdr hdr;
	size_t bytes;
	int i;

	memset(&hdr, 0, sizeof(hdr));

	hdr.magic = SND_SOC_FILE_MAGIC;
	hdr.type = SND_SOC_FILE_DAPM_WIDGET;
	hdr.size = sizeof(widget) * soc_fw->dapm_object->widget_count;

	fprintf(stdout, "widgets: widgets %d size %lu bytes\n",
		soc_fw->dapm_object->widget_count, hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write widget header %lu\n", bytes);
		exit(-bytes);
	}

	for (i = 0; i < soc_fw->dapm_object->widget_count; i++) {

		strncpy(widget.name, soc_fw->dapm_object->widgets[i].name,
			SND_SOC_FILE_TEXT_SIZE);

		if (soc_fw->dapm_object->widgets[i].sname)
			strncpy(widget.sname, soc_fw->dapm_object->widgets[i].sname,
				SND_SOC_FILE_TEXT_SIZE);

		widget.id = soc_fw->dapm_object->widgets[i].id;
		widget.reg = soc_fw->dapm_object->widgets[i].reg;
		widget.shift = soc_fw->dapm_object->widgets[i].shift;
		widget.mask = soc_fw->dapm_object->widgets[i].mask;
		widget.invert = soc_fw->dapm_object->widgets[i].invert;

		fprintf(stdout, " widget: \"%s\" R 0x%x shift %d\n",
			widget.name, widget.reg, widget.shift);

		bytes = write(soc_fw->out_fd, &widget, sizeof(widget));
		if (bytes != sizeof(widget)) {
			fprintf(stderr, "error: can't write widget %lu\n", bytes);
			exit(-bytes);
		}

		import_dapm_widgets_controls(soc_fw,
			soc_fw->dapm_object->widgets[i].num_kcontrols,
			soc_fw->dapm_object->widgets[i].kcontrol_news);
	}
}

static void import_dapm_graph(struct soc_fw_priv *soc_fw)
{
	struct snd_soc_file_dapm_elems elem_hdr;
	struct snd_soc_file_dapm_graph_elem elem;
	struct snd_soc_file_hdr hdr;
	size_t bytes;
	int i;

	memset(&hdr, 0, sizeof(hdr));

	hdr.magic = SND_SOC_FILE_MAGIC;
	hdr.type = SND_SOC_FILE_DAPM_GRAPH;
	hdr.size = sizeof(elem_hdr) +
		sizeof(elem) * soc_fw->dapm_object->graph_count;

	fprintf(stdout, "graph: routes %d size %lu bytes\n",
		soc_fw->dapm_object->graph_count, hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write graph header %lu\n", bytes);
		exit(-bytes);
	}

	elem_hdr.count = soc_fw->dapm_object->graph_count;

	bytes = write(soc_fw->out_fd, &elem_hdr, sizeof(elem_hdr));
	if (bytes != sizeof(elem_hdr)) {
		fprintf(stderr, "error: can't write graph elem header %lu\n", bytes);
		exit(-bytes);
	}

	for (i = 0; i < soc_fw->dapm_object->graph_count; i++) {
		strncpy(elem.sink, soc_fw->dapm_object->graph[i].sink,
			SND_SOC_FILE_TEXT_SIZE);
		strncpy(elem.source, soc_fw->dapm_object->graph[i].source,
			SND_SOC_FILE_TEXT_SIZE);
		if (soc_fw->dapm_object->graph[i].control)
			strncpy(elem.control, soc_fw->dapm_object->graph[i].control,
				SND_SOC_FILE_TEXT_SIZE);

		fprintf(stdout, " graph: %s -> %s -> %s\n",
			elem.source, elem.control, elem.sink); 
		bytes = write(soc_fw->out_fd, &elem, sizeof(elem));
		if (bytes != sizeof(elem)) {
			fprintf(stderr, "error: can't write graph elem %lu\n", bytes);
			exit(-bytes);
		}
	}
}

static void import_vendor(struct soc_fw_priv *soc_fw, int type)
{
	struct snd_soc_file_hdr hdr;
	size_t bytes;
	char buf[4096];
	int i, chunks, rem;

	memset(&hdr, 0, sizeof(hdr));

	soc_fw->vendor_fd = open(soc_fw->vendor_name, O_RDONLY);
	if (soc_fw->vendor_fd < 0) {
		fprintf(stderr, "error: can't open %s %d\n", 
			soc_fw->vendor_name, soc_fw->vendor_fd);
		exit(soc_fw->vendor_fd);
	}

	hdr.magic = SND_SOC_FILE_MAGIC;
	hdr.type = type;
	hdr.size = lseek(soc_fw->vendor_fd, SEEK_END, 0);

	fprintf(stdout, "coeff: %lu bytes\n", hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write vendor header %lu\n", bytes);
		exit(-bytes);
	}

	lseek(soc_fw->vendor_fd, SEEK_SET, 0);

	chunks = hdr.size / 4096;
	rem = hdr.size % 4096;

	for (i = 0; i < chunks; i++) {
		bytes = read(soc_fw->vendor_fd, buf, 4096);
		if (bytes < 0 || bytes != 4096) {
			fprintf(stderr, "error: can't read vendor data %lu\n", bytes);
			exit(-bytes);
		}

		bytes = write(soc_fw->out_fd, buf, 4096);
		if (bytes < 0 || bytes != 4096) {
			fprintf(stderr, "error: can't write vendor data %lu\n", bytes);
			exit(-bytes);
		}
	}

	bytes = read(soc_fw->vendor_fd, buf, rem);
	if (bytes < 0 || bytes != rem) {
		fprintf(stderr, "error: can't read vendor data %lu\n", bytes);
		exit(-bytes);
	}

	bytes = write(soc_fw->out_fd, buf, rem);
	if (bytes < 0 || bytes != rem) {
		fprintf(stderr, "error: can't write vendor data %lu\n", bytes);
		exit(-bytes);
	}
}

static void import_plugin(struct soc_fw_priv *soc_fw)
{
	size_t size;

	/* load the plugin */
	soc_fw->plugin_handle = dlopen(soc_fw->plugin_name, RTLD_LAZY);
	if (!soc_fw->plugin_handle) {
		fprintf(stderr, "error: failed to open %s: %s\n", 
		soc_fw->plugin_name, dlerror());
		exit(-EINVAL);
	}

	soc_fw->dapm_object = dlsym(soc_fw->plugin_handle, "plugin");
	if (!soc_fw->dapm_object) {
		fprintf(stderr, "error: failed to get symbol. %s\n",
			dlerror());
		dlclose(soc_fw->plugin_handle);
		exit(-EINVAL);
	}

	/* dump some plugin info */
	printf("dapm: loaded %s\n", soc_fw->plugin_name);
	if (soc_fw->dapm_object->graph_count > 0)
		fprintf(stdout, " dapm: found graph with %d routes\n",
			soc_fw->dapm_object->graph_count);
	else
		fprintf(stdout, " dapm: no graph found\n");

	if (soc_fw->dapm_object->widget_count > 0)
		fprintf(stdout, " dapm: found %d widgets\n",
			soc_fw->dapm_object->widget_count);
	else
		fprintf(stdout, " dapm: no widgets found\n");

	if (soc_fw->dapm_object->kcontrol_count > 0)
		fprintf(stdout, " dapm: found %d controls\n",
			soc_fw->dapm_object->kcontrol_count);
	else
		fprintf(stdout, " dapm: no controls found\n");

	import_controls(soc_fw);

	import_dapm_widgets(soc_fw);

	import_dapm_graph(soc_fw);

	dlclose(soc_fw->plugin_handle);
}

int main(int argc, char *argv[])
{
	struct soc_fw_priv soc_fw;
	int i;
	
	if (argc < 4)
		usage(argv[0]);

	/* last arg is always filename of output */
	/* open output file */
	soc_fw.out_fd = open(argv[argc - 1], O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (soc_fw.out_fd < 0) {
		fprintf(stderr, "failed to open %s err %d\n",
			argv[argc - 1], soc_fw.out_fd);
		exit(soc_fw.out_fd);
	}

	for (i = 1 ; i < argc - 1; i++) {

		/* plugin - kcontrols, DAPM graph, widgets, pins etc */
		if (!strcmp("-p", argv[i])) {
			if (++i == argc)
				usage(argv[0]);
			soc_fw.plugin_name = argv[i];

			import_plugin(&soc_fw);
			continue;
		}

		/* vendor options */
		if (!strcmp("-vfw", argv[i])) {
			if (++i == argc)
				usage(argv[0]);

			soc_fw.vendor_name = argv[i];
			import_vendor(&soc_fw, SND_SOC_FILE_VENDOR_FW);
			continue;
		}
		if (!strcmp("-vcf", argv[i])) {
			if (++i == argc)
				usage(argv[0]);

			soc_fw.vendor_name = argv[i];
			import_vendor(&soc_fw, SND_SOC_FILE_VENDOR_COEFF);
			continue;
		}
		if (!strcmp("-vco", argv[i])) {
			if (++i == argc)
				usage(argv[0]);

			soc_fw.vendor_name = argv[i];
			import_vendor(&soc_fw, SND_SOC_FILE_VENDOR_CODEC);
			continue;
		}

	}

	close(soc_fw.out_fd);
	return 0;
}

