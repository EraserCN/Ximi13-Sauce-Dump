/*--------------------------------------------------------------------------
Copyright (c) 2019 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

Copyright (c) 2009, 2011, 2015, 2017-2018 The Linux Foundation. All rights reserved.
--------------------------------------------------------------------------*/
/*============================================================================
                            O p e n M A X   w r a p p e r s
                             O p e n  M A X   C o r e

*//** @file QOMX_AudioExtensions.h
  This module contains the extensions for Audio

*//*========================================================================*/

#ifndef __H_QOMX_AUDIOEXTENSIONS_H__
#define __H_QOMX_AUDIOEXTENSIONS_H__

/*========================================================================

                     INCLUDE FILES FOR MODULE

========================================================================== */
#include <OMX_Audio.h>

/*========================================================================

                      DEFINITIONS AND DECLARATIONS

========================================================================== */

#if defined( __cplusplus )
extern "C"
{
#endif /* end of macro __cplusplus */

/* Audio extension strings */
#define OMX_QCOM_INDEX_PARAM_AMRWBPLUS       "OMX.Qualcomm.index.audio.amrwbplus"
#define OMX_QCOM_INDEX_PARAM_WMA10PRO        "OMX.Qualcomm.index.audio.wma10pro"
#define OMX_QCOM_INDEX_PARAM_SESSIONID       "OMX.Qualcomm.index.audio.sessionId"
#define OMX_QCOM_INDEX_PARAM_VOICERECORDTYPE "OMX.Qualcomm.index.audio.VoiceRecord"
#define OMX_QCOM_INDEX_PARAM_AC3TYPE         "OMX.Qualcomm.index.audio.ac3"
#define OMX_QCOM_INDEX_PARAM_AC3PP           "OMX.Qualcomm.index.audio.postproc.ac3"
#define OMX_QCOM_INDEX_PARAM_DAK_BUNDLE      "OMX.Qualcomm.index.audio.dakbundle"
#define OMX_QCOM_INDEX_PARAM_DAK_M2S         "OMX.Qualcomm.index.audio.dak_m2s"
#define OMX_QCOM_INDEX_PARAM_DAK_SSE         "OMX.Qualcomm.index.audio.dak_sse"
#define OMX_QCOM_INDEX_PARAM_DAK_SLC         "OMX.Qualcomm.index.audio.dak_slc"
#define OMX_QCOM_INDEX_PARAM_DAK_VOL         "OMX.Qualcomm.index.audio.dak_vol"
#define OMX_QCOM_INDEX_PARAM_DAK_NB          "OMX.Qualcomm.index.audio.dak_nb"
#define OMX_QCOM_INDEX_PARAM_DAK_GEQ         "OMX.Qualcomm.index.audio.dak_geq"
#define OMX_QCOM_INDEX_PARAM_DAK_MSR         "OMX.Qualcomm.index.audio.dak_msr"
#define OMX_QCOM_INDEX_PARAM_DAK_HFE         "OMX.Qualcomm.index.audio.dak_hfe"
#define OMX_QCOM_INDEX_PARAM_DAK_FADE        "OMX.Qualcomm.index.audio.dak_fade"
#define OMX_QCOM_INDEX_PARAM_DAK_SEQ         "OMX.Qualcomm.index.audio.dak_seq"
#define OMX_QCOM_INDEX_CONFIG_DUALMONO       "OMX.Qualcomm.index.audio.dualmono"
#define OMX_QCOM_INDEX_CONFIG_AAC_SEL_MIX_COEF "OMX.Qualcomm.index.audio.aac_sel_mix_coef"
#define OMX_QCOM_INDEX_PARAM_ALAC            "OMX.Qualcomm.index.audio.alac"
#define OMX_QCOM_INDEX_PARAM_APE             "OMX.Qualcomm.index.audio.ape"
#define OMX_QCOM_INDEX_PARAM_DSD             "OMX.Qualcomm.index.audio.dsd"
#define OMX_QCOM_INDEX_PARAM_FLAC_DEC        "OMX.Qualcomm.index.audio.flacdec"

#define ALAC_CSD_SIZE 24
#define APE_CSD_SIZE 32

typedef enum QOMX_AUDIO_AMRBANDMODETYPE {
    QOMX_AUDIO_AMRBandModeWB9              = 0x7F000001,/**< AMRWB Mode 9 = SID*/
    QOMX_AUDIO_AMRBandModeWB10             = 0x7F000002,/**< AMRWB Mode 10 = 13600 bps */
    QOMX_AUDIO_AMRBandModeWB11             = 0x7F000003,/**< AMRWB Mode 11 = 18000 bps */
    QOMX_AUDIO_AMRBandModeWB12             = 0x7F000004,/**< AMRWB Mode 12 = 24000 bps */
    QOMX_AUDIO_AMRBandModeWB13             = 0x7F000005,/**< AMRWB Mode 13 = 24000 bps */
    QOMX_AUDIO_AMRBandModeWB14             = 0x7F000006,/**< AMRWB Mode 14 = FRAME_ERASE*/
    QOMX_AUDIO_AMRBandModeWB15             = 0x7F000007,/**< AMRWB Mode 15 = NO_DATA */
}QOMX_AUDIO_AMRBANDMODETYPE;

typedef enum QOMX_AUDIO_CODINGTYPE {
   QOMX_AUDIO_CodingVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
   QOMX_AUDIO_CodingEVRCB  = 0x7F000001,
   QOMX_AUDIO_CodingEVRCWB = 0x7F000002,
   QOMX_AUDIO_CodingFLAC   = 0x7F000003,
   QOMX_AUDIO_CodingMPEGH  = 0x7F000004,
   QOMX_AUDIO_CodingMax = 0x7FFFFFFF
}QOMX_AUDIO_CODINGTYPE;


/**
 * AMR WB PLUS type
 *
 *  STRUCT MEMBERS:
 *  nSize           : Size of the structure in bytes
 *  nVersion        : OMX specification version information
 *  nPortIndex      : Port that this structure applies to
 *  nChannels       : Number of channels
 *  nBitRate        : Bit rate read only field
 *  nSampleRate     : Sampling frequency for the clip(16/24/32/48KHz)
 *  eAMRBandMode    : AMR Band Mode enumeration
 *  eAMRDTXMode     : AMR DTX Mode enumeration
 *  eAMRFrameFormat : AMR frame format enumeration
 */

typedef struct QOMX_AUDIO_PARAM_AMRWBPLUSTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nChannels;
    OMX_U32 nBitRate;
    OMX_U32 nSampleRate;
    OMX_AUDIO_AMRBANDMODETYPE   eAMRBandMode;
    OMX_AUDIO_AMRDTXMODETYPE     eAMRDTXMode;
    OMX_AUDIO_AMRFRAMEFORMATTYPE eAMRFrameFormat;
} QOMX_AUDIO_PARAM_AMRWBPLUSTYPE;

