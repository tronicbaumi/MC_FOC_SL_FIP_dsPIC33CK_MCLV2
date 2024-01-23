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
#ifndef CONVFNC_IIR_FIP16_H
#define CONVFNC_IIR_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "IIR_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    float64 CoeffB;
    float64 CoeffA;
    float64 ts_fact;
} IIR_FIP16_MASK_PARAM;

/* public prototypes */
uint8 IIR_FiP16_LoadMP(const IIR_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 IIR_FiP16_SaveMP(IIR_FIP16 *block, IIR_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 IIR_FiP16_InitMP(IIR_FIP16 *block, const IIR_FIP16_MASK_PARAM *maskParam);
uint8 IIR_FiP16_ConvertMP(IIR_FIP16 *block, IIR_FIP16_MASK_PARAM *maskParam);
void IIR_FiP16_BackupMP(IIR_FIP16_MASK_PARAM *maskParam);
void IIR_FiP16_RestoreMP(IIR_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
