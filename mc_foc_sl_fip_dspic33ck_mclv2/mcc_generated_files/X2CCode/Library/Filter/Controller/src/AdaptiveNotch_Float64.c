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
#include "AdaptiveNotch_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(AdaptiveNotch_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Inputs */
#define IN              (*pTAdaptiveNotch_Float64->In)
#define N               (*pTAdaptiveNotch_Float64->n)

/* Outputs */
#define OUT             (pTAdaptiveNotch_Float64->Out)

/* Parameter */
#define N_THRESH        (pTAdaptiveNotch_Float64->n_thresh)
#define A_FACT          (pTAdaptiveNotch_Float64->a_fact)
#define B_FACT          (pTAdaptiveNotch_Float64->b_fact)
#define C_FACT          (pTAdaptiveNotch_Float64->c_fact)

/* Variables */
#define A2              (pTAdaptiveNotch_Float64->a2)
#define A1              (pTAdaptiveNotch_Float64->a1)
#define B1              (pTAdaptiveNotch_Float64->b1)
#define K               (pTAdaptiveNotch_Float64->k)
#define IN_OLD          (pTAdaptiveNotch_Float64->in_old)
#define IN_VERY_OLD     (pTAdaptiveNotch_Float64->in_very_old)
#define OUT_OLD         (pTAdaptiveNotch_Float64->out_old)
#define OUT_VERY_OLD    (pTAdaptiveNotch_Float64->out_very_old)
#define N_OLD           (pTAdaptiveNotch_Float64->n_old)

/* Constants */
#define A0  1.0
#define B0  1.0
#define B2  1.0

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void AdaptiveNotch_Float64_Update(ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float64 temp;
    float64 absN;
    
    absN = ABS_R64(N);

    if (absN > N_THRESH)
    {
        /* current speed is above threshold -> filter the input signal */    
        if (N != N_OLD)
        {
            /* speed has changed -> update filter coefficients */
            float64 expA;

            expA = exp(absN * A_FACT);              /* exp(A) */

            /** - calculate filter coefficients */
            A1 = -2.0 * expA * cos(absN * B_FACT);  /* -2 * exp(A) * cos(B) */
            A2 = expA * expA;                       /* exp(2*A) */ 
            B1 = -2.0 * cos(absN * C_FACT);         /* -2 * cos(C) */

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
void AdaptiveNotch_Float64_Init(ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64)
{
    pTAdaptiveNotch_Float64->ID = ADAPTIVENOTCH_FLOAT64_ID;
    pTAdaptiveNotch_Float64->Out = 0;
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
uint8 AdaptiveNotch_Float64_Load(const ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)32 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->a_fact) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->b_fact) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->c_fact) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(pTAdaptiveNotch_Float64->n_thresh) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)32;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptiveNotch_Float64_Save(ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)32)
    {
        error = (uint8)1;
    }
    else
    {
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        pTAdaptiveNotch_Float64->a_fact = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTAdaptiveNotch_Float64->b_fact = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTAdaptiveNotch_Float64->c_fact = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        pTAdaptiveNotch_Float64->n_thresh = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ADAPTIVENOTCH_FLOAT64_ISLINKED)
void* AdaptiveNotch_Float64_GetAddress(const ADAPTIVENOTCH_FLOAT64* block, uint16 elementId)
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
