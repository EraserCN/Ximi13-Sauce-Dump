/*******************************************************************************
Copyright(c) ArcSoft, All right reserved.

This file is ArcSoft's property. It contains ArcSoft's trade secret, proprietary
and confidential information.

The information and code contained in this file is only for authorized ArcSoft
employees to design, create, modify, or review.

DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER
AUTHORIZATION.

If you are not an intended recipient of this file, you must not copy,
distribute, modify, or take any action in reliance on it.

If you have received this file in error, please immediately notify ArcSoft and
permanently delete the original and any copy of any file and any printout
thereof.
*******************************************************************************/
#ifndef __ASVL_OFFSCREEN_H__
#define __ASVL_OFFSCREEN_H__

#include "amcomdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/*31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00 */

/* R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B */
#define ASVL_PAF_RGB16_B5G6R5 0x101
/* X  R  R  R  R  R  G  G  G  G  G  B  B  B  B  B */
#define ASVL_PAF_RGB16_B5G5R5 0x102
/* X  X  X  X  R  R  R  R  G  G  G  G  B  B  B  B */
#define ASVL_PAF_RGB16_B4G4R4 0x103
/* T  R  R  R  R  R  G  G  G  G  G  B  B  B  B  B */
#define ASVL_PAF_RGB16_B5G5R5T 0x104
/* B  B  B  B  B  G  G  G  G  G  G  R  R  R  R  R */
#define ASVL_PAF_RGB16_R5G6B5 0x105
/* X  B  B  B  B  B  G  G  G  G  G  R  R  R  R  R */
#define ASVL_PAF_RGB16_R5G5B5 0x106
/* X  X  X  X  B  B  B  B  G  G  G  G  R  R  R  R */
#define ASVL_PAF_RGB16_R4G4B4 0x107

/* R	R  R  R	 R	R  R  R  G  G  G  G  G  G  G  G  B  B  B  B  B  B  B  B */
#define ASVL_PAF_RGB24_B8G8R8 0x201
/* X	X  X  X	 X	X  R  R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B  B */
#define ASVL_PAF_RGB24_B6G6R6 0x202
/* X	X  X  X	 X	T  R  R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B  B */
#define ASVL_PAF_RGB24_B6G6R6T 0x203
/* B  B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R	R  R  R	 R	R  R  R */
#define ASVL_PAF_RGB24_R8G8B8 0x204
/* X	X  X  X	 X	X  B  B  B  B  B  B  G  G  G  G  G  G  R  R  R  R  R  R */
#define ASVL_PAF_RGB24_R6G6B6 0x205

/* X	X  X  X	 X	X  X  X	 R	R  R  R	 R	R  R  R  G  G  G  G  G  G G  G  B  B  B  B
 * B  B  B  B */
#define ASVL_PAF_RGB32_B8G8R8 0x301
/* A	A  A  A	 A	A  A  A	 R	R  R  R	 R	R  R  R  G  G  G  G  G  G G  G  B  B  B  B
 * B  B  B  B */
#define ASVL_PAF_RGB32_B8G8R8A8 0x302
/* X	X  X  X	 X	X  X  X	 B  B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R R  R  R	 R
 * R  R  R */
#define ASVL_PAF_RGB32_R8G8B8 0x303
/* B    B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R  R  R  R  R  R  R  R  A	A  A  A  A
 * A  A  A */
#define ASVL_PAF_RGB32_A8R8G8B8 0x304
/* A    A  A  A  A  A  A  A  B  B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R  R  R  R  R	R  R
 * R */
#define ASVL_PAF_RGB32_R8G8B8A8 0x305

/*Y0, U0, V0*/
#define ASVL_PAF_YUV 0x401
/*Y0, V0, U0*/
#define ASVL_PAF_YVU 0x402
/*U0, V0, Y0*/
#define ASVL_PAF_UVY 0x403
/*V0, U0, Y0*/
#define ASVL_PAF_VUY 0x404

/*Y0, U0, Y1, V0*/
#define ASVL_PAF_YUYV 0x501
/*Y0, V0, Y1, U0*/
#define ASVL_PAF_YVYU 0x502
/*U0, Y0, V0, Y1*/
#define ASVL_PAF_UYVY 0x503
/*V0, Y0, U0, Y1*/
#define ASVL_PAF_VYUY 0x504
/*Y1, U0, Y0, V0*/
#define ASVL_PAF_YUYV2 0x505
/*Y1, V0, Y0, U0*/
#define ASVL_PAF_YVYU2 0x506
/*U0, Y1, V0, Y0*/
#define ASVL_PAF_UYVY2 0x507
/*V0, Y1, U0, Y0*/
#define ASVL_PAF_VYUY2 0x508
/*Y0, Y1, U0, V0*/
#define ASVL_PAF_YYUV 0x509

