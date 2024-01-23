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
#ifndef CONVFNC_BANDPASSBIQ_FLOAT64_H
#define CONVFNC_BANDPASSBIQ_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "BandpassBiQ_Float64.h"

/** Mask parameter data structure */
typedef struct {
    uint8 characteristic;
    float64 fc1;
    float64 fc2;
    float64 rc;
    float64 ts_fact;
} BANDPASSBIQ_FLOAT64_MASK_PARAM;

/* public prototypes */
uint8 BandpassBiQ_Float64_LoadMP(const BANDPASSBIQ_FLOAT64_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 BandpassBiQ_Float64_SaveMP(BANDPASSBIQ_FLOAT64 *block, BANDPASSBIQ_FLOAT64_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 BandpassBiQ_Float64_InitMP(BANDPASSBIQ_FLOAT64 *block, const BANDPASSBIQ_FLOAT64_MASK_PARAM *maskParam);
uint8 BandpassBiQ_Float64_ConvertMP(BANDPASSBIQ_FLOAT64 *block, BANDPASSBIQ_FLOAT64_MASK_PARAM *maskParam);
void BandpassBiQ_Float64_BackupMP(BANDPASSBIQ_FLOAT64_MASK_PARAM *maskParam);
void BandpassBiQ_Float64_RestoreMP(BANDPASSBIQ_FLOAT64_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
