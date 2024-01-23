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
#ifndef CONVFNC_BANDSTOPBIQ_FIP16_H
#define CONVFNC_BANDSTOPBIQ_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "BandstopBiQ_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    uint8 characteristic;
    float64 fc1;
    float64 fc2;
    float64 rc;
    float64 ts_fact;
} BANDSTOPBIQ_FIP16_MASK_PARAM;

/* public prototypes */
uint8 BandstopBiQ_FiP16_LoadMP(const BANDSTOPBIQ_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 BandstopBiQ_FiP16_SaveMP(BANDSTOPBIQ_FIP16 *block, BANDSTOPBIQ_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 BandstopBiQ_FiP16_InitMP(BANDSTOPBIQ_FIP16 *block, const BANDSTOPBIQ_FIP16_MASK_PARAM *maskParam);
uint8 BandstopBiQ_FiP16_ConvertMP(BANDSTOPBIQ_FIP16 *block, BANDSTOPBIQ_FIP16_MASK_PARAM *maskParam);
void BandstopBiQ_FiP16_BackupMP(BANDSTOPBIQ_FIP16_MASK_PARAM *maskParam);
void BandstopBiQ_FiP16_RestoreMP(BANDSTOPBIQ_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