typedef enum QOMX_AUDIO_WMAFORMATTYPE {
    QOMX_AUDIO_WMAFormat10Pro = 0x7F000001, /**< Windows Media Audio format 10*/
} QOMX_AUDIO_WMAFORMATTYPE;

/**
 * WMA 10 PRO type
 *
 *  STRUCT MEMBERS:
 *  nSize              : Size of the structure in bytes
 *  nVersion           : OMX specification version information
 *  nPortIndex         : Port that this structure applies to
 *  nChannels          : Number of channels
 *  nBitRate           : Bit rate read only field
 *  eFormat            : Version of WMA stream / data
 *  eProfile           : Profile of WMA stream / data
 *  nSamplingRate      : Sampling rate of the source data
 *  nBlockAlign        : block alignment, or block size, in bytes of the audio codec
 *  nEncodeOptions     : WMA Type-specific data
 *  nSuperBlockAlign   : WMA Type-specific data
 *  validBitsPerSample : encoded stream (24-bit or 16-bit)
 *  formatTag          : codec ID(0x162 or 0x166)
 *  advancedEncodeOpt  : bit packed words indicating the features supported for LBR bitstream
 *  advancedEncodeOpt2 : bit packed words indicating the features supported for LBR bitstream
 */
typedef struct QOMX_AUDIO_PARAM_WMA10PROTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U16 nChannels;
    OMX_U32 nBitRate;
    QOMX_AUDIO_WMAFORMATTYPE eFormat;
    OMX_AUDIO_WMAPROFILETYPE eProfile;
    OMX_U32 nSamplingRate;
    OMX_U16 nBlockAlign;
    OMX_U16 nEncodeOptions;
    OMX_U32 nSuperBlockAlign;
    OMX_U32 validBitsPerSample;
    OMX_U32 formatTag;
    OMX_U32 advancedEncodeOpt;
    OMX_U32 advancedEncodeOpt2;
    OMX_U16 nVirtualPktSize;
} QOMX_AUDIO_PARAM_WMA10PROTYPE;


