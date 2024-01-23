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
 * $LastChangedRevision: 2161 $
 * $LastChangedDate:: 2021-03-23 15:47:26 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_HIGHPASSBIQ_FIP16_H
#define CONVFNC_HIGHPASSBIQ_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "HighpassBiQ_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    uint8 characteristic;
    float64 fc;
    float64 rp;
    float64 rs;
    float64 ts_fact;
} HIGHPASSBIQ_FIP16_MASK_PARAM;

/* public prototypes */
uint8 HighpassBiQ_FiP16_LoadMP(const HIGHPASSBIQ_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 HighpassBiQ_FiP16_SaveMP(HIGHPASSBIQ_FIP16 *block, HIGHPASSBIQ_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 HighpassBiQ_FiP16_InitMP(HIGHPASSBIQ_FIP16 *block, const HIGHPASSBIQ_FIP16_MASK_PARAM *maskParam);
uint8 HighpassBiQ_FiP16_ConvertMP(HIGHPASSBIQ_FIP16 *block, HIGHPASSBIQ_FIP16_MASK_PARAM *maskParam);
void HighpassBiQ_FiP16_BackupMP(HIGHPASSBIQ_FIP16_MASK_PARAM *maskParam);
void HighpassBiQ_FiP16_RestoreMP(HIGHPASSBIQ_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
