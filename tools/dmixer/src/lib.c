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

	/* opaque vendor data */
	int vendor_fd;
	char *vendor_name;

	/* out file */
	int out_fd;
};

static int import_mixer(struct soc_fw_priv *soc_fw,
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
		return bytes;
	}
	bytes = write(soc_fw->out_fd, &mc, sizeof(mc));
	if (bytes != sizeof(mc)) {
		fprintf(stderr, "error: can't write mixer %lu\n", bytes);
		return bytes;
	}

	return 0;
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

static int import_enum_control(struct soc_fw_priv *soc_fw,
	const struct snd_kcontrol_new *kcontrol)
{
	struct snd_soc_file_kcontrol kc;
	struct snd_soc_file_enum_control ec;
	struct soc_enum *menum =
		(struct soc_enum *)kcontrol->private_value;
	size_t bytes;
	int err;

	memset(&kc, 0, sizeof(kc));
	memset(&ec, 0, sizeof(ec));

	kc.type = SND_SOC_FILE_MIXER_ENUM;
	kc.count = kcontrol->count;

	if (kcontrol->count >= SND_SOC_FILE_NUM_TEXTS) {
		fprintf(stderr, "error: too many enum values %d\n",
			kcontrol->count);
		return -EINVAL;;
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
		return bytes;
	}
	bytes = write(soc_fw->out_fd, &ec, sizeof(ec));
	if (bytes != sizeof(ec)) {
		fprintf(stderr, "error: can't write mixer %lu\n", bytes);
		return bytes;
	}

	return 0;
}

int socfw_import_controls(struct soc_fw_priv *soc_fw,
	const struct snd_kcontrol_new *kcontrols, int kcontrol_count)
{
	struct snd_soc_file_hdr hdr;
	int i, mixers = 0, enums = 0;
	size_t bytes;
	int err;

	memset(&hdr, 0, sizeof(hdr));

	hdr.magic = SND_SOC_FILE_MAGIC;
	hdr.type = SND_SOC_FILE_MIXER;

	for (i = 0; i < kcontrol_count; i++) {
		const struct snd_kcontrol_new *kn =
			&kcontrols[i];
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
			return -EINVAL;
		}
	}
	fprintf(stdout, "kcontrols: %d mixers %d enums %d size %lu bytes\n",
		mixers + enums, mixers, enums, hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write kcontrol header %lu\n", bytes);
		return bytes;
	}

	for (i = 0; i < kcontrol_count; i++) {
		const struct snd_kcontrol_new *kn =
			&kcontrols[i];

		switch (kn->iface) {
		case SOC_MIXER_IO_VOLSW:
		case SOC_MIXER_IO_VOLSW_SX:
		case SOC_MIXER_IO_VOLSW_S8:
		case SOC_MIXER_IO_VOLSW_XR_SX:
		case SOC_MIXER_IO_VOLSW_EXT:
			err = import_mixer(soc_fw, kn);
			if (err < 0)
				return err;
			break;
		case SOC_MIXER_IO_ENUM:
		case SOC_MIXER_IO_ENUM_EXT:
			err = import_enum_control(soc_fw, kn);
			if (err < 0)
				return err;
			break;
		case SOC_MIXER_IO_BYTES:
		case SOC_MIXER_IO_BOOL:
		default:
			fprintf(stderr, "error: mixer type %d not supported atm\n",
				kn->iface);
			return -EINVAL;
		}
	}

	return 0;
}

static int import_dapm_widgets_controls(struct soc_fw_priv *soc_fw, int count,
	const struct snd_kcontrol_new *kn)
{
	struct snd_soc_file_hdr hdr;
	int i, err;

	for (i = 0; i < count; i++) {

		switch (kn->iface) {
		case SOC_MIXER_IO_VOLSW:
		case SOC_MIXER_IO_VOLSW_SX:
		case SOC_MIXER_IO_VOLSW_S8:
		case SOC_MIXER_IO_VOLSW_XR_SX:
		case SOC_MIXER_IO_VOLSW_EXT:
			err = import_mixer(soc_fw, kn);
			if (err < 0)
				return err;
			break;
		case SOC_MIXER_IO_ENUM:
		case SOC_MIXER_IO_ENUM_EXT:
			err = import_enum_control(soc_fw, kn);
			if (err < 0)
				return err;
			break;
		case SOC_MIXER_IO_BYTES:
		case SOC_MIXER_IO_BOOL:
		default:
			fprintf(stderr, "error: widget mixer type %d not supported atm\n",
				kn->iface);
			return -EINVAL;
		}
		kn++;
	}

	return 0;
}

