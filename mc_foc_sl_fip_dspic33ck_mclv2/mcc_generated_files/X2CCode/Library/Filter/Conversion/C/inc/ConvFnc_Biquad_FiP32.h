/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2153 $
 * $LastChangedDate:: 2021-03-16 17:27:31 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_BIQUAD_FIP32_H
#define CONVFNC_BIQUAD_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "Biquad_FiP32.h"

/** Mask parameter data structure */
typedef struct {
    float64 b0;
    float64 b1;
    float64 b2;
    float64 a0;
    float64 a1;
    float64 a2;
    float64 ts_fact;
} BIQUAD_FIP32_MASK_PARAM;

/* public prototypes */
uint8 Biquad_FiP32_LoadMP(const BIQUAD_FIP32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 Biquad_FiP32_SaveMP(BIQUAD_FIP32 *block, BIQUAD_FIP32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 Biquad_FiP32_InitMP(BIQUAD_FIP32 *block, const BIQUAD_FIP32_MASK_PARAM *maskParam);
uint8 Biquad_FiP32_ConvertMP(BIQUAD_FIP32 *block, BIQUAD_FIP32_MASK_PARAM *maskParam);
void Biquad_FiP32_BackupMP(BIQUAD_FIP32_MASK_PARAM *maskParam);
void Biquad_FiP32_RestoreMP(BIQUAD_FIP32_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
