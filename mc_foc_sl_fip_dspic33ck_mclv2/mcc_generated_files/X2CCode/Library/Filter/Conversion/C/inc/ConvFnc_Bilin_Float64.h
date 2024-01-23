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
#ifndef CONVFNC_BILIN_FLOAT64_H
#define CONVFNC_BILIN_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "Bilin_Float64.h"

/** Mask parameter data structure */
typedef struct {
    float64 b0;
    float64 b1;
    float64 a0;
    float64 a1;
    float64 ts_fact;
} BILIN_FLOAT64_MASK_PARAM;

/* public prototypes */
uint8 Bilin_Float64_LoadMP(const BILIN_FLOAT64_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 Bilin_Float64_SaveMP(BILIN_FLOAT64 *block, BILIN_FLOAT64_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 Bilin_Float64_InitMP(BILIN_FLOAT64 *block, const BILIN_FLOAT64_MASK_PARAM *maskParam);
uint8 Bilin_Float64_ConvertMP(BILIN_FLOAT64 *block, BILIN_FLOAT64_MASK_PARAM *maskParam);
void Bilin_Float64_BackupMP(BILIN_FLOAT64_MASK_PARAM *maskParam);
void Bilin_Float64_RestoreMP(BILIN_FLOAT64_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
