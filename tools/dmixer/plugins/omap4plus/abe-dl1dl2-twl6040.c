
struct omap_aess;

#define ul_mux_get_route	NULL
#define ul_mux_put_route	NULL
#define abe_get_mixer	NULL
#define put_mixer	NULL
#define abe_put_switch	NULL
#define volume_get_mixer	NULL
#define volume_put_mixer	NULL
#define volume_get_gain	NULL
#define volume_put_gain	NULL
#define abe_get_mono_mixer	NULL
#define abe_put_mono_mixer	NULL

#include "socfw.h"

#include "abe_def.h"
#include "abe_gain.h"


#define OMAP_ABE_FRONTEND_DAI_MEDIA		0
#define OMAP_ABE_FRONTEND_DAI_MEDIA_CAPTURE	1
#define OMAP_ABE_FRONTEND_DAI_VOICE		2
#define OMAP_ABE_FRONTEND_DAI_TONES		3
#define OMAP_ABE_FRONTEND_DAI_VIBRA		4
#define OMAP_ABE_FRONTEND_DAI_MODEM		5
#define OMAP_ABE_FRONTEND_DAI_LP_MEDIA	6
#define OMAP_ABE_FRONTEND_DAI_NUM		7

/* This must currently match the BE order in DSP */
#define OMAP_ABE_DAI_PDM_UL			0
#define OMAP_ABE_DAI_PDM_DL1			1
#define OMAP_ABE_DAI_PDM_DL2			2
#define OMAP_ABE_DAI_PDM_VIB			3
#define OMAP_ABE_DAI_BT_VX			4
#define OMAP_ABE_DAI_MM_FM			5
#define OMAP_ABE_DAI_MODEM			6
#define OMAP_ABE_DAI_DMIC0			7
#define OMAP_ABE_DAI_DMIC1			8
#define OMAP_ABE_DAI_DMIC2			9
#define OMAP_ABE_DAI_NUM			10

#define OMAP_ABE_BE_PDM_DL1		"PDM-DL1"
#define OMAP_ABE_BE_PDM_UL1		"PDM-UL1"
#define OMAP_ABE_BE_PDM_DL2		"PDM-DL2"
#define OMAP_ABE_BE_PDM_VIB		"PDM-VIB"
#define OMAP_ABE_BE_BT_VX_UL		"BT-VX-UL"
#define OMAP_ABE_BE_BT_VX_DL		"BT-VX-DL"
#define OMAP_ABE_BE_MM_EXT0		"FM-EXT"
#define OMAP_ABE_BE_MM_EXT1		"MODEM-EXT"
#define OMAP_ABE_BE_DMIC0		"DMIC0"
#define OMAP_ABE_BE_DMIC1		"DMIC1"
#define OMAP_ABE_BE_DMIC2		"DMIC2"

#define OMAP_ABE_MIXER(x)		(x)


#define MIX_SWITCH_PDM_DL		OMAP_ABE_MIXER(1)
#define MIX_SWITCH_BT_VX_DL		OMAP_ABE_MIXER(2)
#define MIX_SWITCH_MM_EXT_DL		OMAP_ABE_MIXER(3)
#define MIX_DL1_MONO		OMAP_ABE_MIXER(4)
#define MIX_DL2_MONO		OMAP_ABE_MIXER(5)
#define MIX_AUDUL_MONO		OMAP_ABE_MIXER(6)

#define OMAP_ABE_VIRTUAL_SWITCH	36

#define OMAP_ABE_NUM_MONO_MIXERS	(MIX_AUDUL_MONO - MIX_DL1_MONO + 1)
#define OMAP_ABE_NUM_MIXERS		(MIX_AUDUL_MONO + 1)

#define OMAP_ABE_MUX(x)		(x + 37)

#define MUX_MM_UL10		OMAP_ABE_MUX(0)
#define MUX_MM_UL11		OMAP_ABE_MUX(1)
#define MUX_MM_UL12		OMAP_ABE_MUX(2)
#define MUX_MM_UL13		OMAP_ABE_MUX(3)
#define MUX_MM_UL14		OMAP_ABE_MUX(4)
#define MUX_MM_UL15		OMAP_ABE_MUX(5)
#define MUX_MM_UL16		OMAP_ABE_MUX(6)
#define MUX_MM_UL17		OMAP_ABE_MUX(7)
#define MUX_MM_UL20		OMAP_ABE_MUX(8)
#define MUX_MM_UL21		OMAP_ABE_MUX(9)
#define MUX_VX_UL0		OMAP_ABE_MUX(10)
#define MUX_VX_UL1		OMAP_ABE_MUX(11)

#define OMAP_ABE_NUM_MUXES		(MUX_VX_UL1 - MUX_MM_UL10)

#define OMAP_ABE_WIDGET(x)		(x + OMAP_ABE_NUM_MIXERS + OMAP_ABE_NUM_MUXES)

/* ABE AIF Frontend Widgets */
#define OMAP_ABE_AIF_TONES_DL		OMAP_ABE_WIDGET(0)
#define OMAP_ABE_AIF_VX_DL		OMAP_ABE_WIDGET(1)
#define OMAP_ABE_AIF_VX_UL		OMAP_ABE_WIDGET(2)
#define OMAP_ABE_AIF_MM_UL1		OMAP_ABE_WIDGET(3)
#define OMAP_ABE_AIF_MM_UL2		OMAP_ABE_WIDGET(4)
#define OMAP_ABE_AIF_MM_DL		OMAP_ABE_WIDGET(5)
#define OMAP_ABE_AIF_MM_DL_LP		OMAP_ABE_AIF_MM_DL
#define OMAP_ABE_AIF_VIB_DL		OMAP_ABE_WIDGET(6)
#define OMAP_ABE_AIF_MODEM_DL		OMAP_ABE_WIDGET(7)
#define OMAP_ABE_AIF_MODEM_UL		OMAP_ABE_WIDGET(8)