typedef enum OMX_AUDIO_AC3FORMATTYPE {
   omx_audio_ac3       = 0x7f000001, /**< ac-3 */
   omx_audio_eac3      = 0x7f000002  /**< eac-3 */
} OMX_AUDIO_AC3FORMATTYPE;

typedef enum OMX_AUDIO_AC3_CHANNEL_CONFIG
{
   OMX_AUDIO_AC3_CHANNEL_CONFIG_RSVD = 0,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_1_0,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_2_0,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_3_0,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_2_1,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_3_1,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_2_2,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_3_2,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_3_0_1,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_2_2_1,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_3_2_1,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_3_0_2,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_2_2_2,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_3_2_2,
   OMX_AUDIO_AC3_CHANNEL_CONFIG_DEFAULT = 0xFFFF
} OMX_AUDIO_AC3_CHANNEL_CONFIG;

/**
 * AC-3 type
 *
 *  STRUCT MEMBERS:
 *  nSize               : Size of the structure in bytes
 *  nVersion            : OMX specification version information
 *  nPortIndex          : Port that this structure applies to
 *  nChannels           : Number of channels
 *  nBitRate            : Bitrate
 *  nSamplingRate       : Sampling rate, 32K, 44.1K, 48K only supported
 *  eFormat             : AC-3 or EAC-3
 *  eChannelConfig      : Channel configuration
 *  nProgramID          : Indication of ProgramID, 0-7
 *  bCompressionOn      : Flag to enable Compression
 *  bLfeOn              : Flag for LFE on/off
 *  bDelaySurroundChannels : Flag to put delay on surround channels
 *
 */
typedef struct QOMX_AUDIO_PARAM_AC3TYPE {
   OMX_U32 nSize;
   OMX_VERSIONTYPE nVersion;
   OMX_U32 nPortIndex;
   OMX_U16 nChannels;
   OMX_U32 nBitRate;
   OMX_U32 nSamplingRate;
   OMX_AUDIO_AC3FORMATTYPE eFormat;
   OMX_AUDIO_AC3_CHANNEL_CONFIG eChannelConfig;
   OMX_U8 nProgramID;
   OMX_BOOL bCompressionOn;
   OMX_BOOL bLfeOn;
   OMX_BOOL bDelaySurroundChannels;
} QOMX_AUDIO_PARAM_AC3TYPE;

typedef struct OMX_AUDIO_PARAM_ANDROID_PROFILETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 eProfile;      /**< type is OMX_AUDIO_AACPROFILETYPE or OMX_AUDIO_WMAPROFILETYPE
                             depending on context */
    OMX_U32 nProfileIndex; /**< Used to query for individual profile support information */
} OMX_AUDIO_PARAM_ANDROID_PROFILETYPE;

typedef enum OMX_AUDIO_AC3_CHANNEL_ROUTING
{
   OMX_AUDIO_AC3_CHANNEL_LEFT,
   OMX_AUDIO_AC3_CHANNEL_CENTER,
   OMX_AUDIO_AC3_CHANNEL_RIGHT,
   OMX_AUDIO_AC3_CHANNEL_LEFT_SURROUND,
   OMX_AUDIO_AC3_CHANNEL_RIGHT_SURROUND,
   OMX_AUDIO_AC3_CHANNEL_SURROUND,
   OMX_AUDIO_AC3_CHANNEL_EXTENSION_1,
   OMX_AUDIO_AC3_CHANNEL_EXTENSION_2,
   OMX_AUDIO_AC3_CHANNEL_DEFAULT = 0xFFFF
} OMX_AUDIO_AC3_CHANNEL_ROUTING;

typedef enum OMX_AUDIO_AC3_COMPRESSION_MODE
{
   OMX_AUDIO_AC3_COMPRESSION_MODE_ANALOG_DIALNORM,
   OMX_AUDIO_AC3_COMPRESSION_MODE_DIGITAL_DIALNORM,
   OMX_AUDIO_AC3_COMPRESSION_MODE_LINE_OUT,
   OMX_AUDIO_AC3_COMPRESSION_MODE_RF_REMOD
} OMX_AUDIO_AC3_COMPRESSION_MODE;

