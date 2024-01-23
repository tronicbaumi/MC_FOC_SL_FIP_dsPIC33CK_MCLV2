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
 * $LastChangedRevision: 1603 $
 */
// USERCODE-BEGIN:Description                                                                                           
//*     Description:                                                           *
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.general;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
import at.lcm.x2c.utils.QFormat;
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_Saturation_FiP16 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: max                                                                                          
        MaskDouble maxMaskVal = 
            (MaskDouble)this.getMaskParameter("max").getMaskDataType();
        TNumeric maxMaskData = 
            (TNumeric)maxMaskVal.getData();
        // Mask Parameter: min                                                                                          
        MaskDouble minMaskVal = 
            (MaskDouble)this.getMaskParameter("min").getMaskDataType();
        TNumeric minMaskData = 
            (TNumeric)minMaskVal.getData();

        // Implementation Parameter: max                                                                                
        TNumeric maxCtrVal = this.getImplementationParameterData("max");
        // Implementation Parameter: min                                                                                
        TNumeric minCtrVal = this.getImplementationParameterData("min");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
          double min, max;
          final int BITS = 16;
          
          // get controller parameter values
          max = Double.valueOf(maxMaskVal.getValue());
          min = Double.valueOf(minMaskVal.getValue());
          
          // validate input data
          if (min > max){	// limits are in false order
        	  maxCtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(min, BITS-1, BITS, true)));	// swap limits                                
              minCtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(max, BITS-1, BITS, true)));	// swap limits
          } else {			// limits are in correct order
        	  maxCtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(max, BITS-1, BITS, true)));                                
        	  minCtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(min, BITS-1, BITS, true)));
          }                                   
          
// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("max", maxCtrVal);
        this.setImplementationParameterData("min", minCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: max                                                                                          
        MaskDouble maxMaskVal = 
            (MaskDouble)this.getMaskParameter("max").getMaskDataType();
        TNumeric maxMaskData = 
            (TNumeric)maxMaskVal.getData();
        // Mask Parameter: min                                                                                          
        MaskDouble minMaskVal = 
            (MaskDouble)this.getMaskParameter("min").getMaskDataType();
        TNumeric minMaskData = 
            (TNumeric)minMaskVal.getData();

        // Implementation Parameter: max                                                                                
        TNumeric maxCtrVal = this.getImplementationParameterData("max");
        // Implementation Parameter: min                                                                                
        TNumeric minCtrVal = this.getImplementationParameterData("min");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
          double max, min;
          final int BITS = 16;
     	 
 		 // get controller parameter
          max = maxCtrVal.getReal(0, 0);
          min = minCtrVal.getReal(0, 0);
          
          // calculate mask parameter
          maxMaskData.setReal(0, 0, QFormat.getDecValue((long)max, BITS-1, BITS, true));
          minMaskData.setReal(0, 0, QFormat.getDecValue((long)min, BITS-1, BITS, true));
 
          
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("max").setValue(maxMaskData.toFullString());
        this.getMaskParameter("min").setValue(minMaskData.toFullString());
    }
}