/* ABE AIF Backend Widgets */
#define OMAP_ABE_AIF_PDM_UL1		OMAP_ABE_WIDGET(9)
#define OMAP_ABE_AIF_PDM_DL1		OMAP_ABE_WIDGET(10)
#define OMAP_ABE_AIF_PDM_DL2		OMAP_ABE_WIDGET(11)
#define OMAP_ABE_AIF_PDM_VIB		OMAP_ABE_WIDGET(12)
#define OMAP_ABE_AIF_BT_VX_UL		OMAP_ABE_WIDGET(13)
#define OMAP_ABE_AIF_BT_VX_DL		OMAP_ABE_WIDGET(14)
#define OMAP_ABE_AIF_MM_EXT_UL	OMAP_ABE_WIDGET(15)
#define OMAP_ABE_AIF_MM_EXT_DL	OMAP_ABE_WIDGET(16)
#define OMAP_ABE_AIF_DMIC0		OMAP_ABE_WIDGET(17)
#define OMAP_ABE_AIF_DMIC1		OMAP_ABE_WIDGET(18)
#define OMAP_ABE_AIF_DMIC2		OMAP_ABE_WIDGET(19)

/* ABE ROUTE_UL MUX Widgets */
#define OMAP_ABE_MUX_UL00		OMAP_ABE_WIDGET(20)
#define OMAP_ABE_MUX_UL01		OMAP_ABE_WIDGET(21)
#define OMAP_ABE_MUX_UL02		OMAP_ABE_WIDGET(22)
#define OMAP_ABE_MUX_UL03		OMAP_ABE_WIDGET(23)
#define OMAP_ABE_MUX_UL04		OMAP_ABE_WIDGET(24)
#define OMAP_ABE_MUX_UL05		OMAP_ABE_WIDGET(25)
#define OMAP_ABE_MUX_UL06		OMAP_ABE_WIDGET(26)
#define OMAP_ABE_MUX_UL07		OMAP_ABE_WIDGET(27)
#define OMAP_ABE_MUX_UL10		OMAP_ABE_WIDGET(28)
#define OMAP_ABE_MUX_UL11		OMAP_ABE_WIDGET(29)
#define OMAP_ABE_MUX_VX00		OMAP_ABE_WIDGET(30)
#define OMAP_ABE_MUX_VX01		OMAP_ABE_WIDGET(31)

/* ABE Volume and Mixer Widgets */
#define OMAP_ABE_MIXER_DL1		OMAP_ABE_WIDGET(32)
#define OMAP_ABE_MIXER_DL2		OMAP_ABE_WIDGET(33)
#define OMAP_ABE_VOLUME_DL1		OMAP_ABE_WIDGET(34)
#define OMAP_ABE_MIXER_AUDIO_UL	OMAP_ABE_WIDGET(35)
#define OMAP_ABE_MIXER_VX_REC		OMAP_ABE_WIDGET(36)
#define OMAP_ABE_MIXER_SDT		OMAP_ABE_WIDGET(37)
#define OMAP_ABE_VSWITCH_DL1_PDM	OMAP_ABE_WIDGET(38)
#define OMAP_ABE_VSWITCH_DL1_BT_VX	OMAP_ABE_WIDGET(39)
#define OMAP_ABE_VSWITCH_DL1_MM_EXT	OMAP_ABE_WIDGET(40)

#define OMAP_ABE_NUM_WIDGETS		(OMAP_ABE_VSWITCH_DL1_MM_EXT - OMAP_ABE_AIF_TONES_DL)
#define OMAP_ABE_WIDGET_LAST		OMAP_ABE_VSWITCH_DL1_MM_EXT

#define OMAP_ABE_NUM_DAPM_REG		\
	(OMAP_ABE_NUM_MIXERS + OMAP_ABE_NUM_MUXES + OMAP_ABE_NUM_WIDGETS)

#define OMAP_ABE_ROUTES_UL		14

#define OMAP_ABE_OPP_25		0
#define OMAP_ABE_OPP_50		1
#define OMAP_ABE_OPP_100		2
#define OMAP_ABE_OPP_COUNT	3

/* Media DL1 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(mm_dl1_tlv, -12000, 100, 3000);

/* Media DL1 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(tones_dl1_tlv, -12000, 100, 3000);

/* Media DL1 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(voice_dl1_tlv, -12000, 100, 3000);

/* Media DL1 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(capture_dl1_tlv, -12000, 100, 3000);

/* Media DL2 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(mm_dl2_tlv, -12000, 100, 3000);

/* Media DL2 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(tones_dl2_tlv, -12000, 100, 3000);

/* Media DL2 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(voice_dl2_tlv, -12000, 100, 3000);

/* Media DL2 volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(capture_dl2_tlv, -12000, 100, 3000);

/* SDT volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(sdt_ul_tlv, -12000, 100, 3000);

/* SDT volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(sdt_dl_tlv, -12000, 100, 3000);

/* AUDUL volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(audul_mm_tlv, -12000, 100, 3000);

/* AUDUL volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(audul_tones_tlv, -12000, 100, 3000);

/* AUDUL volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(audul_vx_ul_tlv, -12000, 100, 3000);

/* AUDUL volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(audul_vx_dl_tlv, -12000, 100, 3000);

/* VXREC volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(vxrec_mm_dl_tlv, -12000, 100, 3000);

/* VXREC volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(vxrec_tones_tlv, -12000, 100, 3000);

/* VXREC volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(vxrec_vx_dl_tlv, -12000, 100, 3000);

/* VXREC volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(vxrec_vx_ul_tlv, -12000, 100, 3000);

/* DMIC volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(dmic_tlv, -12000, 100, 3000);

/* BT UL volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(btul_tlv, -12000, 100, 3000);

/* AMIC volume control from -120 to 30 dB in 1 dB steps */
static DECLARE_TLV_DB_SCALE(amic_tlv, -12000, 100, 3000);

static const char *route_ul_texts[] = {
	"None", "DMic0L", "DMic0R", "DMic1L", "DMic1R", "DMic2L", "DMic2R",
	"BT Left", "BT Right", "MMExt Left", "MMExt Right", "AMic0", "AMic1",
	"VX Left", "VX Right"
};

