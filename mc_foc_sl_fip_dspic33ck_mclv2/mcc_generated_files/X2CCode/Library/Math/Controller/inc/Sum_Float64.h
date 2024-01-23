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
 * $LastChangedRevision: 2584 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Sum of all inputs.                                   										 **/
/**																													 **/
/**						Sign bit field:																				 **/
/**							00->0 ... Input will be ignored.														 **/
/**							01->+ ... Input will be added to result.												 **/
/**							10->- ... Input will be subtracted from result.	 										 **/
/**																			 										 **/
/* USERCODE-END:Description                                                                                           */
#ifndef SUM_FLOAT64_H
#define SUM_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SUM_FLOAT64_ISLINKED)
#define SUM_FLOAT64_ID ((uint16)4804)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In1;
    float64         *In2;
    float64         *In3;
    float64         *In4;
    float64         *In5;
    float64         *In6;
    float64         *In7;
    float64         *In8;
    float64         Out;
    uint16          sign;
} SUM_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In1;
    FLOAT64_PTR     In2;
    FLOAT64_PTR     In3;
    FLOAT64_PTR     In4;
    FLOAT64_PTR     In5;
    FLOAT64_PTR     In6;
    FLOAT64_PTR     In7;
    FLOAT64_PTR     In8;
    float64         Out;
    uint16          sign;
} SUM_FLOAT64;
#endif

#define SUM_FLOAT64_FUNCTIONS { \
    SUM_FLOAT64_ID, \
    (void (*)(void*))Sum_Float64_Update, \
    (void (*)(void*))Sum_Float64_Init, \
    (tLoadImplementationParameter)Sum_Float64_Load, \
    (tSaveImplementationParameter)Sum_Float64_Save, \
    (void* (*)(const void*, uint16))Sum_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Sum_Float64_Update(SUM_FLOAT64 *pTSum_Float64);
void Sum_Float64_Init(SUM_FLOAT64 *pTSum_Float64);
uint8 Sum_Float64_Load(const SUM_FLOAT64 *pTSum_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Sum_Float64_Save(SUM_FLOAT64 *pTSum_Float64, const uint8 data[], uint16 dataLength);
void* Sum_Float64_GetAddress(const SUM_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
