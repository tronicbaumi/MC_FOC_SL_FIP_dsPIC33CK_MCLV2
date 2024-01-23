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
#include "AdaptiveNotch_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(AdaptiveNotch_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Exp_Data.h"
#include "Sin_Data.h"

/* Inputs */
#define IN              (*pTAdaptiveNotch_FiP16->In)
#define N               (*pTAdaptiveNotch_FiP16->n)

/* Outputs */
#define OUT             (pTAdaptiveNotch_FiP16->Out)

/* Parameter */
#define N_THRESH        (pTAdaptiveNotch_FiP16->n_thresh)
#define A_FACT          (pTAdaptiveNotch_FiP16->a_fact)
#define B_FACT          (pTAdaptiveNotch_FiP16->b_fact)
#define C_FACT          (pTAdaptiveNotch_FiP16->c_fact)
#define SFR_A           (pTAdaptiveNotch_FiP16->sfrA)

/* Variables */
#define A2              (pTAdaptiveNotch_FiP16->a2)
#define A1              (pTAdaptiveNotch_FiP16->a1)
#define B1              (pTAdaptiveNotch_FiP16->b1)
#define K               (pTAdaptiveNotch_FiP16->k)
#define IN_OLD          (pTAdaptiveNotch_FiP16->in_old)
#define IN_VERY_OLD     (pTAdaptiveNotch_FiP16->in_very_old)
#define OUT_OLD         (pTAdaptiveNotch_FiP16->out_old)
#define OUT_VERY_OLD    (pTAdaptiveNotch_FiP16->out_very_old)
#define N_OLD           (pTAdaptiveNotch_FiP16->n_old)

/* Constants */
#define A0              ((int16)INT16_MAX)
#define B0              ((int16)INT16_MAX)
#define B2              ((int16)INT16_MAX)
#define PI_HALF         ((int16)0x4000)         /* Pi/2	[Q15] */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void AdaptiveNotch_FiP16_Update(ADAPTIVENOTCH_FIP16 *pTAdaptiveNotch_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    int32 temp32;
    int16 absN;
    
    /* calculate absolute value of speed to ensure correct computation of coefficients */
    absN = getAbsValI16(N);

    if (absN > N_THRESH)
    {
        /* current speed is above threshold -> filter the input signal */
        if (N != N_OLD)
        {
            /* speed has changed -> update filter coefficients */
            int16 expA, cosine, temp;
       
            temp = ((int32)absN * (int32)A_FACT) >> SFR_A;  /* A = -w0/2/Q*Ts */
            LOOKUP16(Exp_Table16, temp, expA);              /* exp(A) */

            /** - calculate filter coefficients */
            temp = ((int32)absN * (int32)B_FACT) >> 15;     /* B = -w0/2/Q*(sqrt(4*Q^2-1))*Ts */
            temp = PI_HALF - temp;	                        /* cos(temp) = sin(pi/2 - temp) */
            LOOKUP16(Sin_Table16, temp, cosine);            /* cos(B)*/
            A1 = -((int32)expA * (int32)cosine) >> 15;      /* -2 * exp(A) * cos(B)  [Q14] */
            
            A2 = ((int32)expA * (int32)expA) >> 15;         /* exp(2*A) [Q15] */  
            
            temp = ((int32)absN * (int32)C_FACT) >> 15;     /* C = w0 * Ts */
            temp = PI_HALF - temp;	                        /* cos(temp) = sin(pi/2 - temp) */
            LOOKUP16(Sin_Table16, temp, cosine);            /* cos(C)*/
            B1 = -cosine;                                   /* -2 * cos(C) [Q14] */

            /** - calculate gain correction value */
            K = (((int32)A0 + (((int32)A1)<<1) + (int32)A2) << 15) / ((((int32)B0)) + (((int32)B1)<<1) + (((int32)B2))); /* Q30 / Q15 = Q15 */

            N_OLD = N;
        }

        /** - do the filtering */
        temp32  = (int32)IN;                                    /* b0*u(k) */
        temp32 += (((int32)B1 * (int32)IN_OLD) >> 14);          /* b1*u(k-1)*/
        temp32 += ((int32)IN_VERY_OLD);                         /* b2*u(k-2) */
        temp32  = (temp32 * (int32)K) >> 15;                    /* adjust gain */
        temp32 -= (((int32)A1 * (int32)OUT_OLD) >> 14);         /* a1*y(k-1)*/
        temp32 -= (((int32)A2 * (int32)OUT_VERY_OLD) >> 15);    /* a2*y(k-2)*/

        
        /** - set output */
        LIMIT(temp32, INT16_MAX);
        OUT = (int16)temp32;            /* y(k) = b0*u(k) + b1*u(k-1) + b2*u(k-2) - a1*y(k-1) - a2*y(k-2) */
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
void AdaptiveNotch_FiP16_Init(ADAPTIVENOTCH_FIP16 *pTAdaptiveNotch_FiP16)
{
    pTAdaptiveNotch_FiP16->ID = ADAPTIVENOTCH_FIP16_ID;
    pTAdaptiveNotch_FiP16->Out = 0;
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
uint8 AdaptiveNotch_FiP16_Load(const ADAPTIVENOTCH_FIP16 *pTAdaptiveNotch_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)9 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTAdaptiveNotch_FiP16->n_thresh & 0x00FF);
        data[1] = (uint8)((pTAdaptiveNotch_FiP16->n_thresh >> 8) & 0x00FF);
        data[2] = (uint8)(pTAdaptiveNotch_FiP16->a_fact & 0x00FF);
        data[3] = (uint8)((pTAdaptiveNotch_FiP16->a_fact >> 8) & 0x00FF);
        data[4] = (uint8)(pTAdaptiveNotch_FiP16->b_fact & 0x00FF);
        data[5] = (uint8)((pTAdaptiveNotch_FiP16->b_fact >> 8) & 0x00FF);
        data[6] = (uint8)(pTAdaptiveNotch_FiP16->c_fact & 0x00FF);
        data[7] = (uint8)((pTAdaptiveNotch_FiP16->c_fact >> 8) & 0x00FF);
        data[8] = (uint8)pTAdaptiveNotch_FiP16->sfrA;
        *dataLength = (uint16)9;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptiveNotch_FiP16_Save(ADAPTIVENOTCH_FIP16 *pTAdaptiveNotch_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)9)
    {
        error = (uint8)1;
    }
    else
    {
        pTAdaptiveNotch_FiP16->n_thresh = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTAdaptiveNotch_FiP16->a_fact = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTAdaptiveNotch_FiP16->b_fact = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTAdaptiveNotch_FiP16->c_fact = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTAdaptiveNotch_FiP16->sfrA = UINT8_TO_INT8((uint8)data[8]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ADAPTIVENOTCH_FIP16_ISLINKED)
void* AdaptiveNotch_FiP16_GetAddress(const ADAPTIVENOTCH_FIP16* block, uint16 elementId)
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