/*8 bit Y plane followed by 8 bit 2x2 subsampled U and V planes*/
#define ASVL_PAF_I420 0x601
/*8 bit Y plane followed by 8 bit 1x2 subsampled U and V planes*/
#define ASVL_PAF_I422V 0x602
/*8 bit Y plane followed by 8 bit 2x1 subsampled U and V planes*/
#define ASVL_PAF_I422H 0x603
/*8 bit Y plane followed by 8 bit U and V planes*/
#define ASVL_PAF_I444 0x604
/*8 bit Y plane followed by 8 bit 2x2 subsampled V and U planes*/
#define ASVL_PAF_YV12 0x605
/*8 bit Y plane followed by 8 bit 1x2 subsampled V and U planes*/
#define ASVL_PAF_YV16V 0x606
/*8 bit Y plane followed by 8 bit 2x1 subsampled V and U planes*/
#define ASVL_PAF_YV16H 0x607
/*8 bit Y plane followed by 8 bit V and U planes*/
#define ASVL_PAF_YV24 0x608
/*8 bit Y plane only*/
#define ASVL_PAF_GRAY 0x701

/*8 bit Y plane followed by 8 bit 2x2 subsampled UV planes*/
#define ASVL_PAF_NV12 0x801
/*8 bit Y plane followed by 8 bit 2x2 subsampled VU planes*/
#define ASVL_PAF_NV21 0x802
/*8 bit Y plane followed by 8 bit 2x1 subsampled UV planes*/
#define ASVL_PAF_LPI422H 0x803
/*8 bit Y plane followed by 8 bit 2x1 subsampled VU planes*/
#define ASVL_PAF_LPI422H2 0x804

/*8 bit Y plane followed by 8 bit 4x4 subsampled VU planes*/
#define ASVL_PAF_NV41 0x805

/*Negative UYVY, U0, Y0, V0, Y1*/
#define ASVL_PAF_NEG_UYVY 0x901
/*Negative I420, 8 bit Y plane followed by 8 bit 2x2 subsampled U and V planes*/
#define ASVL_PAF_NEG_I420 0x902

/*Mono UYVY, UV values are fixed, gray image in U0, Y0, V0, Y1*/
#define ASVL_PAF_MONO_UYVY 0xa01
/*Mono I420, UV values are fixed, 8 bit Y plane followed by 8 bit 2x2 subsampled U and V planes*/
#define ASVL_PAF_MONO_I420 0xa02

/*P8_YUYV, 8 pixels a group, Y0Y1Y2Y3Y4Y5Y6Y7U0U1U2U3V0V1V2V3*/
#define ASVL_PAF_P8_YUYV 0xb03

/*P16_YUYV, 16*16 pixels a group, Y0Y1Y2Y3...U0U1...V0V1...*/
#define ASVL_PAF_SP16UNIT 0xc01

#define ASVL_PAF_DEPTH_U16 0xc02

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  0  0  D  D  D  D  D  D  D  D ,
*/
#define ASVL_PAF_DEPTH8_U16_MSB 0xc10

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  0  0  0  0  0  0  0  0 ,
*/
#define ASVL_PAF_DEPTH8_U16_LSB 0xc11

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D ,
*/
#define ASVL_PAF_DEPTH10_U16_MSB 0xc12

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0 ,
*/
#define ASVL_PAF_DEPTH10_U16_LSB 0xc13

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D ,
*/
#define ASVL_PAF_DEPTH12_U16_MSB 0xc14

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0 ,
*/
#define ASVL_PAF_DEPTH12_U16_LSB 0xc15

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D ,
*/
#define ASVL_PAF_DEPTH14_U16_MSB 0xc16

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0 ,
*/
#define ASVL_PAF_DEPTH14_U16_LSB 0xc17

/*
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D ,
*/
#define ASVL_PAF_DEPTH16_U16 0xc18

/*10 bits Bayer raw data, each pixel use 10 bits memory size*/
#define ASVL_PAF_RAW10_RGGB_10B 0xd01
#define ASVL_PAF_RAW10_GRBG_10B 0xd02
#define ASVL_PAF_RAW10_GBRG_10B 0xd03
#define ASVL_PAF_RAW10_BGGR_10B 0xd04

/*12 bits Bayer raw data, each pixel use 12 bits memory size*/
#define ASVL_PAF_RAW12_RGGB_12B 0xd05
#define ASVL_PAF_RAW12_GRBG_12B 0xd06
#define ASVL_PAF_RAW12_GBRG_12B 0xd07
#define ASVL_PAF_RAW12_BGGR_12B 0xd08