int socfw_import_dapm_widgets(struct soc_fw_priv *soc_fw,
	const struct snd_soc_dapm_widget *widgets, int widget_count)
{
	struct snd_soc_file_dapm_widget widget;
	struct snd_soc_file_hdr hdr;
	size_t bytes;
	int i, err;

	memset(&hdr, 0, sizeof(hdr));

	hdr.magic = SND_SOC_FILE_MAGIC;
	hdr.type = SND_SOC_FILE_DAPM_WIDGET;
	hdr.size = sizeof(widget) * widget_count;

	fprintf(stdout, "widgets: widgets %d size %lu bytes\n",
		widget_count, hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write widget header %lu\n", bytes);
		return bytes;
	}

	for (i = 0; i < widget_count; i++) {

		strncpy(widget.name, widgets[i].name,
			SND_SOC_FILE_TEXT_SIZE);

		if (widgets[i].sname)
			strncpy(widget.sname, widgets[i].sname,
				SND_SOC_FILE_TEXT_SIZE);

		widget.id = widgets[i].id;
		widget.reg = widgets[i].reg;
		widget.shift = widgets[i].shift;
		widget.mask = widgets[i].mask;
		widget.invert = widgets[i].invert;

		fprintf(stdout, " widget: \"%s\" R 0x%x shift %d\n",
			widget.name, widget.reg, widget.shift);

		bytes = write(soc_fw->out_fd, &widget, sizeof(widget));
		if (bytes != sizeof(widget)) {
			fprintf(stderr, "error: can't write widget %lu\n", bytes);
			return bytes;
		}

		err = import_dapm_widgets_controls(soc_fw,
			widgets[i].num_kcontrols,
			widgets[i].kcontrol_news);
		if (err < 0)
			return err;
	}

	return 0;
}

int socfw_import_dapm_graph(struct soc_fw_priv *soc_fw,
	const struct snd_soc_dapm_route *graph, int graph_count)
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
		sizeof(elem) * graph_count;

	fprintf(stdout, "graph: routes %d size %lu bytes\n",
		graph_count, hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write graph header %lu\n", bytes);
		return bytes;
	}

	elem_hdr.count = graph_count;

	bytes = write(soc_fw->out_fd, &elem_hdr, sizeof(elem_hdr));
	if (bytes != sizeof(elem_hdr)) {
		fprintf(stderr, "error: can't write graph elem header %lu\n", bytes);
		return bytes;
	}

	for (i = 0; i <graph_count; i++) {
		strncpy(elem.sink, graph[i].sink, SND_SOC_FILE_TEXT_SIZE);
		strncpy(elem.source, graph[i].source, SND_SOC_FILE_TEXT_SIZE);
		if (graph[i].control)
			strncpy(elem.control, graph[i].control,
				SND_SOC_FILE_TEXT_SIZE);

		fprintf(stdout, " graph: %s -> %s -> %s\n",
			elem.source, elem.control, elem.sink); 
		bytes = write(soc_fw->out_fd, &elem, sizeof(elem));
		if (bytes != sizeof(elem)) {
			fprintf(stderr, "error: can't write graph elem %lu\n", bytes);
			return bytes;
		}
	}

	return 0;
}

