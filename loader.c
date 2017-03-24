/*
 * Machine driver for EVAL-ADAU1701MINIZ on Analog Devices bfin
 * evaluation boards.
 *
 * Copyright 2011 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 *
 * Licensed under the GPL-2 or later.
 */

#include <linux/module.h>
#include <linux/device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/pcm_params.h>

#include "../linux-e223d71ef728c559aa865d0c5a4cedbdf8789cfd/sound/soc/codecs/adau1701.h"

static const struct snd_soc_dapm_widget adau1701_dapm_widgets[] = {
    SND_SOC_DAPM_SPK("Speaker", NULL),
    SND_SOC_DAPM_LINE("Line Out", NULL),
    SND_SOC_DAPM_LINE("Line In", NULL),
};

static const struct snd_soc_dapm_route adau1701_dapm_routes[] = {
    { "Speaker", NULL, "OUT0" },
    { "Speaker", NULL, "OUT1" },
    { "Line Out", NULL, "OUT2" },
    { "Line Out", NULL, "OUT3" },
    
    { "IN0", NULL, "Line In" },
    { "IN1", NULL, "Line In" },
};

static int adau1701_hw_params(struct snd_pcm_substream *substream,
                              struct snd_pcm_hw_params *params)
{
    struct snd_soc_pcm_runtime *rtd = substream->private_data;
    struct snd_soc_dai *codec_dai = rtd->codec_dai;
    int ret;
    
    ret = snd_soc_dai_set_sysclk(codec_dai, ADAU1701_CLK_SRC_OSC, 12288000,
                                 SND_SOC_CLOCK_IN);
    
    return ret;
}

static struct snd_soc_ops adau1701_ops = {
    .hw_params = adau1701_hw_params,
};

#define ADAU1701_DAI_FMT (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBM_CFM)

static struct snd_soc_dai_link adau1701_dai[] = {
    {
        .name = "adau1701",
        .stream_name = "adau1701",
        .cpu_dai_name = "3f203000.i2s.0",
        .codec_dai_name = "adau1701",
        .platform_name = "bfin-i2s-pcm-audio",
        .codec_name = "adau1701.0-0034",
        .ops = &adau1701_ops,
        .dai_fmt = ADAU1701_DAI_FMT,
    },
    /*
    {
        .name = "adau1701",
        .stream_name = "adau1701",
        .cpu_dai_name = "3f203000.i2s",
        .codec_dai_name = "adau1701",
        .platform_name = "bfin-i2s-pcm-audio",
        .codec_name = "adau1701.0-0034",
        .ops = &adau1701_ops,
        .dai_fmt = ADAU1701_DAI_FMT,
    },
     */
};

static struct snd_soc_card adau1701 = {
    .name = "abacus-adau1701",
    .owner = THIS_MODULE,
    .dai_link = adau1701_dai,
    .num_links = 1,
    
    .dapm_widgets		= adau1701_dapm_widgets,
    .num_dapm_widgets	= ARRAY_SIZE(adau1701_dapm_widgets),
    .dapm_routes		= adau1701_dapm_routes,
    .num_dapm_routes	= ARRAY_SIZE(adau1701_dapm_routes),
};

static int adau1701_probe(struct platform_device *pdev)
{
    struct snd_soc_card *card = &adau1701;
    
    card->dev = &pdev->dev;
    
    return devm_snd_soc_register_card(&pdev->dev, &adau1701);
}

static struct platform_driver adau1701_driver = {
    .driver = {
        .name = "abacus-adau1701",
        .pm = &snd_soc_pm_ops,
    },
    .probe = adau1701_probe,
};

module_platform_driver(adau1701_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("ALSA SoC bfin ADAU1701 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:abacus-adau1701");