typedef enum OMX_AUDIO_AC3_STEREO_MODE
{
   OMX_AUDIO_AC3_STEREO_MODE_AUTO_DETECT,
   OMX_AUDIO_AC3_STEREO_MODE_LT_RT,
   OMX_AUDIO_AC3_STEREO_MODE_LO_RO,
   OMX_AUDIO_AC3_STEREO_MODE_DEFAULT = 0xFFFF
} OMX_AUDIO_AC3_STEREO_MODE;

typedef enum OMX_AUDIO_AC3_DUAL_MONO_MODE
{
   OMX_AUDIO_AC3_DUAL_MONO_MODE_STEREO,
   OMX_AUDIO_AC3_DUAL_MONO_MODE_LEFT_MONO,
   OMX_AUDIO_AC3_DUAL_MONO_MODE_RIGHT_MONO,
   OMX_AUDIO_AC3_DUAL_MONO_MODE_MIXED_MONO,
   OMX_AUDIO_AC3_DUAL_MONO_MODE_DEFAULT = 0xFFFF
} OMX_AUDIO_AC3_DUAL_MONO_MODE;

typedef enum OMX_AUDIO_AC3_KARAOKE_MODE
{
   OMX_AUDIO_AC3_KARAOKE_MODE_NO_VOCAL,
   OMX_AUDIO_AC3_KARAOKE_MODE_LEFT_VOCAL,
   OMX_AUDIO_AC3_KARAOKE_MODE_RIGHT_VOCAL,
   OMX_AUDIO_AC3_KARAOKE_MODE_BOTH_VOCAL,
   OMX_AUDIO_AC3_KARAOKE_MODE_DEFAULT = 0xFFFF
} OMX_AUDIO_AC3_KARAOKE_MODE;


typedef struct QOMX_AUDIO_PARAM_AC3PP
{
   OMX_U32 nSize;
   OMX_VERSIONTYPE nVersion;
   OMX_U32 nPortIndex;
   OMX_AUDIO_AC3_CHANNEL_ROUTING eChannelRouting[8];
   OMX_AUDIO_AC3_COMPRESSION_MODE eCompressionMode;
   OMX_AUDIO_AC3_STEREO_MODE eStereoMode;
   OMX_AUDIO_AC3_DUAL_MONO_MODE eDualMonoMode;
   OMX_U32 usPcmScale;
   OMX_U32 usDynamicScaleBoost;
   OMX_U32 usDynamicScaleCut;
   OMX_AUDIO_AC3_KARAOKE_MODE eKaraokeMode;
} QOMX_AUDIO_PARAM_AC3PP;


/**
 * Stream info data
 *
 *  STRUCT MEMBERS:
 *  sessionId :  session Id for alsa to route data
 */
typedef struct QOMX_AUDIO_STREAM_INFO_DATA {
    OMX_U8  sessionId;
} QOMX_AUDIO_STREAM_INFO_DATA;


/**
 * Record Path
 *
 * STRUCT MEMBERS:
 * recPath : Record Path for encoding
 */
typedef enum{

QOMX_AUDIO_VOICE_TX,
QOMX_AUDIO_VOICE_RX,
QOMX_AUDIO_VOICE_MIXED,

} QOMX_AUDIO_VOICERECORDMODETYPE;
typedef struct QOMX_AUDIO_CONFIG_VOICERECORDTYPE {

OMX_U32                            nSize;
OMX_VERSIONTYPE                    nVersion;
QOMX_AUDIO_VOICERECORDMODETYPE     eVoiceRecordMode;
}  QOMX_AUDIO_CONFIG_VOICERECORDTYPE;

/* Enum for mapping dual-mono contents to left and right channels */
typedef enum OMX_AUDIO_DUAL_MONO_CHANNEL_CONFIG {
 OMX_AUDIO_DUAL_MONO_MODE_FL_FR,/* 1st SCE to left & right */
 OMX_AUDIO_DUAL_MONO_MODE_SL_SR,/* 2nd SCE to left & right */
 OMX_AUDIO_DUAL_MONO_MODE_SL_FR,/* 2nd SCE to left, 1st SCE to right */
 OMX_AUDIO_DUAL_MONO_MODE_FL_SR,/* 1st SCE to left, 2nd SCE to right default */
 OMX_AUDIO_DUAL_MONO_MODE_DEFAULT = OMX_AUDIO_DUAL_MONO_MODE_FL_SR,
 OMX_AUDIO_DUAL_MONO_MODE_INVALID = -1
} OMX_AUDIO_DUAL_MONO_CHANNEL_CONFIG;