/* ROUTE_UL Mux table */
static const struct soc_enum abe_enum[] = {
		SOC_ENUM_SINGLE(MUX_MM_UL10, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL11, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL12, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL13, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL14, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL15, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL16, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL17, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL20, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_MM_UL21, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_VX_UL0, 0, 15, route_ul_texts),
		SOC_ENUM_SINGLE(MUX_VX_UL1, 0, 15, route_ul_texts),
};

static const struct snd_kcontrol_new mm_ul00_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[0],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul01_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[1],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul02_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[2],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul03_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[3],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul04_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[4],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul05_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[5],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul06_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[6],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul07_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[7],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul10_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[8],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_ul11_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[9],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_vx0_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[10],
	ul_mux_get_route, ul_mux_put_route);

static const struct snd_kcontrol_new mm_vx1_control =
	SOC_DAPM_ENUM_EXT("Route", abe_enum[11],
	ul_mux_get_route, ul_mux_put_route);

/* DL1 mixer paths */
static const struct snd_kcontrol_new dl1_mixer_controls[] = {
	SOC_SINGLE_EXT("Tones", OMAP_AESS_MIXDL1_TONES, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Voice", OMAP_AESS_MIXDL1_VX_DL, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Capture", OMAP_AESS_MIXDL1_MM_UL2, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Multimedia", OMAP_AESS_MIXDL1_MM_DL, 0, 1, 0,
		abe_get_mixer, put_mixer),
};

/* DL2 mixer paths */
static const struct snd_kcontrol_new dl2_mixer_controls[] = {
	SOC_SINGLE_EXT("Tones", OMAP_AESS_MIXDL2_TONES, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Voice", OMAP_AESS_MIXDL2_VX_DL, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Capture", OMAP_AESS_MIXDL2_MM_UL2, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Multimedia", OMAP_AESS_MIXDL2_MM_DL, 0, 1, 0,
		abe_get_mixer, put_mixer),
};

/* AUDUL ("Voice Capture Mixer") mixer paths */
static const struct snd_kcontrol_new audio_ul_mixer_controls[] = {
	SOC_SINGLE_EXT("Tones Playback", OMAP_AESS_MIXAUDUL_TONES, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Media Playback", OMAP_AESS_MIXAUDUL_MM_DL, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Capture", OMAP_AESS_MIXAUDUL_UPLINK, 0, 1, 0,
		abe_get_mixer, put_mixer),
};

/* VXREC ("Capture Mixer")  mixer paths */
static const struct snd_kcontrol_new vx_rec_mixer_controls[] = {
	SOC_SINGLE_EXT("Tones", OMAP_AESS_MIXVXREC_TONES, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Voice Playback", OMAP_AESS_MIXVXREC_VX_DL,
		0, 1, 0, abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Voice Capture", OMAP_AESS_MIXVXREC_VX_UL,
		0, 1, 0, abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Media Playback", OMAP_AESS_MIXVXREC_MM_DL,
		0, 1, 0, abe_get_mixer, put_mixer),
};

/* SDT ("Sidetone Mixer") mixer paths */
static const struct snd_kcontrol_new sdt_mixer_controls[] = {
	SOC_SINGLE_EXT("Capture", OMAP_AESS_MIXSDT_UL, 0, 1, 0,
		abe_get_mixer, put_mixer),
	SOC_SINGLE_EXT("Playback", OMAP_AESS_MIXSDT_DL, 0, 1, 0,
		abe_get_mixer, put_mixer),
};

/* Virtual PDM_DL Switch */
static const struct snd_kcontrol_new pdm_dl1_switch_controls =
	SOC_SINGLE_EXT("Switch", OMAP_ABE_VIRTUAL_SWITCH, MIX_SWITCH_PDM_DL, 1, 0,
			abe_get_mixer, abe_put_switch);

/* Virtual BT_VX_DL Switch */
static const struct snd_kcontrol_new bt_vx_dl_switch_controls =
	SOC_SINGLE_EXT("Switch", OMAP_ABE_VIRTUAL_SWITCH, MIX_SWITCH_BT_VX_DL, 1, 0,
			abe_get_mixer, abe_put_switch);

/* Virtual MM_EXT_DL Switch */
static const struct snd_kcontrol_new mm_ext_dl_switch_controls =
	SOC_SINGLE_EXT("Switch", OMAP_ABE_VIRTUAL_SWITCH, MIX_SWITCH_MM_EXT_DL, 1, 0,
			abe_get_mixer, abe_put_switch);

