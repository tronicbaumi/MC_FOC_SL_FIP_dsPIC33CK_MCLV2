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
#include "IIR_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(IIR_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			    (*pTIIR_Float32->In)

/* Outputs */
#define OUT			    (pTIIR_Float32->Out)

/* Parameter */
#define	COEFF_A			(pTIIR_Float32->coeffA)         /* Denominator coefficients array in reversed order (an,...,a2,a1) */
#define	COEFF_B			(pTIIR_Float32->coeffB)         /* Numerator coefficients array in reversed order (bn,...,b2,b1,b0) */
#define ORDER_N			(pTIIR_Float32->orderN)         /* Length of numerator coefficients array */
#define ORDER_D			(pTIIR_Float32->orderD)         /* Length of denominator coefficients array */

/* Variables */
#define BUFFER_IN       (pTIIR_Float32->inputBuffer)    /* Circular buffer for input signal */
#define BUFFER_OUT      (pTIIR_Float32->outputBuffer)   /* Circular buffer for output signal */
#define IDX_IN			(pTIIR_Float32->indexIn)        /* Pointer to current position in input buffer */
#define IDX_OUT			(pTIIR_Float32->indexOut)       /* Pointer to current position in output buffer */

/* Constants */
#define BUFFER_LEN      (32)                            /* Maximum length of circular buffer */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void IIR_Float32_Update(IIR_FLOAT32 *pTIIR_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int8 i;
	float32 sumA = 0, sumB = 0;

    /* enter In(k) and Out(k-1) in circular buffer */
    BUFFER_IN[IDX_IN]   = IN;
    BUFFER_OUT[IDX_OUT] = OUT;

    /* increase pointers to circular buffers */
	IDX_IN  = (IDX_IN  + 1) % ORDER_N;  /* pointer to element k-N */
	IDX_OUT = (IDX_OUT + 1) % ORDER_D;  /* pointer to element k-D */

    /* calculate sums of numerator and denominator */
    for (i=0; i < ORDER_N; i++)
    {
        sumB += (COEFF_B[i] * BUFFER_IN[(IDX_IN + i) % ORDER_N]);
		sumA += (COEFF_A[i] * BUFFER_OUT[(IDX_OUT + i) % ORDER_D]);
	}
    for (i=ORDER_N; i < ORDER_D; i++)
    {
        sumA += (COEFF_A[i] * BUFFER_OUT[(IDX_OUT + i) % ORDER_D]);
    }
    
    /* calculate total sum and assign output */
	OUT = sumB - sumA;
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void IIR_Float32_Init(IIR_FLOAT32 *pTIIR_Float32)
{
    pTIIR_Float32->ID = IIR_FLOAT32_ID;
    pTIIR_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    IDX_IN = 0;
	IDX_OUT = 0;
    {
        int8 i;
        for (i=0; i < (BUFFER_LEN-1); i++)
        {
            BUFFER_IN[i]  = 0;
            BUFFER_OUT[i] = 0;
        }
        BUFFER_IN[i+1] = 0;
    }
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 IIR_Float32_Load(const IIR_FLOAT32 *pTIIR_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)254 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[0])) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[0]) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[0]) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[0]) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[1])) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[1]) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[1]) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[1]) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[2])) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[2]) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[2]) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[2]) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[3])) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[3]) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[3]) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[3]) >> 24) & 0x000000FF);
        data[16] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[4])) & 0x000000FF);
        data[17] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[4]) >> 8) & 0x000000FF);
        data[18] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[4]) >> 16) & 0x000000FF);
        data[19] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[4]) >> 24) & 0x000000FF);
        data[20] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[5])) & 0x000000FF);
        data[21] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[5]) >> 8) & 0x000000FF);
        data[22] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[5]) >> 16) & 0x000000FF);
        data[23] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[5]) >> 24) & 0x000000FF);
        data[24] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[6])) & 0x000000FF);
        data[25] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[6]) >> 8) & 0x000000FF);
        data[26] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[6]) >> 16) & 0x000000FF);
        data[27] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[6]) >> 24) & 0x000000FF);
        data[28] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[7])) & 0x000000FF);
        data[29] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[7]) >> 8) & 0x000000FF);
        data[30] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[7]) >> 16) & 0x000000FF);
        data[31] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[7]) >> 24) & 0x000000FF);
        data[32] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[8])) & 0x000000FF);
        data[33] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[8]) >> 8) & 0x000000FF);
        data[34] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[8]) >> 16) & 0x000000FF);
        data[35] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[8]) >> 24) & 0x000000FF);
        data[36] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[9])) & 0x000000FF);
        data[37] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[9]) >> 8) & 0x000000FF);
        data[38] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[9]) >> 16) & 0x000000FF);
        data[39] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[9]) >> 24) & 0x000000FF);
        data[40] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[10])) & 0x000000FF);
        data[41] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[10]) >> 8) & 0x000000FF);
        data[42] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[10]) >> 16) & 0x000000FF);
        data[43] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[10]) >> 24) & 0x000000FF);
        data[44] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[11])) & 0x000000FF);
        data[45] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[11]) >> 8) & 0x000000FF);
        data[46] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[11]) >> 16) & 0x000000FF);
        data[47] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[11]) >> 24) & 0x000000FF);
        data[48] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[12])) & 0x000000FF);
        data[49] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[12]) >> 8) & 0x000000FF);
        data[50] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[12]) >> 16) & 0x000000FF);
        data[51] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[12]) >> 24) & 0x000000FF);
        data[52] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[13])) & 0x000000FF);
        data[53] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[13]) >> 8) & 0x000000FF);
        data[54] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[13]) >> 16) & 0x000000FF);
        data[55] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[13]) >> 24) & 0x000000FF);
        data[56] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[14])) & 0x000000FF);
        data[57] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[14]) >> 8) & 0x000000FF);
        data[58] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[14]) >> 16) & 0x000000FF);
        data[59] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[14]) >> 24) & 0x000000FF);
        data[60] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[15])) & 0x000000FF);
        data[61] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[15]) >> 8) & 0x000000FF);
        data[62] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[15]) >> 16) & 0x000000FF);
        data[63] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[15]) >> 24) & 0x000000FF);
        data[64] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[16])) & 0x000000FF);
        data[65] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[16]) >> 8) & 0x000000FF);
        data[66] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[16]) >> 16) & 0x000000FF);
        data[67] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[16]) >> 24) & 0x000000FF);
        data[68] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[17])) & 0x000000FF);
        data[69] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[17]) >> 8) & 0x000000FF);
        data[70] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[17]) >> 16) & 0x000000FF);
        data[71] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[17]) >> 24) & 0x000000FF);
        data[72] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[18])) & 0x000000FF);
        data[73] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[18]) >> 8) & 0x000000FF);
        data[74] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[18]) >> 16) & 0x000000FF);
        data[75] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[18]) >> 24) & 0x000000FF);
        data[76] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[19])) & 0x000000FF);
        data[77] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[19]) >> 8) & 0x000000FF);
        data[78] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[19]) >> 16) & 0x000000FF);
        data[79] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[19]) >> 24) & 0x000000FF);
        data[80] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[20])) & 0x000000FF);
        data[81] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[20]) >> 8) & 0x000000FF);
        data[82] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[20]) >> 16) & 0x000000FF);
        data[83] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[20]) >> 24) & 0x000000FF);
        data[84] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[21])) & 0x000000FF);
        data[85] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[21]) >> 8) & 0x000000FF);
        data[86] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[21]) >> 16) & 0x000000FF);
        data[87] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[21]) >> 24) & 0x000000FF);
        data[88] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[22])) & 0x000000FF);
        data[89] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[22]) >> 8) & 0x000000FF);
        data[90] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[22]) >> 16) & 0x000000FF);
        data[91] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[22]) >> 24) & 0x000000FF);
        data[92] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[23])) & 0x000000FF);
        data[93] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[23]) >> 8) & 0x000000FF);
        data[94] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[23]) >> 16) & 0x000000FF);
        data[95] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[23]) >> 24) & 0x000000FF);
        data[96] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[24])) & 0x000000FF);
        data[97] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[24]) >> 8) & 0x000000FF);
        data[98] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[24]) >> 16) & 0x000000FF);
        data[99] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[24]) >> 24) & 0x000000FF);
        data[100] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[25])) & 0x000000FF);
        data[101] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[25]) >> 8) & 0x000000FF);
        data[102] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[25]) >> 16) & 0x000000FF);
        data[103] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[25]) >> 24) & 0x000000FF);
        data[104] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[26])) & 0x000000FF);
        data[105] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[26]) >> 8) & 0x000000FF);
        data[106] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[26]) >> 16) & 0x000000FF);
        data[107] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[26]) >> 24) & 0x000000FF);
        data[108] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[27])) & 0x000000FF);
        data[109] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[27]) >> 8) & 0x000000FF);
        data[110] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[27]) >> 16) & 0x000000FF);
        data[111] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[27]) >> 24) & 0x000000FF);
        data[112] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[28])) & 0x000000FF);
        data[113] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[28]) >> 8) & 0x000000FF);
        data[114] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[28]) >> 16) & 0x000000FF);
        data[115] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[28]) >> 24) & 0x000000FF);
        data[116] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[29])) & 0x000000FF);
        data[117] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[29]) >> 8) & 0x000000FF);
        data[118] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[29]) >> 16) & 0x000000FF);
        data[119] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[29]) >> 24) & 0x000000FF);
        data[120] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[30])) & 0x000000FF);
        data[121] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[30]) >> 8) & 0x000000FF);
        data[122] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[30]) >> 16) & 0x000000FF);
        data[123] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[30]) >> 24) & 0x000000FF);
        data[124] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[31])) & 0x000000FF);
        data[125] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[31]) >> 8) & 0x000000FF);
        data[126] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[31]) >> 16) & 0x000000FF);
        data[127] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffB[31]) >> 24) & 0x000000FF);
        data[128] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[0])) & 0x000000FF);
        data[129] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[0]) >> 8) & 0x000000FF);
        data[130] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[0]) >> 16) & 0x000000FF);
        data[131] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[0]) >> 24) & 0x000000FF);
        data[132] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[1])) & 0x000000FF);
        data[133] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[1]) >> 8) & 0x000000FF);
        data[134] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[1]) >> 16) & 0x000000FF);
        data[135] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[1]) >> 24) & 0x000000FF);
        data[136] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[2])) & 0x000000FF);
        data[137] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[2]) >> 8) & 0x000000FF);
        data[138] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[2]) >> 16) & 0x000000FF);
        data[139] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[2]) >> 24) & 0x000000FF);
        data[140] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[3])) & 0x000000FF);
        data[141] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[3]) >> 8) & 0x000000FF);
        data[142] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[3]) >> 16) & 0x000000FF);
        data[143] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[3]) >> 24) & 0x000000FF);
        data[144] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[4])) & 0x000000FF);
        data[145] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[4]) >> 8) & 0x000000FF);
        data[146] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[4]) >> 16) & 0x000000FF);
        data[147] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[4]) >> 24) & 0x000000FF);
        data[148] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[5])) & 0x000000FF);
        data[149] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[5]) >> 8) & 0x000000FF);
        data[150] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[5]) >> 16) & 0x000000FF);
        data[151] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[5]) >> 24) & 0x000000FF);
        data[152] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[6])) & 0x000000FF);
        data[153] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[6]) >> 8) & 0x000000FF);
        data[154] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[6]) >> 16) & 0x000000FF);
        data[155] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[6]) >> 24) & 0x000000FF);
        data[156] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[7])) & 0x000000FF);
        data[157] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[7]) >> 8) & 0x000000FF);
        data[158] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[7]) >> 16) & 0x000000FF);
        data[159] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[7]) >> 24) & 0x000000FF);
        data[160] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[8])) & 0x000000FF);
        data[161] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[8]) >> 8) & 0x000000FF);
        data[162] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[8]) >> 16) & 0x000000FF);
        data[163] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[8]) >> 24) & 0x000000FF);
        data[164] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[9])) & 0x000000FF);
        data[165] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[9]) >> 8) & 0x000000FF);
        data[166] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[9]) >> 16) & 0x000000FF);
        data[167] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[9]) >> 24) & 0x000000FF);
        data[168] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[10])) & 0x000000FF);
        data[169] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[10]) >> 8) & 0x000000FF);
        data[170] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[10]) >> 16) & 0x000000FF);
        data[171] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[10]) >> 24) & 0x000000FF);
        data[172] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[11])) & 0x000000FF);
        data[173] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[11]) >> 8) & 0x000000FF);
        data[174] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[11]) >> 16) & 0x000000FF);
        data[175] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[11]) >> 24) & 0x000000FF);
        data[176] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[12])) & 0x000000FF);
        data[177] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[12]) >> 8) & 0x000000FF);
        data[178] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[12]) >> 16) & 0x000000FF);
        data[179] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[12]) >> 24) & 0x000000FF);
        data[180] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[13])) & 0x000000FF);
        data[181] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[13]) >> 8) & 0x000000FF);
        data[182] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[13]) >> 16) & 0x000000FF);
        data[183] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[13]) >> 24) & 0x000000FF);
        data[184] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[14])) & 0x000000FF);
        data[185] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[14]) >> 8) & 0x000000FF);
        data[186] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[14]) >> 16) & 0x000000FF);
        data[187] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[14]) >> 24) & 0x000000FF);
        data[188] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[15])) & 0x000000FF);
        data[189] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[15]) >> 8) & 0x000000FF);
        data[190] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[15]) >> 16) & 0x000000FF);
        data[191] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[15]) >> 24) & 0x000000FF);
        data[192] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[16])) & 0x000000FF);
        data[193] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[16]) >> 8) & 0x000000FF);
        data[194] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[16]) >> 16) & 0x000000FF);
        data[195] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[16]) >> 24) & 0x000000FF);
        data[196] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[17])) & 0x000000FF);
        data[197] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[17]) >> 8) & 0x000000FF);
        data[198] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[17]) >> 16) & 0x000000FF);
        data[199] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[17]) >> 24) & 0x000000FF);
        data[200] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[18])) & 0x000000FF);
        data[201] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[18]) >> 8) & 0x000000FF);
        data[202] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[18]) >> 16) & 0x000000FF);
        data[203] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[18]) >> 24) & 0x000000FF);
        data[204] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[19])) & 0x000000FF);
        data[205] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[19]) >> 8) & 0x000000FF);
        data[206] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[19]) >> 16) & 0x000000FF);
        data[207] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[19]) >> 24) & 0x000000FF);
        data[208] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[20])) & 0x000000FF);
        data[209] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[20]) >> 8) & 0x000000FF);
        data[210] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[20]) >> 16) & 0x000000FF);
        data[211] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[20]) >> 24) & 0x000000FF);
        data[212] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[21])) & 0x000000FF);
        data[213] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[21]) >> 8) & 0x000000FF);
        data[214] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[21]) >> 16) & 0x000000FF);
        data[215] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[21]) >> 24) & 0x000000FF);
        data[216] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[22])) & 0x000000FF);
        data[217] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[22]) >> 8) & 0x000000FF);
        data[218] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[22]) >> 16) & 0x000000FF);
        data[219] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[22]) >> 24) & 0x000000FF);
        data[220] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[23])) & 0x000000FF);
        data[221] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[23]) >> 8) & 0x000000FF);
        data[222] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[23]) >> 16) & 0x000000FF);
        data[223] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[23]) >> 24) & 0x000000FF);
        data[224] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[24])) & 0x000000FF);
        data[225] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[24]) >> 8) & 0x000000FF);
        data[226] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[24]) >> 16) & 0x000000FF);
        data[227] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[24]) >> 24) & 0x000000FF);
        data[228] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[25])) & 0x000000FF);
        data[229] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[25]) >> 8) & 0x000000FF);
        data[230] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[25]) >> 16) & 0x000000FF);
        data[231] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[25]) >> 24) & 0x000000FF);
        data[232] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[26])) & 0x000000FF);
        data[233] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[26]) >> 8) & 0x000000FF);
        data[234] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[26]) >> 16) & 0x000000FF);
        data[235] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[26]) >> 24) & 0x000000FF);
        data[236] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[27])) & 0x000000FF);
        data[237] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[27]) >> 8) & 0x000000FF);
        data[238] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[27]) >> 16) & 0x000000FF);
        data[239] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[27]) >> 24) & 0x000000FF);
        data[240] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[28])) & 0x000000FF);
        data[241] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[28]) >> 8) & 0x000000FF);
        data[242] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[28]) >> 16) & 0x000000FF);
        data[243] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[28]) >> 24) & 0x000000FF);
        data[244] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[29])) & 0x000000FF);
        data[245] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[29]) >> 8) & 0x000000FF);
        data[246] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[29]) >> 16) & 0x000000FF);
        data[247] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[29]) >> 24) & 0x000000FF);
        data[248] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[30])) & 0x000000FF);
        data[249] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[30]) >> 8) & 0x000000FF);
        data[250] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[30]) >> 16) & 0x000000FF);
        data[251] = (uint8)((*(uint32*)&(pTIIR_Float32->coeffA[30]) >> 24) & 0x000000FF);
        data[252] = (uint8)pTIIR_Float32->orderN;
        data[253] = (uint8)pTIIR_Float32->orderD;
        *dataLength = (uint16)254;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 IIR_Float32_Save(IIR_FLOAT32 *pTIIR_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)254)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTIIR_Float32->coeffB[0] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTIIR_Float32->coeffB[1] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTIIR_Float32->coeffB[2] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTIIR_Float32->coeffB[3] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24);
        pTIIR_Float32->coeffB[4] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[20] + \
            ((uint32)data[21] << 8) + ((uint32)data[22] << 16) + \
            ((uint32)data[23] << 24);
        pTIIR_Float32->coeffB[5] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[24] + \
            ((uint32)data[25] << 8) + ((uint32)data[26] << 16) + \
            ((uint32)data[27] << 24);
        pTIIR_Float32->coeffB[6] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[28] + \
            ((uint32)data[29] << 8) + ((uint32)data[30] << 16) + \
            ((uint32)data[31] << 24);
        pTIIR_Float32->coeffB[7] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[32] + \
            ((uint32)data[33] << 8) + ((uint32)data[34] << 16) + \
            ((uint32)data[35] << 24);
        pTIIR_Float32->coeffB[8] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[36] + \
            ((uint32)data[37] << 8) + ((uint32)data[38] << 16) + \
            ((uint32)data[39] << 24);
        pTIIR_Float32->coeffB[9] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[40] + \
            ((uint32)data[41] << 8) + ((uint32)data[42] << 16) + \
            ((uint32)data[43] << 24);
        pTIIR_Float32->coeffB[10] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[44] + \
            ((uint32)data[45] << 8) + ((uint32)data[46] << 16) + \
            ((uint32)data[47] << 24);
        pTIIR_Float32->coeffB[11] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[48] + \
            ((uint32)data[49] << 8) + ((uint32)data[50] << 16) + \
            ((uint32)data[51] << 24);
        pTIIR_Float32->coeffB[12] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[52] + \
            ((uint32)data[53] << 8) + ((uint32)data[54] << 16) + \
            ((uint32)data[55] << 24);
        pTIIR_Float32->coeffB[13] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[56] + \
            ((uint32)data[57] << 8) + ((uint32)data[58] << 16) + \
            ((uint32)data[59] << 24);
        pTIIR_Float32->coeffB[14] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[60] + \
            ((uint32)data[61] << 8) + ((uint32)data[62] << 16) + \
            ((uint32)data[63] << 24);
        pTIIR_Float32->coeffB[15] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[64] + \
            ((uint32)data[65] << 8) + ((uint32)data[66] << 16) + \
            ((uint32)data[67] << 24);
        pTIIR_Float32->coeffB[16] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[68] + \
            ((uint32)data[69] << 8) + ((uint32)data[70] << 16) + \
            ((uint32)data[71] << 24);
        pTIIR_Float32->coeffB[17] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[72] + \
            ((uint32)data[73] << 8) + ((uint32)data[74] << 16) + \
            ((uint32)data[75] << 24);
        pTIIR_Float32->coeffB[18] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[76] + \
            ((uint32)data[77] << 8) + ((uint32)data[78] << 16) + \
            ((uint32)data[79] << 24);
        pTIIR_Float32->coeffB[19] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[80] + \
            ((uint32)data[81] << 8) + ((uint32)data[82] << 16) + \
            ((uint32)data[83] << 24);
        pTIIR_Float32->coeffB[20] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[84] + \
            ((uint32)data[85] << 8) + ((uint32)data[86] << 16) + \
            ((uint32)data[87] << 24);
        pTIIR_Float32->coeffB[21] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[88] + \
            ((uint32)data[89] << 8) + ((uint32)data[90] << 16) + \
            ((uint32)data[91] << 24);
        pTIIR_Float32->coeffB[22] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[92] + \
            ((uint32)data[93] << 8) + ((uint32)data[94] << 16) + \
            ((uint32)data[95] << 24);
        pTIIR_Float32->coeffB[23] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[96] + \
            ((uint32)data[97] << 8) + ((uint32)data[98] << 16) + \
            ((uint32)data[99] << 24);
        pTIIR_Float32->coeffB[24] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[100] + \
            ((uint32)data[101] << 8) + ((uint32)data[102] << 16) + \
            ((uint32)data[103] << 24);
        pTIIR_Float32->coeffB[25] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[104] + \
            ((uint32)data[105] << 8) + ((uint32)data[106] << 16) + \
            ((uint32)data[107] << 24);
        pTIIR_Float32->coeffB[26] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[108] + \
            ((uint32)data[109] << 8) + ((uint32)data[110] << 16) + \
            ((uint32)data[111] << 24);
        pTIIR_Float32->coeffB[27] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[112] + \
            ((uint32)data[113] << 8) + ((uint32)data[114] << 16) + \
            ((uint32)data[115] << 24);
        pTIIR_Float32->coeffB[28] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[116] + \
            ((uint32)data[117] << 8) + ((uint32)data[118] << 16) + \
            ((uint32)data[119] << 24);
        pTIIR_Float32->coeffB[29] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[120] + \
            ((uint32)data[121] << 8) + ((uint32)data[122] << 16) + \
            ((uint32)data[123] << 24);
        pTIIR_Float32->coeffB[30] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[124] + \
            ((uint32)data[125] << 8) + ((uint32)data[126] << 16) + \
            ((uint32)data[127] << 24);
        pTIIR_Float32->coeffB[31] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[128] + \
            ((uint32)data[129] << 8) + ((uint32)data[130] << 16) + \
            ((uint32)data[131] << 24);
        pTIIR_Float32->coeffA[0] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[132] + \
            ((uint32)data[133] << 8) + ((uint32)data[134] << 16) + \
            ((uint32)data[135] << 24);
        pTIIR_Float32->coeffA[1] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[136] + \
            ((uint32)data[137] << 8) + ((uint32)data[138] << 16) + \
            ((uint32)data[139] << 24);
        pTIIR_Float32->coeffA[2] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[140] + \
            ((uint32)data[141] << 8) + ((uint32)data[142] << 16) + \
            ((uint32)data[143] << 24);
        pTIIR_Float32->coeffA[3] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[144] + \
            ((uint32)data[145] << 8) + ((uint32)data[146] << 16) + \
            ((uint32)data[147] << 24);
        pTIIR_Float32->coeffA[4] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[148] + \
            ((uint32)data[149] << 8) + ((uint32)data[150] << 16) + \
            ((uint32)data[151] << 24);
        pTIIR_Float32->coeffA[5] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[152] + \
            ((uint32)data[153] << 8) + ((uint32)data[154] << 16) + \
            ((uint32)data[155] << 24);
        pTIIR_Float32->coeffA[6] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[156] + \
            ((uint32)data[157] << 8) + ((uint32)data[158] << 16) + \
            ((uint32)data[159] << 24);
        pTIIR_Float32->coeffA[7] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[160] + \
            ((uint32)data[161] << 8) + ((uint32)data[162] << 16) + \
            ((uint32)data[163] << 24);
        pTIIR_Float32->coeffA[8] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[164] + \
            ((uint32)data[165] << 8) + ((uint32)data[166] << 16) + \
            ((uint32)data[167] << 24);
        pTIIR_Float32->coeffA[9] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[168] + \
            ((uint32)data[169] << 8) + ((uint32)data[170] << 16) + \
            ((uint32)data[171] << 24);
        pTIIR_Float32->coeffA[10] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[172] + \
            ((uint32)data[173] << 8) + ((uint32)data[174] << 16) + \
            ((uint32)data[175] << 24);
        pTIIR_Float32->coeffA[11] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[176] + \
            ((uint32)data[177] << 8) + ((uint32)data[178] << 16) + \
            ((uint32)data[179] << 24);
        pTIIR_Float32->coeffA[12] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[180] + \
            ((uint32)data[181] << 8) + ((uint32)data[182] << 16) + \
            ((uint32)data[183] << 24);
        pTIIR_Float32->coeffA[13] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[184] + \
            ((uint32)data[185] << 8) + ((uint32)data[186] << 16) + \
            ((uint32)data[187] << 24);
        pTIIR_Float32->coeffA[14] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[188] + \
            ((uint32)data[189] << 8) + ((uint32)data[190] << 16) + \
            ((uint32)data[191] << 24);
        pTIIR_Float32->coeffA[15] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[192] + \
            ((uint32)data[193] << 8) + ((uint32)data[194] << 16) + \
            ((uint32)data[195] << 24);
        pTIIR_Float32->coeffA[16] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[196] + \
            ((uint32)data[197] << 8) + ((uint32)data[198] << 16) + \
            ((uint32)data[199] << 24);
        pTIIR_Float32->coeffA[17] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[200] + \
            ((uint32)data[201] << 8) + ((uint32)data[202] << 16) + \
            ((uint32)data[203] << 24);
        pTIIR_Float32->coeffA[18] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[204] + \
            ((uint32)data[205] << 8) + ((uint32)data[206] << 16) + \
            ((uint32)data[207] << 24);
        pTIIR_Float32->coeffA[19] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[208] + \
            ((uint32)data[209] << 8) + ((uint32)data[210] << 16) + \
            ((uint32)data[211] << 24);
        pTIIR_Float32->coeffA[20] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[212] + \
            ((uint32)data[213] << 8) + ((uint32)data[214] << 16) + \
            ((uint32)data[215] << 24);
        pTIIR_Float32->coeffA[21] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[216] + \
            ((uint32)data[217] << 8) + ((uint32)data[218] << 16) + \
            ((uint32)data[219] << 24);
        pTIIR_Float32->coeffA[22] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[220] + \
            ((uint32)data[221] << 8) + ((uint32)data[222] << 16) + \
            ((uint32)data[223] << 24);
        pTIIR_Float32->coeffA[23] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[224] + \
            ((uint32)data[225] << 8) + ((uint32)data[226] << 16) + \
            ((uint32)data[227] << 24);
        pTIIR_Float32->coeffA[24] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[228] + \
            ((uint32)data[229] << 8) + ((uint32)data[230] << 16) + \
            ((uint32)data[231] << 24);
        pTIIR_Float32->coeffA[25] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[232] + \
            ((uint32)data[233] << 8) + ((uint32)data[234] << 16) + \
            ((uint32)data[235] << 24);
        pTIIR_Float32->coeffA[26] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[236] + \
            ((uint32)data[237] << 8) + ((uint32)data[238] << 16) + \
            ((uint32)data[239] << 24);
        pTIIR_Float32->coeffA[27] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[240] + \
            ((uint32)data[241] << 8) + ((uint32)data[242] << 16) + \
            ((uint32)data[243] << 24);
        pTIIR_Float32->coeffA[28] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[244] + \
            ((uint32)data[245] << 8) + ((uint32)data[246] << 16) + \
            ((uint32)data[247] << 24);
        pTIIR_Float32->coeffA[29] = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[248] + \
            ((uint32)data[249] << 8) + ((uint32)data[250] << 16) + \
            ((uint32)data[251] << 24);
        pTIIR_Float32->coeffA[30] = (float32)(*(float32*)&tmp32);
        pTIIR_Float32->orderN = UINT8_TO_INT8((uint8)data[252]);
        pTIIR_Float32->orderD = UINT8_TO_INT8((uint8)data[253]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(IIR_FLOAT32_ISLINKED)
void* IIR_Float32_GetAddress(const IIR_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
