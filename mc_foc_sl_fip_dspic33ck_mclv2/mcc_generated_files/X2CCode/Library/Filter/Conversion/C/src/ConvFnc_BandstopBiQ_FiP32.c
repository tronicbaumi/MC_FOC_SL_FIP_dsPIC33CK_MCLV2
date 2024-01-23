/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2159 $
 * $LastChangedDate:: 2021-03-22 17:32:11 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_BandstopBiQ_FiP32.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int32 b0;
    int32 b1;
    int32 b2;
    int32 a1;
    int32 a2;
    int8 sfrb0;
    int8 sfrb1;
    int8 sfrb2;
    int8 sfra1;
    int8 sfra2;
} BANDSTOPBIQ_FIP32_IMPL_PARAM;

/** characteristic enumeration */
typedef enum {
    CHARACTERISTIC_BUTTERWORTH = 0,
    CHARACTERISTIC_CHEBYSHEV = 1
} tcharacteristic;

/** Private prototypes */
static uint8 convertM2I(const BANDSTOPBIQ_FIP32_MASK_PARAM *maskParam, BANDSTOPBIQ_FIP32_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const BANDSTOPBIQ_FIP32_MASK_PARAM *maskParam, BANDSTOPBIQ_FIP32_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
//#error CONVERSION-ON-TARGET CURRENTLY NOT SUPPORTED / MASK-TO-IMPLEMENTATION CONVERSION MISSING
/* USERCODE-END:Conversion                                                                                            */
    return (error);
}

/**
 * @brief Load block mask parameter data.
 *
 * @param[in] maskParam Mask parameter data structure
 * @param[out] data Data
 * @param[out] dataLen Data length
 * @param[in] maxSize Maximum Service data length
 *
 * @return Error: zero on success, not zero in case of load- or conversion error
 */
uint8 BandstopBiQ_FiP32_LoadMP(const BANDSTOPBIQ_FIP32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)33 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(maskParam->characteristic);
        data[1] = (uint8)((*(uint64*)&(maskParam->fc1)) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->fc1) >> 8) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->fc1) >> 16) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->fc1) >> 24) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->fc1) >> 32) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->fc1) >> 40) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->fc1) >> 48) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->fc1) >> 56) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->fc2)) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->fc2) >> 8) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->fc2) >> 16) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->fc2) >> 24) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->fc2) >> 32) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->fc2) >> 40) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->fc2) >> 48) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->fc2) >> 56) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->rc)) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->rc) >> 8) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->rc) >> 16) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->rc) >> 24) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->rc) >> 32) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->rc) >> 40) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->rc) >> 48) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->rc) >> 56) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)33;
    }
    return (error);
}

/**
 * @brief Save block mask parameter data.
 *
 * @param[in] block Pointer to block structure
 * @param[out] maskParam Mask parameter data structure
 * @param[in] data Data
 * @param dataLen Length of mask parameter data stream
 *
 * @return Error: zero on success, not zero in case of save- or conversion error
 */
uint8 BandstopBiQ_FiP32_SaveMP(BANDSTOPBIQ_FIP32 *block, BANDSTOPBIQ_FIP32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)33)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        BandstopBiQ_FiP32_BackupMP(maskParam);

        /** - Save new mask parameters */
        maskParam->characteristic = data[0];
        tmp64 = (uint64)data[1] + \
            ((uint64)data[2] << 8) + ((uint64)data[3] << 16) + \
            ((uint64)data[4] << 24) + ((uint64)data[5] << 32) + \
            ((uint64)data[6] << 40) + ((uint64)data[7] << 48) + \
            ((uint64)data[8] << 56);
        maskParam->fc1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[9] + \
            ((uint64)data[10] << 8) + ((uint64)data[11] << 16) + \
            ((uint64)data[12] << 24) + ((uint64)data[13] << 32) + \
            ((uint64)data[14] << 40) + ((uint64)data[15] << 48) + \
            ((uint64)data[16] << 56);
        maskParam->fc2 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[17] + \
            ((uint64)data[18] << 8) + ((uint64)data[19] << 16) + \
            ((uint64)data[20] << 24) + ((uint64)data[21] << 32) + \
            ((uint64)data[22] << 40) + ((uint64)data[23] << 48) + \
            ((uint64)data[24] << 56);
        maskParam->rc = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[25] + \
            ((uint64)data[26] << 8) + ((uint64)data[27] << 16) + \
            ((uint64)data[28] << 24) + ((uint64)data[29] << 32) + \
            ((uint64)data[30] << 40) + ((uint64)data[31] << 48) + \
            ((uint64)data[32] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        error = BandstopBiQ_FiP32_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            BandstopBiQ_FiP32_RestoreMP(maskParam);
        }

    }
    return (error);
}