static const struct snd_kcontrol_new controls[] = {
	/* DL1 mixer gains */
	SOC_SINGLE_EXT_TLV("DL1 Media Playback Volume",
		OMAP_AESS_MIXDL1_MM_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, mm_dl1_tlv),
	SOC_SINGLE_EXT_TLV("DL1 Tones Playback Volume",
		OMAP_AESS_MIXDL1_TONES, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, tones_dl1_tlv),
	SOC_SINGLE_EXT_TLV("DL1 Voice Playback Volume",
		OMAP_AESS_MIXDL1_VX_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, voice_dl1_tlv),
	SOC_SINGLE_EXT_TLV("DL1 Capture Playback Volume",
		OMAP_AESS_MIXDL1_MM_UL2, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, capture_dl1_tlv),

	/* DL2 mixer gains */
	SOC_SINGLE_EXT_TLV("DL2 Media Playback Volume",
		OMAP_AESS_MIXDL2_MM_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, mm_dl2_tlv),
	SOC_SINGLE_EXT_TLV("DL2 Tones Playback Volume",
		OMAP_AESS_MIXDL2_TONES, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, tones_dl2_tlv),
	SOC_SINGLE_EXT_TLV("DL2 Voice Playback Volume",
		OMAP_AESS_MIXDL2_VX_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, voice_dl2_tlv),
	SOC_SINGLE_EXT_TLV("DL2 Capture Playback Volume",
		OMAP_AESS_MIXDL2_MM_UL2, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, capture_dl2_tlv),

	/* VXREC mixer gains */
	SOC_SINGLE_EXT_TLV("VXREC Media Volume",
		OMAP_AESS_MIXVXREC_MM_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, vxrec_mm_dl_tlv),
	SOC_SINGLE_EXT_TLV("VXREC Tones Volume",
		OMAP_AESS_MIXVXREC_TONES, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, vxrec_tones_tlv),
	SOC_SINGLE_EXT_TLV("VXREC Voice DL Volume",
		OMAP_AESS_MIXVXREC_VX_UL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, vxrec_vx_dl_tlv),
	SOC_SINGLE_EXT_TLV("VXREC Voice UL Volume",
		OMAP_AESS_MIXVXREC_VX_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, vxrec_vx_ul_tlv),

	/* AUDUL mixer gains */
	SOC_SINGLE_EXT_TLV("AUDUL Media Volume",
		OMAP_AESS_MIXAUDUL_MM_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, audul_mm_tlv),
	SOC_SINGLE_EXT_TLV("AUDUL Tones Volume",
		OMAP_AESS_MIXAUDUL_TONES, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, audul_tones_tlv),
	SOC_SINGLE_EXT_TLV("AUDUL Voice UL Volume",
		OMAP_AESS_MIXAUDUL_UPLINK, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, audul_vx_ul_tlv),
	SOC_SINGLE_EXT_TLV("AUDUL Voice DL Volume",
		OMAP_AESS_MIXAUDUL_VX_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, audul_vx_dl_tlv),

	/* SDT mixer gains */
	SOC_SINGLE_EXT_TLV("SDT UL Volume",
		OMAP_AESS_MIXSDT_UL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, sdt_ul_tlv),
	SOC_SINGLE_EXT_TLV("SDT DL Volume",
		OMAP_AESS_MIXSDT_DL, 0, 149, 0,
		volume_get_mixer, volume_put_mixer, sdt_dl_tlv),

	/* DMIC gains */
	SOC_DOUBLE_EXT_TLV("DMIC1 UL Volume",
		GAINS_DMIC1, OMAP_AESS_GAIN_DMIC1_LEFT, OMAP_AESS_GAIN_DMIC1_RIGHT, 149, 0,
		volume_get_gain, volume_put_gain, dmic_tlv),

	SOC_DOUBLE_EXT_TLV("DMIC2 UL Volume",
		GAINS_DMIC2, OMAP_AESS_GAIN_DMIC2_LEFT, OMAP_AESS_GAIN_DMIC2_RIGHT, 149, 0,
		volume_get_gain, volume_put_gain, dmic_tlv),

	SOC_DOUBLE_EXT_TLV("DMIC3 UL Volume",
		GAINS_DMIC3, OMAP_AESS_GAIN_DMIC3_LEFT, OMAP_AESS_GAIN_DMIC3_RIGHT, 149, 0,
		volume_get_gain, volume_put_gain, dmic_tlv),

	SOC_DOUBLE_EXT_TLV("AMIC UL Volume",
		GAINS_AMIC, OMAP_AESS_GAIN_AMIC_LEFT, OMAP_AESS_GAIN_AMIC_RIGHT, 149, 0,
		volume_get_gain, volume_put_gain, amic_tlv),

	SOC_DOUBLE_EXT_TLV("BT UL Volume",
		GAINS_BTUL, OMAP_AESS_GAIN_BTUL_LEFT, OMAP_AESS_GAIN_BTUL_RIGHT, 149, 0,
		volume_get_gain, volume_put_gain, btul_tlv),
	SOC_SINGLE_EXT("DL1 Mono Mixer", MIXDL1, MIX_DL1_MONO, 1, 0,
		abe_get_mono_mixer, abe_put_mono_mixer),
	SOC_SINGLE_EXT("DL2 Mono Mixer", MIXDL2, MIX_DL2_MONO, 1, 0,
		abe_get_mono_mixer, abe_put_mono_mixer),
	SOC_SINGLE_EXT("AUDUL Mono Mixer", MIXAUDUL, MIX_AUDUL_MONO, 1, 0,
		abe_get_mono_mixer, abe_put_mono_mixer),
};