/*10 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW10_RGGB_16B 0xd09
#define ASVL_PAF_RAW10_GRBG_16B 0xd0A
#define ASVL_PAF_RAW10_GBRG_16B 0xd0B
#define ASVL_PAF_RAW10_BGGR_16B 0xd0C

/*12 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW12_RGGB_16B 0xd11
#define ASVL_PAF_RAW12_GRBG_16B 0xd12
#define ASVL_PAF_RAW12_GBRG_16B 0xd13
#define ASVL_PAF_RAW12_BGGR_16B 0xd14

/*16 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW16_RGGB_16B 0xd21
#define ASVL_PAF_RAW16_GRBG_16B 0xd22
#define ASVL_PAF_RAW16_GBRG_16B 0xd23
#define ASVL_PAF_RAW16_BGGR_16B 0xd24

/*14 bits Bayer raw data, each pixel use 14 bits memory size*/
#define ASVL_PAF_RAW14_RGGB_14B 0xd35
#define ASVL_PAF_RAW14_GRBG_14B 0xd36
#define ASVL_PAF_RAW14_GBRG_14B 0xd37
#define ASVL_PAF_RAW14_BGGR_14B 0xd38

/*14 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW14_RGGB_16B 0xd41
#define ASVL_PAF_RAW14_GRBG_16B 0xd42
#define ASVL_PAF_RAW14_GBRG_16B 0xd43
#define ASVL_PAF_RAW14_BGGR_16B 0xd44

/*10 bits gray raw data, each pixel use 10 bits memory size*/
#define ASVL_PAF_RAW10_GRAY_10B 0xe01

/*12 bits gray raw data, each pixel use 12 bits memory size*/
#define ASVL_PAF_RAW12_GRAY_12B 0xe11

/*14 bits gray raw data, each pixel use 14 bits memory size*/
#define ASVL_PAF_RAW14_GRAY_14B 0xe21

/*16 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW16_GRAY_16B 0xe31

/*10 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW10_GRAY_16B 0xe81

/*12 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW12_GRAY_16B 0xe91

/*14 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define ASVL_PAF_RAW14_GRAY_16B 0xea1

/*10 bit Y plane followed by 10 bit 2x2 subsampled UV planes*/
/*
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y ,
  ....
  0  0  0  0  0  0  U  U  U  U  U  U  U  U  U  U ,
  0  0  0  0  0  0  V  V  V  V  V  V  V  V  V  V ,
  ....
*/
#define ASVL_PAF_P010_MSB 0xf01

/*10 bit Y plane followed by 10 bit 2x2 subsampled UV planes*/
/*
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  0  0  0  0  0  0 ,
  ....
  U  U  U  U  U  U  U  U  U  U  0  0  0  0  0  0 ,
  V  V  V  V  V  V  V  V  V  V  0  0  0  0  0  0 ,
  ....
*/
#define ASVL_PAF_P010_LSB 0xf02

/*12 bit Y plane followed by 12 bit 2x2 subsampled UV planes*/
/*
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y ,
  ....
  0  0  0  0  U  U  U  U  U  U  U  U  U  U  U  U ,
  0  0  0  0  V  V  V  V  V  V  V  V  V  V  V  V ,
  ....
*/
#define ASVL_PAF_P012_MSB 0xf03

/*12 bit Y plane followed by 12 bit 2x2 subsampled UV planes*/
/*
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  0  0  0  0 ,
  ....
  U  U  U  U  U  U  U  U  U  U  U  U  0  0  0  0 ,
  V  V  V  V  V  V  V  V  V  V  V  V  0  0  0  0 ,
  ....
*/
#define ASVL_PAF_P012_LSB 0xf04

/*14 bit Y plane followed by 14 bit 2x2 subsampled UV planes*/
/*
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y ,
  ....
  0  0  U  U  U  U  U  U  U  U  U  U  U  U  U  U ,
  0  0  V  V  V  V  V  V  V  V  V  V  V  V  V  V ,
  ....
*/
#define ASVL_PAF_P014_MSB 0xf05

/*14 bit Y plane followed by 14 bit 2x2 subsampled UV planes*/
/*
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  0  0 ,
  ....
  U  U  U  U  U  U  U  U  U  U  U  U  U  U  0  0 ,
  V  V  V  V  V  V  V  V  V  V  V  V  V  V  0  0 ,
  ....
*/
#define ASVL_PAF_P014_LSB 0xf06

/*Define the image format space*/
typedef struct __tag_ASVL_OFFSCREEN
{
    MUInt32 u32PixelArrayFormat;
    MInt32 i32Width;
    MInt32 i32Height;
    MUInt8 *ppu8Plane[4];
    MInt32 pi32Pitch[4];
} ASVLOFFSCREEN, *LPASVLOFFSCREEN;

/*Define the SDK Version infos. This is the template!!!*/
typedef struct __tag_ASVL_VERSION
{
    MLong lCodebase;        // Codebase version number
    MLong lMajor;           // major version number
    MLong lMinor;           // minor version number
    MLong lBuild;           // Build version number, increasable only
    const MChar *Version;   // version in string form
    const MChar *BuildDate; // latest build Date
    const MChar *CopyRight; // copyright
} ASVL_VERSION;
const ASVL_VERSION *ASVL_GetVersion();

#ifdef __cplusplus
}
#endif

#endif /*__ASVL_OFFSCREEN_H__*/