/************************************/
/* DAK */
/*************************************/

/** this is the list of custom vendor index */
typedef enum OMX_INDEX_DAK_TYPE {
    OMX_IndexConfigDAK_BUNDLE = OMX_IndexVendorStartUnused /*0x7F000000*/,    /**< reference: OMX_DAK_CONFIG_BUNDLETYPE */
    OMX_IndexConfigDAK_M2S,    /**< reference: OMX_DAK_CONFIG_M2STYPE */
    OMX_IndexConfigDAK_SSE,    /**< reference: OMX_DAK_CONFIG_SSETYPE */
    OMX_IndexConfigDAK_SLC,    /**< reference: OMX_DAK_CONFIG_SLCTYPE */
    OMX_IndexConfigDAK_VOL,    /**< reference: OMX_DAK_CONFIG_VOLTYPE */
    OMX_IndexConfigDAK_NB,     /**< reference: OMX_DAK_CONFIG_NBTYPE */
    OMX_IndexConfigDAK_GEQ,    /**< reference: OMX_DAK_CONFIG_GEQTYPE */
    OMX_IndexConfigDAK_MSR,    /**< reference: OMX_DAK_CONFIG_MSRTYPE */
    OMX_IndexConfigDAK_HFE,    /**< reference: OMX_DAK_CONFIG_HFETYPE */
    OMX_IndexConfigDAK_FADE,   /**< reference: OMX_DAK_CONFIG_FADETYPE */
    OMX_IndexConfigDAK_SEQ,    /**< reference: OMX_DAK_CONFIG_SEQTYPE */

} OMX_INDEX_DAK_TYPE;


/** Dolby Audio Kernel TDAS bundle */
typedef struct OMX_DAK_CONFIG_BUNDLETYPE {
    OMX_U32 nSize;                 /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;      /**< OMX specification version information */
    OMX_U32 nDAK_Version;          /**< Dolby Audio Kernel version information */
    OMX_U32 nDAK_Revision;         /**< Dolby Audio Kernel revision information */
    OMX_U8 nLfeMixLevel;           /**< level at which the LFE channel is mixed into the output audio */
    OMX_U8 nSampleRateIndex;       /**< Output sample rate */
    OMX_U8 nInChans;               /**< Channel format of input audio */
    OMX_U8 nInMatrix;              /**< L/R mixing specification for stereo audio input */
    OMX_U8 nBypass;                /**< Audio Processing bypass */
    OMX_U8 nRateMultipier;         /**< Sample-rate multiplier (output with respect to input) */
    OMX_U8 nInChanFormat;          /**< Input/Output channel format */
    OMX_U8 nMsrMaxProfile;         /**< Maximum number of virtual rendering channels in Mobile Surround */
    OMX_BOOL bPortablemodeEnable;  /**< Enable or disable Pulse Portable Mode */
    OMX_S16 nPotablemodeGain;      /**< Send the Portable Mode gain value from the Pulse decoder */
    OMX_U8 nORL;                   /**< Device specific target signal level (output reference level) */
    OMX_BOOL bPulsedownmixEnable;  /**< Enable the Pulse Downmix compensation */
    OMX_S8 nPulsedownmixAtten;     /**< Attenuation value that Pulse is currently applying */
    OMX_U8 nOutChans;              /**< Channel format of output audio */

} OMX_DAK_CONFIG_BUNDLETYPE;

/** Dolby Audio Kernel Mono-to-Stereo Creator */
typedef struct OMX_DAK_CONFIG_M2STYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Mono-to-Stereo Creator enable */
    OMX_BOOL bDetector;        /**< Stereo detector status */
} OMX_DAK_CONFIG_M2STYPE;

/** Dolby Audio Kernel Sound Space Expander */
typedef struct OMX_DAK_CONFIG_SSETYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Sound Space Expander enable */
    OMX_U8 nWidth;             /**< Width of expansion effect */
    OMX_U8 nSpkMode;           /**< Speaker Mode */
} OMX_DAK_CONFIG_SSETYPE;

/** Dolby Audio Kernel Sound Level Controller */
typedef struct OMX_DAK_CONFIG_SLCTYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Sound Level Controller enable */
    OMX_U8 nLevel;             /**< Source audio RMS level */
    OMX_U8 nDepth;             /**< Depth of effect */
} OMX_DAK_CONFIG_SLCTYPE;