/**
 * @brief Initializes Implementation parameters from Mask parameters.
 *
 * @param[out] block Block
 * @param[in] maskParam Mask parameters
 *
 * @return Error: zero on success, not zero in case of initialization error
 */
uint8 BandstopBiQ_FiP32_InitMP(BANDSTOPBIQ_FIP32 *block, const BANDSTOPBIQ_FIP32_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    BANDSTOPBIQ_FIP32_IMPL_PARAM *implParam = (BANDSTOPBIQ_FIP32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->b0 & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->b0 >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->b0 >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->b0 >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->b1 & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b1 >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b1 >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b1 >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)(implParam->b2 & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->b2 >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->b2 >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->b2 >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->a1 & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->a1 >> 8) & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((implParam->a1 >> 16) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((implParam->a1 >> 24) & 0x000000FF);
    SaveFncDataBuffer[16] = (uint8)(implParam->a2 & 0x000000FF);
    SaveFncDataBuffer[17] = (uint8)((implParam->a2 >> 8) & 0x000000FF);
    SaveFncDataBuffer[18] = (uint8)((implParam->a2 >> 16) & 0x000000FF);
    SaveFncDataBuffer[19] = (uint8)((implParam->a2 >> 24) & 0x000000FF);
    SaveFncDataBuffer[20] = (uint8)implParam->sfrb0;
    SaveFncDataBuffer[21] = (uint8)implParam->sfrb1;
    SaveFncDataBuffer[22] = (uint8)implParam->sfrb2;
    SaveFncDataBuffer[23] = (uint8)implParam->sfra1;
    SaveFncDataBuffer[24] = (uint8)implParam->sfra2;

    /** - Execute save function of block */
    error = BandstopBiQ_FiP32_Save(block, SaveFncDataBuffer, 25);

    return (error);
}

/**
 * @brief Converts Mask parameters into Implementation parameters and executes Block Save function.
 *
 * @param[out] block Block Implementation
 * @param[in] maskParam Mask Parameters
 *
 * @return 0 if successful, greater than 0 if conversion failed
 */
uint8 BandstopBiQ_FiP32_ConvertMP(BANDSTOPBIQ_FIP32 *block, BANDSTOPBIQ_FIP32_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    BANDSTOPBIQ_FIP32_IMPL_PARAM *implParam = (BANDSTOPBIQ_FIP32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->b0 & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->b0 >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->b0 >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->b0 >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->b1 & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b1 >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b1 >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b1 >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)(implParam->b2 & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->b2 >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->b2 >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->b2 >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->a1 & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->a1 >> 8) & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((implParam->a1 >> 16) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((implParam->a1 >> 24) & 0x000000FF);
    SaveFncDataBuffer[16] = (uint8)(implParam->a2 & 0x000000FF);
    SaveFncDataBuffer[17] = (uint8)((implParam->a2 >> 8) & 0x000000FF);
    SaveFncDataBuffer[18] = (uint8)((implParam->a2 >> 16) & 0x000000FF);
    SaveFncDataBuffer[19] = (uint8)((implParam->a2 >> 24) & 0x000000FF);
    SaveFncDataBuffer[20] = (uint8)implParam->sfrb0;
    SaveFncDataBuffer[21] = (uint8)implParam->sfrb1;
    SaveFncDataBuffer[22] = (uint8)implParam->sfrb2;
    SaveFncDataBuffer[23] = (uint8)implParam->sfra1;
    SaveFncDataBuffer[24] = (uint8)implParam->sfra2;

    /** - Execute save function of block */
    error = BandstopBiQ_FiP32_Save(block, SaveFncDataBuffer, 25);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void BandstopBiQ_FiP32_BackupMP(BANDSTOPBIQ_FIP32_MASK_PARAM* maskParam)
{
    memcpy(MaskParamBuffer, maskParam, sizeof(*maskParam));
}

/**
 * @brief Restores Mask parameters from global Mask parameter backup array.
 *
 * @param[out] maskParam Mask parameters
 *
 * @return Nothing
 */
void BandstopBiQ_FiP32_RestoreMP(BANDSTOPBIQ_FIP32_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
