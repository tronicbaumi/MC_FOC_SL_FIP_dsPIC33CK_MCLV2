/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2582 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Implementation:
 *
 *   A = -w0/2/Q*Ts
 *   B = -w0/2/Q*(sqrt(4*Q^2-1))*Ts
 *   C = w0*Ts
 *   a = [1, -2 * exp(A) * cos(B), exp(2*A)]
 *   b = [1, -2 * cos(C),          1]
 *
 *   K = sum(a) / sum(b)
 *   b = b * K
 */
/* USERCODE-END:Description                                                                                           */
#include "AdaptiveNotch_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(AdaptiveNotch_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Inputs */
#define IN              (*pTAdaptiveNotch_Float32->In)
#define N               (*pTAdaptiveNotch_Float32->n)

/* Outputs */
#define OUT             (pTAdaptiveNotch_Float32->Out)

/* Parameter */
#define N_THRESH        (pTAdaptiveNotch_Float32->n_thresh)
#define A_FACT          (pTAdaptiveNotch_Float32->a_fact)
#define B_FACT          (pTAdaptiveNotch_Float32->b_fact)
#define C_FACT          (pTAdaptiveNotch_Float32->c_fact)

/* Variables */
#define A2              (pTAdaptiveNotch_Float32->a2)
#define A1              (pTAdaptiveNotch_Float32->a1)
#define B1              (pTAdaptiveNotch_Float32->b1)
#define K               (pTAdaptiveNotch_Float32->k)
#define IN_OLD          (pTAdaptiveNotch_Float32->in_old)
#define IN_VERY_OLD     (pTAdaptiveNotch_Float32->in_very_old)
#define OUT_OLD         (pTAdaptiveNotch_Float32->out_old)
#define OUT_VERY_OLD    (pTAdaptiveNotch_Float32->out_very_old)
#define N_OLD           (pTAdaptiveNotch_Float32->n_old)

/* Constants */
#define A0  1.0f
#define B0  1.0f
#define B2  1.0f

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void AdaptiveNotch_Float32_Update(ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float32 temp;
    float32 absN;
    
    /* calculate absolute value of speed to ensure correct computation of coefficients */
    absN = ABS_R32(N);

    if (absN > N_THRESH)
    {
        /* current speed is above threshold -> filter the input signal */
        if (N != N_OLD)
        {
            /* speed has changed -> update filter coefficients */
            float32 expA;

            expA = expf(absN * A_FACT);             /* exp(A) */

            /** - calculate filter coefficients */
            A1 = -2.0f * expA * cosf(absN * B_FACT);/* -2 * exp(A) * cos(B) */
            A2 = expA * expA;                       /* exp(2*A) */ 
            B1 = -2.0f * cosf(absN * C_FACT);       /* -2 * cos(C) */

            /** - calculate gain correction value */
            K = (A0 + A1 + A2) / (B0 + B1 + B2);
            
            N_OLD = N;
        }

        /** - do the filtering */
        temp  = (IN + (B1 * IN_OLD) + IN_VERY_OLD);         /* b0*u(k) + b1*u(k-1) + b2*u(k-2) */
        temp  = temp * K;                                   /* adjust gain */
        temp -= ((A1 * OUT_OLD) + (A2 * OUT_VERY_OLD));     /* a1*y(k-1) + a2*y(k-2)*/

        /** - set output */
        OUT = temp;                 /* y(k) = b0*u(k) + b1*u(k-1) + b2*u(k-2) - a1*y(k-1) - a2*y(k-2) */
    }
    else
    {
        /* current speed is below threshold -> do not filter the input signal */
        OUT = IN;
    }

    /** - save in- and output values for next cycle */
    IN_VERY_OLD = IN_OLD;
    IN_OLD = IN;
    OUT_VERY_OLD = OUT_OLD;
    OUT_OLD = OUT;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void AdaptiveNotch_Float32_Init(ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32)
{
    pTAdaptiveNotch_Float32->ID = ADAPTIVENOTCH_FLOAT32_ID;
    pTAdaptiveNotch_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    A2 = 0;
    A1 = 0;
    B1 = 0;
    IN_VERY_OLD = 0;
    IN_OLD = 0;
    OUT_VERY_OLD = 0;
    OUT_OLD = 0;
    N_OLD = 0;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptiveNotch_Float32_Load(const ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)16 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->a_fact)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->a_fact) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->a_fact) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->a_fact) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->b_fact)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->b_fact) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->b_fact) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->b_fact) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->c_fact)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->c_fact) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->c_fact) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->c_fact) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->n_thresh)) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->n_thresh) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->n_thresh) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTAdaptiveNotch_Float32->n_thresh) >> 24) & 0x000000FF);
        *dataLength = (uint16)16;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptiveNotch_Float32_Save(ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)16)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTAdaptiveNotch_Float32->a_fact = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTAdaptiveNotch_Float32->b_fact = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTAdaptiveNotch_Float32->c_fact = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTAdaptiveNotch_Float32->n_thresh = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ADAPTIVENOTCH_FLOAT32_ISLINKED)
void* AdaptiveNotch_Float32_GetAddress(const ADAPTIVENOTCH_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->n;
            break;
        case 3:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
