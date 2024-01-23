/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1975 $
 * $LastChangedDate:: 2020-07-20 16:25:13 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_Sin2Limiter_Float64.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    float64 RateUp;
    float64 RateDown;
} SIN2LIMITER_FLOAT64_IMPL_PARAM;

/** Private prototypes */
static uint8 convertM2I(const SIN2LIMITER_FLOAT64_MASK_PARAM *maskParam, SIN2LIMITER_FLOAT64_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const SIN2LIMITER_FLOAT64_MASK_PARAM *maskParam, SIN2LIMITER_FLOAT64_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
    float_CoT mp_Tr, mp_Tf;

    mp_Tr = maskParam->Tr;
    mp_Tf = maskParam->Tf;

    /* check range of rising/falling time */
    if (mp_Tr < ts)
    {
        mp_Tr = ts;
    }
    if (mp_Tf < ts)
    {
        mp_Tf = ts;
    }

    impParam->RateUp = (float64)(ts/mp_Tr*PI_R64*(float64)0.5);     /* pi/2 due to sin^2(0) ... sin^2(pi/2) */
    impParam->RateDown = (float64)(ts/mp_Tf*PI_R64*(float64)0.5);   /* pi/2 due to sin^2(0) ... sin^2(pi/2) */

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
uint8 Sin2Limiter_Float64_LoadMP(const SIN2LIMITER_FLOAT64_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)24 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->Tr)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->Tr) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->Tr) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->Tr) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->Tr) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->Tr) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->Tr) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->Tr) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->Tf)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->Tf) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->Tf) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->Tf) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->Tf) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->Tf) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->Tf) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->Tf) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)24;
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
uint8 Sin2Limiter_Float64_SaveMP(SIN2LIMITER_FLOAT64 *block, SIN2LIMITER_FLOAT64_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)24)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        Sin2Limiter_Float64_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->Tr = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->Tf = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        error = Sin2Limiter_Float64_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            Sin2Limiter_Float64_RestoreMP(maskParam);
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
uint8 Sin2Limiter_Float64_InitMP(SIN2LIMITER_FLOAT64 *block, const SIN2LIMITER_FLOAT64_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    SIN2LIMITER_FLOAT64_IMPL_PARAM *implParam = (SIN2LIMITER_FLOAT64_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint64*)&(implParam->RateUp)) & 0x00000000000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint64*)&(implParam->RateUp) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint64*)&(implParam->RateUp) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint64*)&(implParam->RateUp) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint64*)&(implParam->RateUp) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint64*)&(implParam->RateUp) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint64*)&(implParam->RateUp) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint64*)&(implParam->RateUp) >> 56) & 0x00000000000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint64*)&(implParam->RateDown)) & 0x00000000000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint64*)&(implParam->RateDown) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint64*)&(implParam->RateDown) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint64*)&(implParam->RateDown) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint64*)&(implParam->RateDown) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint64*)&(implParam->RateDown) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint64*)&(implParam->RateDown) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint64*)&(implParam->RateDown) >> 56) & 0x00000000000000FF);

    /** - Execute save function of block */
    error = Sin2Limiter_Float64_Save(block, SaveFncDataBuffer, 16);

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
uint8 Sin2Limiter_Float64_ConvertMP(SIN2LIMITER_FLOAT64 *block, SIN2LIMITER_FLOAT64_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    SIN2LIMITER_FLOAT64_IMPL_PARAM *implParam = (SIN2LIMITER_FLOAT64_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint64*)&(implParam->RateUp)) & 0x00000000000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint64*)&(implParam->RateUp) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint64*)&(implParam->RateUp) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint64*)&(implParam->RateUp) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint64*)&(implParam->RateUp) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint64*)&(implParam->RateUp) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint64*)&(implParam->RateUp) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint64*)&(implParam->RateUp) >> 56) & 0x00000000000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint64*)&(implParam->RateDown)) & 0x00000000000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint64*)&(implParam->RateDown) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint64*)&(implParam->RateDown) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint64*)&(implParam->RateDown) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint64*)&(implParam->RateDown) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint64*)&(implParam->RateDown) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint64*)&(implParam->RateDown) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint64*)&(implParam->RateDown) >> 56) & 0x00000000000000FF);

    /** - Execute save function of block */
    error = Sin2Limiter_Float64_Save(block, SaveFncDataBuffer, 16);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void Sin2Limiter_Float64_BackupMP(SIN2LIMITER_FLOAT64_MASK_PARAM* maskParam)
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
void Sin2Limiter_Float64_RestoreMP(SIN2LIMITER_FLOAT64_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