/** Dolby Audio Kernel Volume */
typedef struct OMX_DAK_CONFIG_VOLTYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Volume enable */
    OMX_U8 nGainType;          /**< Linear/Logarithmic audio scaling */
    OMX_U8 nInternalGain;      /**< Audio volume scale */
    OMX_U8 nExternalGain;      /**< Audio volume scale applied by external volume control */
    OMX_S8 nBalance;           /**< L/R panning for output audio */
    OMX_BOOL bMute;            /**< Audio Mute */
} OMX_DAK_CONFIG_VOLTYPE;

/** Dolby Audio Kernel Natural Bass */
typedef struct OMX_DAK_CONFIG_NBTYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Natural Bass enable */
    OMX_U8 nCutoff;            /**< Speakers/headphones lower cutoff frequency */
    OMX_U8 nBoost;             /**< Strength of effect */
    OMX_U8 nLevel;             /**< Maximum output level capability of speakers/headphones */
} OMX_DAK_CONFIG_NBTYPE;

/** Dolby Audio Kernel Graphic EQ */
typedef struct OMX_DAK_CONFIG_GEQTYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Graphic EQ enable */
    OMX_U8 nNbands;            /**< Number of frequency bands */
    OMX_S8 nPreamp;            /**< Global attenuation to apply prior to band level adjustment */
    OMX_U8 nMaxboost;          /**< Maximum absolute boost with respect to the source audio */
    OMX_S8 nBand1;             /**< Boost/cut for 1st frequency band */
    OMX_S8 nBand2;             /**< Boost/cut for 2nd frequency band */
    OMX_S8 nBand3;             /**< Boost/cut for 3rd frequency band */
    OMX_S8 nBand4;             /**< Boost/cut for 4th frequency band */
    OMX_S8 nBand5;             /**< Boost/cut for 5th frequency band */
    OMX_S8 nBand6;             /**< Boost/cut for 6th frequency band */
    OMX_S8 nBand7;             /**< Boost/cut for 7th frequency band */
} OMX_DAK_CONFIG_GEQTYPE;

/** Dolby Audio Kernel, Mobile Surround and Surround Upmixer */
typedef struct OMX_DAK_CONFIG_MSRTYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bMsrEnable;       /**< Mobile Surround enable */
    OMX_U8 nMsrRoom;           /**< Room Size control */
    OMX_U8 nMsrBright;         /**< Brightness control */
    OMX_BOOL bMupEnable;       /**< Mobile Surround Upmixer enable */
} OMX_DAK_CONFIG_MSRTYPE;

/** Dolby Audio Kernel High Frequency Enhancer */
typedef struct OMX_DAK_CONFIG_HFETYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< High Frequency Enhancer enable */
    OMX_U8 nDepth;             /**< Strength of effect */
} OMX_DAK_CONFIG_HFETYPE;

/** Dolby Audio Kernel Fade */
typedef struct OMX_DAK_CONFIG_FADETYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Fade enable */
    OMX_U8 nTarget;            /**< Target fade level */
    OMX_U16 nTime;             /**< Fade time interval */
} OMX_DAK_CONFIG_FADETYPE;

/** Dolby Audio Kernel Speaker EQ */
typedef struct OMX_DAK_CONFIG_SEQTYPE {
    OMX_U32 nSize;             /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;  /**< OMX specification version information */
    OMX_BOOL bEnable;          /**< Speaker EQ enable */
    OMX_S8 nLeftGainDB;        /**< Additional gain for Left channel */
    OMX_S8 nRightGainDB;       /**< Additional gain for Right channel */
    OMX_U8 nCoef48000Size;     /**< Length of the block of coefficients for 48KHz Sampling Rate case */
    OMX_PTR pCoef48000;        /**< Pointer to the block of coefficients for the 48KHz case */
    OMX_U8 nCoef44100Size;     /**< Length of the block of coefficients for 44.1KHz Sampling Rate case */
    OMX_PTR pCoef44100;        /**< Pointer to the block of coefficients for the 44.1KHz case */
    OMX_U8 nCoef32000Size;     /**< Length of the block of coefficients for 32KHz Sampling Rate case */
    OMX_PTR pCoef32000;        /**< Pointer to the block of coefficients for the 32KHz case */
    OMX_U8 nCoef24000Size;     /**< Length of the block of coefficients for 24KHz Sampling Rate case */
    OMX_PTR pCoef24000;        /**< Pointer to the block of coefficients for the 24KHz case */

} OMX_DAK_CONFIG_SEQTYPE;


