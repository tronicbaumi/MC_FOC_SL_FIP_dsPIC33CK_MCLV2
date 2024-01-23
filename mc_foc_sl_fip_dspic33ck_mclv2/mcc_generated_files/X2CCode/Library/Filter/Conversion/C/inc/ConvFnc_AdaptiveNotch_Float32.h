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
 * $LastChangedRevision: 2112 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_ADAPTIVENOTCH_FLOAT32_H
#define CONVFNC_ADAPTIVENOTCH_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "AdaptiveNotch_Float32.h"

/** Mask parameter data structure */
typedef struct {
    float64 Q;
    float64 n_thresh;
    float64 n_max;
    float64 p;
    float64 ts_fact;
    uint8 method;
} ADAPTIVENOTCH_FLOAT32_MASK_PARAM;

/* public prototypes */
uint8 AdaptiveNotch_Float32_LoadMP(const ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 AdaptiveNotch_Float32_SaveMP(ADAPTIVENOTCH_FLOAT32 *block, ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 AdaptiveNotch_Float32_InitMP(ADAPTIVENOTCH_FLOAT32 *block, const ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam);
uint8 AdaptiveNotch_Float32_ConvertMP(ADAPTIVENOTCH_FLOAT32 *block, ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam);
void AdaptiveNotch_Float32_BackupMP(ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam);
void AdaptiveNotch_Float32_RestoreMP(ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
