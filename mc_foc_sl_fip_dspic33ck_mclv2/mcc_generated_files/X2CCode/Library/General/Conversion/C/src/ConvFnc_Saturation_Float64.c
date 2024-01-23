/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_Saturation_Float64.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    float64 max;
    float64 min;
} SATURATION_FLOAT64_IMPL_PARAM;

/** Private prototypes */
static uint8 convertM2I(const SATURATION_FLOAT64_MASK_PARAM *maskParam, SATURATION_FLOAT64_IMPL_PARAM *impParam);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const SATURATION_FLOAT64_MASK_PARAM *maskParam, SATURATION_FLOAT64_IMPL_PARAM *impParam)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
    if (maskParam->min > maskParam->max)    /* limits are in false order*/
    {
        impParam->max = (float64)(maskParam->min);   /* swap limits */
        impParam->min = (float64)(maskParam->max);   /* swap limits */
    }
    else                                    /* limits are in correct order */
    {
        impParam->max = (float64)(maskParam->max);
        impParam->min = (float64)(maskParam->min);
    }

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
uint8 Saturation_Float64_LoadMP(const SATURATION_FLOAT64_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)16 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->max)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->max) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->max) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->max) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->max) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->max) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->max) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->max) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->min)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->min) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->min) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->min) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->min) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->min) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->min) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->min) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)16;
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
uint8 Saturation_Float64_SaveMP(SATURATION_FLOAT64 *block, SATURATION_FLOAT64_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)16)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        Saturation_Float64_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->min = (float64)(*(float64*)&tmp64);

        error = Saturation_Float64_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            Saturation_Float64_RestoreMP(maskParam);
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
uint8 Saturation_Float64_InitMP(SATURATION_FLOAT64 *block, const SATURATION_FLOAT64_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;

    SATURATION_FLOAT64_IMPL_PARAM *implParam = (SATURATION_FLOAT64_IMPL_PARAM*)ImplParamBuffer;

    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint64*)&(implParam->max)) & 0x00000000000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint64*)&(implParam->max) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint64*)&(implParam->max) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint64*)&(implParam->max) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint64*)&(implParam->max) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint64*)&(implParam->max) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint64*)&(implParam->max) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint64*)&(implParam->max) >> 56) & 0x00000000000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint64*)&(implParam->min)) & 0x00000000000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint64*)&(implParam->min) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint64*)&(implParam->min) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint64*)&(implParam->min) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint64*)&(implParam->min) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint64*)&(implParam->min) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint64*)&(implParam->min) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint64*)&(implParam->min) >> 56) & 0x00000000000000FF);

    /** - Execute save function of block */
    error = Saturation_Float64_Save(block, SaveFncDataBuffer, 16);

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
uint8 Saturation_Float64_ConvertMP(SATURATION_FLOAT64 *block, SATURATION_FLOAT64_MASK_PARAM *maskParam)
{
    uint8 error;
    SATURATION_FLOAT64_IMPL_PARAM *implParam = (SATURATION_FLOAT64_IMPL_PARAM*)ImplParamBuffer;

    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint64*)&(implParam->max)) & 0x00000000000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint64*)&(implParam->max) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint64*)&(implParam->max) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint64*)&(implParam->max) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint64*)&(implParam->max) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint64*)&(implParam->max) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint64*)&(implParam->max) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint64*)&(implParam->max) >> 56) & 0x00000000000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint64*)&(implParam->min)) & 0x00000000000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint64*)&(implParam->min) >> 8) & 0x00000000000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint64*)&(implParam->min) >> 16) & 0x00000000000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint64*)&(implParam->min) >> 24) & 0x00000000000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint64*)&(implParam->min) >> 32) & 0x00000000000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint64*)&(implParam->min) >> 40) & 0x00000000000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint64*)&(implParam->min) >> 48) & 0x00000000000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint64*)&(implParam->min) >> 56) & 0x00000000000000FF);

    /** - Execute save function of block */
    error = Saturation_Float64_Save(block, SaveFncDataBuffer, 16);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void Saturation_Float64_BackupMP(SATURATION_FLOAT64_MASK_PARAM* maskParam)
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
void Saturation_Float64_RestoreMP(SATURATION_FLOAT64_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