int socfw_import_vendor(struct soc_fw_priv *soc_fw, const char *name, int type)
{
	struct snd_soc_file_hdr hdr;
	size_t bytes;
	char buf[4096];
	int i, chunks, rem;

	memset(&hdr, 0, sizeof(hdr));

	soc_fw->vendor_fd = open(name, O_RDONLY);
	if (soc_fw->vendor_fd < 0) {
		fprintf(stderr, "error: can't open %s %d\n", 
			name, soc_fw->vendor_fd);
		return soc_fw->vendor_fd;
	}

	hdr.magic = SND_SOC_FILE_MAGIC;
	hdr.type = type;
	hdr.size = lseek(soc_fw->vendor_fd, SEEK_END, 0);

	fprintf(stdout, "coeff: %lu bytes\n", hdr.size);

	bytes = write(soc_fw->out_fd, &hdr, sizeof(hdr));
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "error: can't write vendor header %lu\n", bytes);
		return bytes;
	}

	lseek(soc_fw->vendor_fd, SEEK_SET, 0);

	chunks = hdr.size / 4096;
	rem = hdr.size % 4096;

	for (i = 0; i < chunks; i++) {
		bytes = read(soc_fw->vendor_fd, buf, 4096);
		if (bytes < 0 || bytes != 4096) {
			fprintf(stderr, "error: can't read vendor data %lu\n", bytes);
			return bytes;
		}

		bytes = write(soc_fw->out_fd, buf, 4096);
		if (bytes < 0 || bytes != 4096) {
			fprintf(stderr, "error: can't write vendor data %lu\n", bytes);
			return bytes;
		}
	}

	bytes = read(soc_fw->vendor_fd, buf, rem);
	if (bytes < 0 || bytes != rem) {
		fprintf(stderr, "error: can't read vendor data %lu\n", bytes);
		return bytes;
	}

	bytes = write(soc_fw->out_fd, buf, rem);
	if (bytes < 0 || bytes != rem) {
		fprintf(stderr, "error: can't write vendor data %lu\n", bytes);
		return bytes;
	}

	return 0;
}

int socfw_import_plugin(struct soc_fw_priv *soc_fw, const char *name)
{
	struct soc_dapm_plugin *plugin;
	size_t size;
	void *plugin_handle;
	int ret;

	/* load the plugin */
	plugin_handle = dlopen(name, RTLD_LAZY);
	if (!plugin_handle) {
		fprintf(stderr, "error: failed to open %s: %s\n", name,
			dlerror());
		return -EINVAL;
	}

	plugin = dlsym(plugin_handle, "plugin");
	if (!plugin) {
		fprintf(stderr, "error: failed to get symbol. %s\n",
			dlerror());
		dlclose(plugin_handle);
		return -EINVAL;
	}

	/* dump some plugin info */
	fprintf(stdout, "dapm: loaded %s\n", name);
	if (plugin->graph_count > 0)
		fprintf(stdout, " dapm: found graph with %d routes\n",
			plugin->graph_count);
	else
		fprintf(stdout, " dapm: no graph found\n");

	if (plugin->widget_count > 0)
		fprintf(stdout, " dapm: found %d widgets\n",
			plugin->widget_count);
	else
		fprintf(stdout, " dapm: no widgets found\n");

	if (plugin->kcontrol_count > 0)
		fprintf(stdout, " dapm: found %d controls\n",
			plugin->kcontrol_count);
	else
		fprintf(stdout, " dapm: no controls found\n");

	ret = socfw_import_controls(soc_fw, plugin->kcontrols,
		plugin->kcontrol_count);
	if (ret < 0)
		goto out;

	ret = socfw_import_dapm_widgets(soc_fw, plugin->widgets,
		plugin->widget_count);
	if (ret < 0)
		goto out;

	ret = socfw_import_dapm_graph(soc_fw, plugin->graph,
		plugin->graph_count);

out:
	dlclose(plugin_handle);
	return ret;
}

struct soc_fw_priv *socfw_new(const char *name)
{
	struct soc_fw_priv * soc_fw;
	int fd;

	soc_fw = calloc(1, sizeof(struct soc_fw_priv));
	if (!soc_fw)
		return NULL;

	fd = open(name, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0) {
		fprintf(stderr, "failed to open %s err %d\n", name, fd);
		free(soc_fw);
		return NULL;
	}

	soc_fw->out_fd = fd;
	return soc_fw;
}

void socfw_free(struct soc_fw_priv *soc_fw)
{
	close(soc_fw->out_fd);
	free(soc_fw);
}