typedef enum OMX_AUDIO_CHANNELTYPE_EXTENSION {
    OMX_AUDIO_ChannelTS = OMX_AUDIO_ChannelVendorStartUnused,  /**< Top Surround */
    OMX_AUDIO_ChannelCVH       /**< Central Vertical Height */
} OMX_AUDIO_CHANNELTYPE_EXTENSION;

/**
 * DUAL-MONO type
 *
 *  STRUCT MEMBERS:
 *  nSize               : Size of the structure in bytes
 *  nVersion            : OMX specification version information
 *  nPortIndex          : Port that this structure applies to
 *  eChannelConfig      : Enum for channel config
 *
 */
typedef struct QOMX_AUDIO_CONFIG_DUALMONOTYPE {
   OMX_U32 nSize;
   OMX_VERSIONTYPE nVersion;
   OMX_U32 nPortIndex;
   OMX_AUDIO_DUAL_MONO_CHANNEL_CONFIG eChannelConfig;
} QOMX_AUDIO_CONFIG_DUALMONOTYPE;

typedef struct QOMX_AUDIO_PARAM_ALACTYPE {
    OMX_U32 nSize; /* Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex; /* Port that this structure applies to */
    OMX_BOOL bBytesStreamMode; /*enable byte stream mode*/
    OMX_U32 nFrameLength; /* Frames per packet when no explicit frames per packet setting is present in the packet header */
    OMX_U8 nCompatibleVersion; /* Indicates the compatible version */
    OMX_U8 nBitDepth; /* Bit depth of the source PCM data */
    OMX_U8 nPb; /* Tuning Parameter; currently not used */
    OMX_U8 nMb; /* Tuning Parameter; currently not used */
    OMX_U8 nKb; /* Tuning Parameter; currently not used */
    OMX_U8 nChannels; /* Number of channels for multichannel decoding */
    OMX_U16 nMaxRun; /* Currently not used */
    OMX_U32 nMaxFrameBytes; /* Max size of an Apple Lossless packet within the encoded stream */
    OMX_U32 nAvgBitRate; /* Average bit rate in bits per second of the Apple Lossless stream */
    OMX_U32 nSampleRate; /* Number of samples per second in Hertz */
    OMX_U32 nChannelLayoutTag; /*Indicates whether channel layout information is present in the bitstream */
} QOMX_AUDIO_PARAM_ALACTYPE;

typedef struct QOMX_AUDIO_PARAM_APETYPE {
    OMX_U32 nSize; /* Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex; /* Port that this structure applies to */
    OMX_BOOL bBytesStreamMode; /*enable byte stream mode*/
    OMX_U16 nCompatibleVersion; /* Indicates the compatible version */
    OMX_U16 nCompressionLevel; /* The compression level present in the encoded packet */
    OMX_U32 nFormatFlags; /* Reserved parameter for future use */
    OMX_U32 nBlocksPerFrame; /* Indicates the number of audio blocks in one frame present in the encoded packet header */
    OMX_U32 nFinalFrameBlocks; /* Indicates the number of audio blocks in the final frame present in the encoded packet header */
    OMX_U32 nTotalFrames; /* Indicates the total number of frames */
    OMX_U16 nBitsPerSample; /* Bit depth of the source PCM data */
    OMX_U16 nChannels; /* Number of channels for decoding */
    OMX_U32 nSampleRate; /* Samples per second in Hertz */
    OMX_U32 nSeekTablePresent; /* Flag to indicate if seek table is present or not */
} QOMX_AUDIO_PARAM_APETYPE;

typedef struct QOMX_AUDIO_PARAM_FLAC_DEC_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nChannels;
    OMX_U32 nSampleRate;
    OMX_U32 nBitsPerSample;
    OMX_U32 nMinBlkSize;
    OMX_U32 nMaxBlkSize;
    OMX_U32 nMinFrmSize;
    OMX_U32 nMaxFrmSize;
} QOMX_AUDIO_PARAM_FLAC_DEC_TYPE;

