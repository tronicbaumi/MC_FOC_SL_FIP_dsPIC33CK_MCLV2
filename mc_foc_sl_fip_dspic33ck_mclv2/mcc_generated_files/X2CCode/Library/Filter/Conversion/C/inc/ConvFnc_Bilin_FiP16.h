/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2153 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_BILIN_FIP16_H
#define CONVFNC_BILIN_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "Bilin_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    float64 b0;
    float64 b1;
    float64 a0;
    float64 a1;
    float64 ts_fact;
} BILIN_FIP16_MASK_PARAM;

/* public prototypes */
uint8 Bilin_FiP16_LoadMP(const BILIN_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 Bilin_FiP16_SaveMP(BILIN_FIP16 *block, BILIN_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 Bilin_FiP16_InitMP(BILIN_FIP16 *block, const BILIN_FIP16_MASK_PARAM *maskParam);
uint8 Bilin_FiP16_ConvertMP(BILIN_FIP16 *block, BILIN_FIP16_MASK_PARAM *maskParam);
void Bilin_FiP16_BackupMP(BILIN_FIP16_MASK_PARAM *maskParam);
void Bilin_FiP16_RestoreMP(BILIN_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
