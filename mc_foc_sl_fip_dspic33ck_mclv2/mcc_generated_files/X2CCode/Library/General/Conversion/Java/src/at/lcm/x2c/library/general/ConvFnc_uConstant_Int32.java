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
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.general;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_uConstant_Int32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: Value                                                                                        
        MaskDouble ValueMaskVal = 
            (MaskDouble)this.getMaskParameter("Value").getMaskDataType();
        TNumeric ValueMaskData = 
            (TNumeric)ValueMaskVal.getData();

        // Implementation Parameter: K                                                                                  
        TNumeric KCtrVal = this.getImplementationParameterData("K");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        double K;
        final int BITS = 32;
        final double INTMAX = Math.pow(2, BITS - 1) - 1;

        // get mask parameter value
        K = Math.round(Math.abs(Double.valueOf(ValueMaskVal.getValue())));
        // adjust Java's asymmetrical round() to be compliant with with C's symmetrical round()
        if (Double.valueOf(ValueMaskVal.getValue()) < 0) {
            K = -K;
        }

        // range check
        // NOTE: X2C does not allow the conversion of asymmetrical, signed integers. To prevent errors range check is symmetrical
        if (K > INTMAX) {
            K = INTMAX;
        } else if (K < -INTMAX) {
            K = -INTMAX;
        }

        // set controller parameter
        KCtrVal.setReal(0, 0, K);

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("K", KCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: Value                                                                                        
        MaskDouble ValueMaskVal = 
            (MaskDouble)this.getMaskParameter("Value").getMaskDataType();
        TNumeric ValueMaskData = 
            (TNumeric)ValueMaskVal.getData();

        // Implementation Parameter: K                                                                                  
        TNumeric KCtrVal = this.getImplementationParameterData("K");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        double K;

        // get controller parameter
        K = KCtrVal.getReal(0, 0);

        // set mask parameter
        ValueMaskData.setReal(0, 0, K);

// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("Value").setValue(ValueMaskData.toFullString());
    }
}