static const struct snd_soc_dapm_widget widgets[] = {

	/* Frontend AIFs */
	SND_SOC_DAPM_AIF_IN("TONES_DL", NULL, 0,
			OMAP_ABE_AIF_TONES_DL, OMAP_ABE_OPP_25, 0),

	SND_SOC_DAPM_AIF_IN("VX_DL", NULL, 0,
			OMAP_ABE_AIF_VX_DL, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_OUT("VX_UL", NULL, 0,
			OMAP_ABE_AIF_VX_UL, OMAP_ABE_OPP_50, 0),

	SND_SOC_DAPM_AIF_OUT("MM_UL1", NULL, 0,
			OMAP_ABE_AIF_MM_UL1, OMAP_ABE_OPP_100, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UL2", NULL, 0,
			OMAP_ABE_AIF_MM_UL2, OMAP_ABE_OPP_50, 0),

	SND_SOC_DAPM_AIF_IN("MM_DL", NULL, 0,
			OMAP_ABE_AIF_MM_DL, OMAP_ABE_OPP_25, 0),

	SND_SOC_DAPM_AIF_IN("VIB_DL", NULL, 0,
			OMAP_ABE_AIF_VIB_DL, OMAP_ABE_OPP_100, 0),
	SND_SOC_DAPM_AIF_IN("MODEM_DL", NULL, 0,
			OMAP_ABE_AIF_MODEM_DL, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_OUT("MODEM_UL", NULL, 0,
			OMAP_ABE_AIF_MODEM_UL, OMAP_ABE_OPP_50, 0),

	/* Backend DAIs  */
	SND_SOC_DAPM_AIF_IN("PDM_UL1", NULL, 0,
			OMAP_ABE_AIF_PDM_UL1, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_OUT("PDM_DL1", NULL, 0,
			OMAP_ABE_AIF_PDM_DL1, OMAP_ABE_OPP_25, 0),
	SND_SOC_DAPM_AIF_OUT("PDM_DL2", NULL, 0,
			OMAP_ABE_AIF_PDM_DL2, OMAP_ABE_OPP_100, 0),
	SND_SOC_DAPM_AIF_OUT("PDM_VIB", NULL, 0,
			OMAP_ABE_AIF_PDM_VIB, OMAP_ABE_OPP_100, 0),
	SND_SOC_DAPM_AIF_IN("BT_VX_UL", "BT Capture", 0,
			OMAP_ABE_AIF_BT_VX_UL, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_OUT("BT_VX_DL", "BT Playback", 0,
			OMAP_ABE_AIF_BT_VX_DL, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_IN("MM_EXT_UL", "FM Capture", 0,
			OMAP_ABE_AIF_MM_EXT_UL, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_OUT("MM_EXT_DL", "FM Playback", 0,
			OMAP_ABE_AIF_MM_EXT_DL, OMAP_ABE_OPP_25, 0),
	SND_SOC_DAPM_AIF_IN("DMIC0", "DMIC0 Capture", 0,
			OMAP_ABE_AIF_DMIC0, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_IN("DMIC1", "DMIC1 Capture", 0,
			OMAP_ABE_AIF_DMIC1, OMAP_ABE_OPP_50, 0),
	SND_SOC_DAPM_AIF_IN("DMIC2", "DMIC2 Capture", 0,
			OMAP_ABE_AIF_DMIC2, OMAP_ABE_OPP_50, 0),

	/* ROUTE_UL Capture Muxes */
	SND_SOC_DAPM_MUX("MUX_UL00",
			OMAP_ABE_MUX_UL00, OMAP_ABE_OPP_50, 0, &mm_ul00_control),
	SND_SOC_DAPM_MUX("MUX_UL01",
			OMAP_ABE_MUX_UL01, OMAP_ABE_OPP_50, 0, &mm_ul01_control),
	SND_SOC_DAPM_MUX("MUX_UL02",
			OMAP_ABE_MUX_UL02, OMAP_ABE_OPP_50, 0, &mm_ul02_control),
	SND_SOC_DAPM_MUX("MUX_UL03",
			OMAP_ABE_MUX_UL03, OMAP_ABE_OPP_50, 0, &mm_ul03_control),
	SND_SOC_DAPM_MUX("MUX_UL04",
			OMAP_ABE_MUX_UL04, OMAP_ABE_OPP_50, 0, &mm_ul04_control),
	SND_SOC_DAPM_MUX("MUX_UL05",
			OMAP_ABE_MUX_UL05, OMAP_ABE_OPP_50, 0, &mm_ul05_control),
	SND_SOC_DAPM_MUX("MUX_UL06",
			OMAP_ABE_MUX_UL06, OMAP_ABE_OPP_50, 0, &mm_ul06_control),
	SND_SOC_DAPM_MUX("MUX_UL07",
			OMAP_ABE_MUX_UL07, OMAP_ABE_OPP_50, 0, &mm_ul07_control),
	SND_SOC_DAPM_MUX("MUX_UL10",
			OMAP_ABE_MUX_UL10, OMAP_ABE_OPP_50, 0, &mm_ul10_control),
	SND_SOC_DAPM_MUX("MUX_UL11",
			OMAP_ABE_MUX_UL11, OMAP_ABE_OPP_50, 0, &mm_ul11_control),
	SND_SOC_DAPM_MUX("MUX_VX0",
			OMAP_ABE_MUX_VX00, OMAP_ABE_OPP_50, 0, &mm_vx0_control),
	SND_SOC_DAPM_MUX("MUX_VX1",
			OMAP_ABE_MUX_VX01, OMAP_ABE_OPP_50, 0, &mm_vx1_control),

	/* DL1 & DL2 Playback Mixers */
	SND_SOC_DAPM_MIXER("DL1 Mixer",
			OMAP_ABE_MIXER_DL1, OMAP_ABE_OPP_25, 0, dl1_mixer_controls,
			ARRAY_SIZE(dl1_mixer_controls)),
	SND_SOC_DAPM_MIXER("DL2 Mixer",
			OMAP_ABE_MIXER_DL2, OMAP_ABE_OPP_100, 0, dl2_mixer_controls,
			ARRAY_SIZE(dl2_mixer_controls)),

	/* DL1 Mixer Input volumes ?????*/
	SND_SOC_DAPM_PGA("DL1 Media Volume",
			OMAP_ABE_VOLUME_DL1, 0, 0, NULL, 0),

	/* AUDIO_UL_MIXER */
	SND_SOC_DAPM_MIXER("Voice Capture Mixer",
			OMAP_ABE_MIXER_AUDIO_UL, OMAP_ABE_OPP_50, 0,
			audio_ul_mixer_controls, ARRAY_SIZE(audio_ul_mixer_controls)),

	/* VX_REC_MIXER */
	SND_SOC_DAPM_MIXER("Capture Mixer",
			OMAP_ABE_MIXER_VX_REC, OMAP_ABE_OPP_50, 0, vx_rec_mixer_controls,
			ARRAY_SIZE(vx_rec_mixer_controls)),

	/* SDT_MIXER  */
	SND_SOC_DAPM_MIXER("Sidetone Mixer",
			OMAP_ABE_MIXER_SDT, OMAP_ABE_OPP_25, 0, sdt_mixer_controls,
			ARRAY_SIZE(sdt_mixer_controls)),

	/*
	 * The Following three are virtual switches to select the output port
	 * after DL1 Gain.
	 */

	/* Virtual PDM_DL1 Switch */
	SND_SOC_DAPM_MIXER("DL1 PDM", OMAP_ABE_VSWITCH_DL1_PDM,
			OMAP_ABE_OPP_25, 0, &pdm_dl1_switch_controls, 1),

	/* Virtual BT_VX_DL Switch */
	SND_SOC_DAPM_MIXER("DL1 BT_VX", OMAP_ABE_VSWITCH_DL1_BT_VX,
			OMAP_ABE_OPP_50, 0, &bt_vx_dl_switch_controls, 1),

	/* Virtual MM_EXT_DL Switch */
	SND_SOC_DAPM_MIXER("DL1 MM_EXT", OMAP_ABE_VSWITCH_DL1_MM_EXT,
			OMAP_ABE_OPP_50, 0, &mm_ext_dl_switch_controls, 1),

	/* Virtuals to join our capture sources */
	SND_SOC_DAPM_MIXER("Sidetone Capture VMixer", SND_SOC_NOPM, 0, 0, NULL, 0),
	SND_SOC_DAPM_MIXER("Voice Capture VMixer", SND_SOC_NOPM, 0, 0, NULL, 0),
	SND_SOC_DAPM_MIXER("DL1 Capture VMixer", SND_SOC_NOPM, 0, 0, NULL, 0),
	SND_SOC_DAPM_MIXER("DL2 Capture VMixer", SND_SOC_NOPM, 0, 0, NULL, 0),

	/* Virtual MODEM and VX_UL mixer */
	SND_SOC_DAPM_MIXER("VX UL VMixer", SND_SOC_NOPM, 0, 0, NULL, 0),
	SND_SOC_DAPM_MIXER("VX DL VMixer", SND_SOC_NOPM, 0, 0, NULL, 0),

	/* Virtual MM1 and MM LP mixer */
	SND_SOC_DAPM_MIXER("MM VMixer", SND_SOC_NOPM, 0, 0, NULL, 0),

	/* Virtual Pins to force backends ON atm */
	SND_SOC_DAPM_OUTPUT("BE_OUT"),
	SND_SOC_DAPM_INPUT("BE_IN"),
};

static const struct snd_soc_dapm_route graph[] = {

	/* MUX_UL00 - ROUTE_UL - Chan 0  */
	{"MUX_UL00", "DMic0L", "DMIC0"},
	{"MUX_UL00", "DMic0R", "DMIC0"},
	{"MUX_UL00", "DMic1L", "DMIC1"},
	{"MUX_UL00", "DMic1R", "DMIC1"},
	{"MUX_UL00", "DMic2L", "DMIC2"},
	{"MUX_UL00", "DMic2R", "DMIC2"},
	{"MUX_UL00", "BT Left", "BT_VX_UL"},
	{"MUX_UL00", "BT Right", "BT_VX_UL"},
	{"MUX_UL00", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL00", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL00", "AMic0", "PDM_UL1"},
	{"MUX_UL00", "AMic1", "PDM_UL1"},
	{"MUX_UL00", "VX Left", "Capture Mixer"},
	{"MUX_UL00", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL00"},

	/* MUX_UL01 - ROUTE_UL - Chan 1  */
	{"MUX_UL01", "DMic0L", "DMIC0"},
	{"MUX_UL01", "DMic0R", "DMIC0"},
	{"MUX_UL01", "DMic1L", "DMIC1"},
	{"MUX_UL01", "DMic1R", "DMIC1"},
	{"MUX_UL01", "DMic2L", "DMIC2"},
	{"MUX_UL01", "DMic2R", "DMIC2"},
	{"MUX_UL01", "BT Left", "BT_VX_UL"},
	{"MUX_UL01", "BT Right", "BT_VX_UL"},
	{"MUX_UL01", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL01", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL01", "AMic0", "PDM_UL1"},
	{"MUX_UL01", "AMic1", "PDM_UL1"},
	{"MUX_UL01", "VX Left", "Capture Mixer"},
	{"MUX_UL01", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL01"},

	/* MUX_UL02 - ROUTE_UL - Chan 2  */
	{"MUX_UL02", "DMic0L", "DMIC0"},
	{"MUX_UL02", "DMic0R", "DMIC0"},
	{"MUX_UL02", "DMic1L", "DMIC1"},
	{"MUX_UL02", "DMic1R", "DMIC1"},
	{"MUX_UL02", "DMic2L", "DMIC2"},
	{"MUX_UL02", "DMic2R", "DMIC2"},
	{"MUX_UL02", "BT Left", "BT_VX_UL"},
	{"MUX_UL02", "BT Right", "BT_VX_UL"},
	{"MUX_UL02", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL02", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL02", "AMic0", "PDM_UL1"},
	{"MUX_UL02", "AMic1", "PDM_UL1"},
	{"MUX_UL02", "VX Left", "Capture Mixer"},
	{"MUX_UL02", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL02"},

	/* MUX_UL03 - ROUTE_UL - Chan 3  */
	{"MUX_UL03", "DMic0L", "DMIC0"},
	{"MUX_UL03", "DMic0R", "DMIC0"},
	{"MUX_UL03", "DMic1L", "DMIC1"},
	{"MUX_UL03", "DMic1R", "DMIC1"},
	{"MUX_UL03", "DMic2L", "DMIC2"},
	{"MUX_UL03", "DMic2R", "DMIC2"},
	{"MUX_UL03", "BT Left", "BT_VX_UL"},
	{"MUX_UL03", "BT Right", "BT_VX_UL"},
	{"MUX_UL03", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL03", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL03", "AMic0", "PDM_UL1"},
	{"MUX_UL03", "AMic1", "PDM_UL1"},
	{"MUX_UL03", "VX Left", "Capture Mixer"},
	{"MUX_UL03", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL03"},

	/* MUX_UL04 - ROUTE_UL - Chan 4  */
	{"MUX_UL04", "DMic0L", "DMIC0"},
	{"MUX_UL04", "DMic0R", "DMIC0"},
	{"MUX_UL04", "DMic1L", "DMIC1"},
	{"MUX_UL04", "DMic1R", "DMIC1"},
	{"MUX_UL04", "DMic2L", "DMIC2"},
	{"MUX_UL04", "DMic2R", "DMIC2"},
	{"MUX_UL04", "BT Left", "BT_VX_UL"},
	{"MUX_UL04", "BT Right", "BT_VX_UL"},
	{"MUX_UL04", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL04", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL04", "AMic0", "PDM_UL1"},
	{"MUX_UL04", "AMic1", "PDM_UL1"},
	{"MUX_UL04", "VX Left", "Capture Mixer"},
	{"MUX_UL04", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL04"},

	/* MUX_UL05 - ROUTE_UL - Chan 5  */
	{"MUX_UL05", "DMic0L", "DMIC0"},
	{"MUX_UL05", "DMic0R", "DMIC0"},
	{"MUX_UL05", "DMic1L", "DMIC1"},
	{"MUX_UL05", "DMic1R", "DMIC1"},
	{"MUX_UL05", "DMic2L", "DMIC2"},
	{"MUX_UL05", "DMic2R", "DMIC2"},
	{"MUX_UL05", "BT Left", "BT_VX_UL"},
	{"MUX_UL05", "BT Right", "BT_VX_UL"},
	{"MUX_UL05", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL05", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL05", "AMic0", "PDM_UL1"},
	{"MUX_UL05", "AMic1", "PDM_UL1"},
	{"MUX_UL05", "VX Left", "Capture Mixer"},
	{"MUX_UL05", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL05"},

	/* MUX_UL06 - ROUTE_UL - Chan 6  */
	{"MUX_UL06", "DMic0L", "DMIC0"},
	{"MUX_UL06", "DMic0R", "DMIC0"},
	{"MUX_UL06", "DMic1L", "DMIC1"},
	{"MUX_UL06", "DMic1R", "DMIC1"},
	{"MUX_UL06", "DMic2L", "DMIC2"},
	{"MUX_UL06", "DMic2R", "DMIC2"},
	{"MUX_UL06", "BT Left", "BT_VX_UL"},
	{"MUX_UL06", "BT Right", "BT_VX_UL"},
	{"MUX_UL06", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL06", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL06", "AMic0", "PDM_UL1"},
	{"MUX_UL06", "AMic1", "PDM_UL1"},
	{"MUX_UL06", "VX Left", "Capture Mixer"},
	{"MUX_UL06", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL06"},

	/* MUX_UL07 - ROUTE_UL - Chan 7  */
	{"MUX_UL07", "DMic0L", "DMIC0"},
	{"MUX_UL07", "DMic0R", "DMIC0"},
	{"MUX_UL07", "DMic1L", "DMIC1"},
	{"MUX_UL07", "DMic1R", "DMIC1"},
	{"MUX_UL07", "DMic2L", "DMIC2"},
	{"MUX_UL07", "DMic2R", "DMIC2"},
	{"MUX_UL07", "BT Left", "BT_VX_UL"},
	{"MUX_UL07", "BT Right", "BT_VX_UL"},
	{"MUX_UL07", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL07", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL07", "AMic0", "PDM_UL1"},
	{"MUX_UL07", "AMic1", "PDM_UL1"},
	{"MUX_UL07", "VX Left", "Capture Mixer"},
	{"MUX_UL07", "VX Right", "Capture Mixer"},
	{"MM_UL1", NULL, "MUX_UL07"},

	/* MUX_UL10 - ROUTE_UL - Chan 0  */
	{"MUX_UL10", "DMic0L", "DMIC0"},
	{"MUX_UL10", "DMic0R", "DMIC0"},
	{"MUX_UL10", "DMic1L", "DMIC1"},
	{"MUX_UL10", "DMic1R", "DMIC1"},
	{"MUX_UL10", "DMic2L", "DMIC2"},
	{"MUX_UL10", "DMic2R", "DMIC2"},
	{"MUX_UL10", "BT Left", "BT_VX_UL"},
	{"MUX_UL10", "BT Right", "BT_VX_UL"},
	{"MUX_UL10", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL10", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL10", "AMic0", "PDM_UL1"},
	{"MUX_UL10", "AMic1", "PDM_UL1"},
	{"MUX_UL10", "VX Left", "Capture Mixer"},
	{"MUX_UL10", "VX Right", "Capture Mixer"},
	{"MM_UL2", NULL, "MUX_UL10"},

	/* MUX_UL11 - ROUTE_UL - Chan 1  */
	{"MUX_UL11", "DMic0L", "DMIC0"},
	{"MUX_UL11", "DMic0R", "DMIC0"},
	{"MUX_UL11", "DMic1L", "DMIC1"},
	{"MUX_UL11", "DMic1R", "DMIC1"},
	{"MUX_UL11", "DMic2L", "DMIC2"},
	{"MUX_UL11", "DMic2R", "DMIC2"},
	{"MUX_UL11", "BT Left", "BT_VX_UL"},
	{"MUX_UL11", "BT Right", "BT_VX_UL"},
	{"MUX_UL11", "MMExt Left", "MM_EXT_UL"},
	{"MUX_UL11", "MMExt Right", "MM_EXT_UL"},
	{"MUX_UL11", "AMic0", "PDM_UL1"},
	{"MUX_UL11", "AMic1", "PDM_UL1"},
	{"MUX_UL11", "VX Left", "Capture Mixer"},
	{"MUX_UL11", "VX Right", "Capture Mixer"},
	{"MM_UL2", NULL, "MUX_UL11"},

	/* MUX_VX0 - ROUTE_UL - Chan 0  */
	{"MUX_VX0", "DMic0L", "DMIC0"},
	{"MUX_VX0", "DMic0R", "DMIC0"},
	{"MUX_VX0", "DMic1L", "DMIC1"},
	{"MUX_VX0", "DMic1R", "DMIC1"},
	{"MUX_VX0", "DMic2L", "DMIC2"},
	{"MUX_VX0", "DMic2R", "DMIC2"},
	{"MUX_VX0", "BT Left", "BT_VX_UL"},
	{"MUX_VX0", "BT Right", "BT_VX_UL"},
	{"MUX_VX0", "MMExt Left", "MM_EXT_UL"},
	{"MUX_VX0", "MMExt Right", "MM_EXT_UL"},
	{"MUX_VX0", "AMic0", "PDM_UL1"},
	{"MUX_VX0", "AMic1", "PDM_UL1"},
	{"MUX_VX0", "VX Left", "Capture Mixer"},
	{"MUX_VX0", "VX Right", "Capture Mixer"},

	/* MUX_VX1 - ROUTE_UL - Chan 1 */
	{"MUX_VX1", "DMic0L", "DMIC0"},
	{"MUX_VX1", "DMic0R", "DMIC0"},
	{"MUX_VX1", "DMic1L", "DMIC1"},
	{"MUX_VX1", "DMic1R", "DMIC1"},
	{"MUX_VX1", "DMic2L", "DMIC2"},
	{"MUX_VX1", "DMic2R", "DMIC2"},
	{"MUX_VX1", "BT Left", "BT_VX_UL"},
	{"MUX_VX1", "BT Right", "BT_VX_UL"},
	{"MUX_VX1", "MMExt Left", "MM_EXT_UL"},
	{"MUX_VX1", "MMExt Right", "MM_EXT_UL"},
	{"MUX_VX1", "AMic0", "PDM_UL1"},
	{"MUX_VX1", "AMic1", "PDM_UL1"},
	{"MUX_VX1", "VX Left", "Capture Mixer"},
	{"MUX_VX1", "VX Right", "Capture Mixer"},

	/* Headset (DL1)  playback path */
	{"DL1 Mixer", "Tones", "TONES_DL"},
	{"DL1 Mixer", "Voice", "VX DL VMixer"},
	{"DL1 Mixer", "Capture", "DL1 Capture VMixer"},
	{"DL1 Capture VMixer", NULL, "MUX_UL10"},
	{"DL1 Capture VMixer", NULL, "MUX_UL11"},
	{"DL1 Mixer", "Multimedia", "MM_DL"},

	/* Sidetone Mixer */
	{"Sidetone Mixer", "Playback", "DL1 Mixer"},
	{"Sidetone Mixer", "Capture", "Sidetone Capture VMixer"},
	{"Sidetone Capture VMixer", NULL, "MUX_VX0"},
	{"Sidetone Capture VMixer", NULL, "MUX_VX1"},

	/* Playback Output selection after DL1 Gain */
	{"DL1 BT_VX", "Switch", "Sidetone Mixer"},
	{"DL1 MM_EXT", "Switch", "Sidetone Mixer"},
	{"DL1 PDM", "Switch", "Sidetone Mixer"},
	{"PDM_DL1", NULL, "DL1 PDM"},
	{"BT_VX_DL", NULL, "DL1 BT_VX"},
	{"MM_EXT_DL", NULL, "DL1 MM_EXT"},

	/* Handsfree (DL2) playback path */
	{"DL2 Mixer", "Tones", "TONES_DL"},
	{"DL2 Mixer", "Voice", "VX DL VMixer"},
	{"DL2 Mixer", "Capture", "DL2 Capture VMixer"},
	{"DL2 Capture VMixer", NULL, "MUX_UL10"},
	{"DL2 Capture VMixer", NULL, "MUX_UL11"},
	{"DL2 Mixer", "Multimedia", "MM_DL"},
	{"PDM_DL2", NULL, "DL2 Mixer"},

	/* VxREC Mixer */
	{"Capture Mixer", "Tones", "TONES_DL"},
	{"Capture Mixer", "Voice Playback", "VX DL VMixer"},
	{"Capture Mixer", "Voice Capture", "VX UL VMixer"},
	{"Capture Mixer", "Media Playback", "MM_DL"},

	/* Audio UL mixer */
	{"Voice Capture Mixer", "Tones Playback", "TONES_DL"},
	{"Voice Capture Mixer", "Media Playback", "MM_DL"},
	{"Voice Capture Mixer", "Capture", "Voice Capture VMixer"},
	{"Voice Capture VMixer", NULL, "MUX_VX0"},
	{"Voice Capture VMixer", NULL, "MUX_VX1"},

	/* BT */
	{"VX UL VMixer", NULL, "Voice Capture Mixer"},

	/* Vibra */
	{"PDM_VIB", NULL, "VIB_DL"},

	/* VX and MODEM */
	{"VX_UL", NULL, "VX UL VMixer"},
	{"MODEM_UL", NULL, "VX UL VMixer"},
	{"VX DL VMixer", NULL, "VX_DL"},
	{"VX DL VMixer", NULL, "MODEM_DL"},

	/* DAIs */
	{"MM1 Capture", NULL, "MM_UL1"},
	{"MM2 Capture", NULL, "MM_UL2"},
	{"TONES_DL", NULL, "Tones Playback"},
	{"VIB_DL", NULL, "Vibra Playback"},
	{"MM_DL", NULL, "MM VMixer"},
	{"MM VMixer", NULL, "MMLP Playback"},
	{"MM VMixer", NULL, "MM1 Playback"},

	{"VX_DL", NULL, "Voice Playback"},
	{"Voice Capture", NULL, "VX_UL"},
	{"MODEM_DL", NULL, "Modem Playback"},
	{"Modem Capture", NULL, "MODEM_UL"},

	/* Backend Enablement */
	{"BE_OUT", NULL, "PDM_DL1"},
	{"BE_OUT", NULL, "PDM_DL2"},
	{"BE_OUT", NULL, "PDM_VIB"},
	{"BE_OUT", NULL, "MM_EXT_DL"},
	{"BE_OUT", NULL, "BT_VX_DL"},
	{"PDM_UL1", NULL, "BE_IN"},
	{"BT_VX_UL", NULL, "BE_IN"},
	{"MM_EXT_UL", NULL, "BE_IN"},
	{"DMIC0", NULL, "BE_IN"},
	{"DMIC1", NULL, "BE_IN"},
	{"DMIC2", NULL, "BE_IN"},
};

struct soc_dapm_plugin plugin = {
	.graph		= graph,
	.graph_count	= ARRAY_SIZE(graph),

	.widgets	= widgets,
	.widget_count	= ARRAY_SIZE(widgets),

	.kcontrols 	= controls,
	.kcontrol_count	= ARRAY_SIZE(controls),
};