typedef struct QOMX_AUDIO_PARAM_DSD_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bBytesStreamMode; /*enable byte stream mode*/
    OMX_U32 nSampleRate;
    OMX_U32 nOutSamplePerCh;
    OMX_U32 nChannels;
    OMX_U32 nBitsPerSample;
} QOMX_AUDIO_PARAM_DSD_TYPE;

typedef struct QOMX_AUDIO_PARAM_MPEGH_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nSampleRate;      /** Sent In-Band as well and can be redundant For Decoder, **/
    OMX_U32 nBitRate;         /** Sent In-Band as well and can be redundant For Decoder, **/
    OMX_U32 nSamplesPerFrame; /** Sent In-Band as well and can be redundant For Decoder, **/
    OMX_U32 nDFrames;         /** No of Dependent Frames; if 10;every 11 frame is seekable
                                   - Specific to Encoder; Redundant for Decoder **/
    OMX_U32 nHOAOrder;        /** HOA Order - Specific to Encoder; May be redundant for
                                  Decoder **/
} QOMX_AUDIO_PARAM_MPEGH_TYPE;

typedef struct QOMX_AUDIO_PARAM_MPEGH_HEADER_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U64 pConfig;
    OMX_U64 pSceneInfo;
    OMX_U64 pDRC;
    OMX_U64 pGroup;
    OMX_U64 pSwitchGroup;
    OMX_U64 pPreset;
    OMX_U64 pTextLabel;
} QOMX_AUDIO_PARAM_MPEGH_HEADER_TYPE;

typedef struct QOMX_AUDIO_PARAM_CHANNEL_CONFIG_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nChannelMask; /* Masked defined in Android audio-base.h */
} QOMX_AUDIO_PARAM_CHANNEL_CONFIG_TYPE;

typedef enum QOMX_BINAURAL_MODE {
   QOMX_BINAURAL_MODE_OFF,
   QOMX_BINAURAL_MODE_ON
} QOMX_BINAURAL_MODE;

typedef struct QOMX_AUDIO_PARAM_BINAURAL_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    QOMX_BINAURAL_MODE eBinauralMode;
} QOMX_AUDIO_PARAM_BINAURAL_TYPE;

typedef struct QOMX_AUDIO_PARAM_ROTATION_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_S32 nQX; /* x vector component of quaternion */
    OMX_S32 nQY; /* y vector component of quaternion */
    OMX_S32 nQZ; /* z vector component of quaternion */
    OMX_S32 nQW; /* Scalar component of quaternion */
} QOMX_AUDIO_PARAM_ROTATION_TYPE;

enum {
    kKeyIndexAlacFrameLength = 0,
    kKeyIndexAlacCompatibleVersion = 4,
    kKeyIndexAlacBitDepth = 5,
    kKeyIndexAlacPb = 6,
    kKeyIndexAlacMb = 7,
    kKeyIndexAlacKb = 8,
    kKeyIndexAlacNumChannels = 9,
    kKeyIndexAlacMaxRun = 10,
    kKeyIndexAlacMaxFrameBytes = 12,
    kKeyIndexAlacAvgBitRate = 16,
    kKeyIndexAlacSamplingRate = 20,
    kKeyIndexAlacChannelLayoutTag = 24,
    kKeyIndexAlacMax = kKeyIndexAlacChannelLayoutTag,
};

enum {
    kKeyIndexApeCompatibleVersion = 0,
    kKeyIndexApeCompressionLevel = 2,
    kKeyIndexApeFormatFlags = 4,
    kKeyIndexApeBlocksPerFrame = 8,
    kKeyIndexApeFinalFrameBlocks = 12,
    kKeyIndexApeTotalFrames = 16,
    kKeyIndexApeBitsPerSample = 20,
    kKeyIndexApeNumChannels = 22,
    kKeyIndexApeSampleRate = 24,
    kKeyIndexApeSeekTablePresent = 28,
    kKeyIndexApeMax = kKeyIndexApeSeekTablePresent,
};

enum {
    APE_COMPRESSION_LEVEL_FAST = 1000,
    APE_COMPRESSION_LEVEL_NORMAL = 2000,
    APE_COMPRESSION_LEVEL_HIGH = 3000,
    APE_COMPRESSION_LEVEL_EXTRA_HIGH = 4000,
    APE_COMPRESSION_LEVEL_INSANE = 5000,
};

#if defined( __cplusplus )
}
#endif /* end of macro __cplusplus */

#endif /* end of macro __H_QOMX_AUDIOEXTENSIONS_H__ */
