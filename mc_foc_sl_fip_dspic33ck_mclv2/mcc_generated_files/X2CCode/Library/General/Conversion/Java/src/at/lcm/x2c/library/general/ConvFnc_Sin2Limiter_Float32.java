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
 * $LastChangedRevision: 1894 $
 * $LastChangedDate:: 2020-04-28 23:26:04 +0200#$
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
public class ConvFnc_Sin2Limiter_Float32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: Tr                                                                                           
        MaskDouble TrMaskVal = 
            (MaskDouble)this.getMaskParameter("Tr").getMaskDataType();
        TNumeric TrMaskData = 
            (TNumeric)TrMaskVal.getData();
        // Mask Parameter: Tf                                                                                           
        MaskDouble TfMaskVal = 
            (MaskDouble)this.getMaskParameter("Tf").getMaskDataType();
        TNumeric TfMaskData = 
            (TNumeric)TfMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: RateUp                                                                             
        TNumeric RateUpCtrVal = this.getImplementationParameterData("RateUp");
        // Implementation Parameter: RateDown                                                                           
        TNumeric RateDownCtrVal = this.getImplementationParameterData("RateDown");
        // Implementation Parameter: Scaled_RateUp                                                                      
        TNumeric Scaled_RateUpCtrVal = this.getImplementationParameterData("Scaled_RateUp");
        // Implementation Parameter: Scaled_RateDown                                                                    
        TNumeric Scaled_RateDownCtrVal = this.getImplementationParameterData("Scaled_RateDown");
        // Implementation Parameter: Out_end                                                                            
        TNumeric Out_endCtrVal = this.getImplementationParameterData("Out_end");
        // Implementation Parameter: Level                                                                              
        TNumeric LevelCtrVal = this.getImplementationParameterData("Level");
        // Implementation Parameter: Step_Height                                                                        
        TNumeric Step_HeightCtrVal = this.getImplementationParameterData("Step_Height");
        // Implementation Parameter: State                                                                              
        TNumeric StateCtrVal = this.getImplementationParameterData("State");
        // Implementation Parameter: Enable_old                                                                         
        TNumeric Enable_oldCtrVal = this.getImplementationParameterData("Enable_old");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
		double Tr, Tf;
		double Ts = 0;
		int ts_fact;

		// get parameter values
		Tr = Double.valueOf(TrMaskVal.getValue());
		Tf = Double.valueOf(TfMaskVal.getValue());
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();

		// validate controller parameters
		if (ts_fact <= 0) {
			ts_fact = 1;
		}

		// calculate sample time
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// check range of rising/falling time
		if (Tr < Ts) {
			Tr = Ts;
		}
		if (Tf < Ts) {
			Tf = Ts;
		}

		// calculate Q-values
		RateUpCtrVal.setReal(0, 0, ((Ts / Tr) * Math.PI) / 2); // pi/2 due to sin^2(0) ... sin^2(pi/2)
		RateDownCtrVal.setReal(0, 0, ((Ts / Tf) * Math.PI) / 2); // pi/2 due to sin^2(0) ... sin^2(pi/2)

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("RateUp", RateUpCtrVal);
        this.setImplementationParameterData("RateDown", RateDownCtrVal);
        this.setImplementationParameterData("Scaled_RateUp", Scaled_RateUpCtrVal);
        this.setImplementationParameterData("Scaled_RateDown", Scaled_RateDownCtrVal);
        this.setImplementationParameterData("Out_end", Out_endCtrVal);
        this.setImplementationParameterData("Level", LevelCtrVal);
        this.setImplementationParameterData("Step_Height", Step_HeightCtrVal);
        this.setImplementationParameterData("State", StateCtrVal);
        this.setImplementationParameterData("Enable_old", Enable_oldCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: Tr                                                                                           
        MaskDouble TrMaskVal = 
            (MaskDouble)this.getMaskParameter("Tr").getMaskDataType();
        TNumeric TrMaskData = 
            (TNumeric)TrMaskVal.getData();
        // Mask Parameter: Tf                                                                                           
        MaskDouble TfMaskVal = 
            (MaskDouble)this.getMaskParameter("Tf").getMaskDataType();
        TNumeric TfMaskData = 
            (TNumeric)TfMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: RateUp                                                                             
        TNumeric RateUpCtrVal = this.getImplementationParameterData("RateUp");
        // Implementation Parameter: RateDown                                                                           
        TNumeric RateDownCtrVal = this.getImplementationParameterData("RateDown");
        // Implementation Parameter: Scaled_RateUp                                                                      
        TNumeric Scaled_RateUpCtrVal = this.getImplementationParameterData("Scaled_RateUp");
        // Implementation Parameter: Scaled_RateDown                                                                    
        TNumeric Scaled_RateDownCtrVal = this.getImplementationParameterData("Scaled_RateDown");
        // Implementation Parameter: Out_end                                                                            
        TNumeric Out_endCtrVal = this.getImplementationParameterData("Out_end");
        // Implementation Parameter: Level                                                                              
        TNumeric LevelCtrVal = this.getImplementationParameterData("Level");
        // Implementation Parameter: Step_Height                                                                        
        TNumeric Step_HeightCtrVal = this.getImplementationParameterData("Step_Height");
        // Implementation Parameter: State                                                                              
        TNumeric StateCtrVal = this.getImplementationParameterData("State");
        // Implementation Parameter: Enable_old                                                                         
        TNumeric Enable_oldCtrVal = this.getImplementationParameterData("Enable_old");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
		double Ts = 0;
		int ts_fact;
		double RateUp, RateDown;

		// get controller parameter
		RateUp = RateUpCtrVal.getReal(0, 0);
		RateDown = RateDownCtrVal.getReal(0, 0);

		// get sample time information from model (sample time information can't be obtained from target)
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// set mask parameter
		TrMaskData.setReal(0, 0, (Ts / RateUp / Math.PI) * 2);
		TfMaskData.setReal(0, 0, (Ts / RateDown / Math.PI) * 2);

// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("Tr").setValue(TrMaskData.toFullString());
        this.getMaskParameter("Tf").setValue(TfMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
