/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 * $LastChangedDate:: 2022-05-03 15:06:23 +0200#$
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.filter;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_Biquad_Float32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: b0                                                                                           
        MaskDouble b0MaskVal = 
            (MaskDouble)this.getMaskParameter("b0").getMaskDataType();
        TNumeric b0MaskData = 
            (TNumeric)b0MaskVal.getData();
        // Mask Parameter: b1                                                                                           
        MaskDouble b1MaskVal = 
            (MaskDouble)this.getMaskParameter("b1").getMaskDataType();
        TNumeric b1MaskData = 
            (TNumeric)b1MaskVal.getData();
        // Mask Parameter: b2                                                                                           
        MaskDouble b2MaskVal = 
            (MaskDouble)this.getMaskParameter("b2").getMaskDataType();
        TNumeric b2MaskData = 
            (TNumeric)b2MaskVal.getData();
        // Mask Parameter: a0                                                                                           
        MaskDouble a0MaskVal = 
            (MaskDouble)this.getMaskParameter("a0").getMaskDataType();
        TNumeric a0MaskData = 
            (TNumeric)a0MaskVal.getData();
        // Mask Parameter: a1                                                                                           
        MaskDouble a1MaskVal = 
            (MaskDouble)this.getMaskParameter("a1").getMaskDataType();
        TNumeric a1MaskData = 
            (TNumeric)a1MaskVal.getData();
        // Mask Parameter: a2                                                                                           
        MaskDouble a2MaskVal = 
            (MaskDouble)this.getMaskParameter("a2").getMaskDataType();
        TNumeric a2MaskData = 
            (TNumeric)a2MaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: b0                                                                                 
        TNumeric b0CtrVal = this.getImplementationParameterData("b0");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: b2                                                                                 
        TNumeric b2CtrVal = this.getImplementationParameterData("b2");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: a2                                                                                 
        TNumeric a2CtrVal = this.getImplementationParameterData("a2");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");
        // Implementation Parameter: in_veryold                                                                         
        TNumeric in_veryoldCtrVal = this.getImplementationParameterData("in_veryold");
        // Implementation Parameter: out_old                                                                            
        TNumeric out_oldCtrVal = this.getImplementationParameterData("out_old");
        // Implementation Parameter: out_veryold                                                                        
        TNumeric out_veryoldCtrVal = this.getImplementationParameterData("out_veryold");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        double b0, b1, b2, a0, a1, a2;

        /* get coefficient a0 for normalization purposes */
        a0 = Double.valueOf(a0MaskVal.getValue());
        if (a0 == 0) {
            throw new Exception("Coefficient a0 must not be zero!");
        }

        /* get mask parameter values and normalize them */
        b0 = Double.valueOf(b0MaskVal.getValue()) / a0;
        b1 = Double.valueOf(b1MaskVal.getValue()) / a0;
        b2 = Double.valueOf(b2MaskVal.getValue()) / a0;
        a1 = Double.valueOf(a1MaskVal.getValue()) / a0;
        a2 = Double.valueOf(a2MaskVal.getValue()) / a0;

        /* set implementation parameter values */
        b0CtrVal.setReal(0, 0, b0);
        b1CtrVal.setReal(0, 0, b1);
        b2CtrVal.setReal(0, 0, b2);
        a1CtrVal.setReal(0, 0, a1);
        a2CtrVal.setReal(0, 0, a2);
// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("b0", b0CtrVal);
        this.setImplementationParameterData("b1", b1CtrVal);
        this.setImplementationParameterData("b2", b2CtrVal);
        this.setImplementationParameterData("a1", a1CtrVal);
        this.setImplementationParameterData("a2", a2CtrVal);
        this.setImplementationParameterData("in_old", in_oldCtrVal);
        this.setImplementationParameterData("in_veryold", in_veryoldCtrVal);
        this.setImplementationParameterData("out_old", out_oldCtrVal);
        this.setImplementationParameterData("out_veryold", out_veryoldCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: b0                                                                                           
        MaskDouble b0MaskVal = 
            (MaskDouble)this.getMaskParameter("b0").getMaskDataType();
        TNumeric b0MaskData = 
            (TNumeric)b0MaskVal.getData();
        // Mask Parameter: b1                                                                                           
        MaskDouble b1MaskVal = 
            (MaskDouble)this.getMaskParameter("b1").getMaskDataType();
        TNumeric b1MaskData = 
            (TNumeric)b1MaskVal.getData();
        // Mask Parameter: b2                                                                                           
        MaskDouble b2MaskVal = 
            (MaskDouble)this.getMaskParameter("b2").getMaskDataType();
        TNumeric b2MaskData = 
            (TNumeric)b2MaskVal.getData();
        // Mask Parameter: a0                                                                                           
        MaskDouble a0MaskVal = 
            (MaskDouble)this.getMaskParameter("a0").getMaskDataType();
        TNumeric a0MaskData = 
            (TNumeric)a0MaskVal.getData();
        // Mask Parameter: a1                                                                                           
        MaskDouble a1MaskVal = 
            (MaskDouble)this.getMaskParameter("a1").getMaskDataType();
        TNumeric a1MaskData = 
            (TNumeric)a1MaskVal.getData();
        // Mask Parameter: a2                                                                                           
        MaskDouble a2MaskVal = 
            (MaskDouble)this.getMaskParameter("a2").getMaskDataType();
        TNumeric a2MaskData = 
            (TNumeric)a2MaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: b0                                                                                 
        TNumeric b0CtrVal = this.getImplementationParameterData("b0");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: b2                                                                                 
        TNumeric b2CtrVal = this.getImplementationParameterData("b2");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: a2                                                                                 
        TNumeric a2CtrVal = this.getImplementationParameterData("a2");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");
        // Implementation Parameter: in_veryold                                                                         
        TNumeric in_veryoldCtrVal = this.getImplementationParameterData("in_veryold");
        // Implementation Parameter: out_old                                                                            
        TNumeric out_oldCtrVal = this.getImplementationParameterData("out_old");
        // Implementation Parameter: out_veryold                                                                        
        TNumeric out_veryoldCtrVal = this.getImplementationParameterData("out_veryold");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        double b0, b1, b2, a1, a2;

        /* get implementation parameter */
        b0 = b0CtrVal.getReal(0, 0);
        b1 = b1CtrVal.getReal(0, 0);
        b2 = b2CtrVal.getReal(0, 0);
        a1 = a1CtrVal.getReal(0, 0);
        a2 = a2CtrVal.getReal(0, 0);

        /* set mask parameter */
        /*
         * NOTE: coefficient a0 can not be calculated from implementation parameter -> a coefficient with value of 1 is
         * assumed
         */
        b0MaskData.setReal(0, 0, b0);
        b1MaskData.setReal(0, 0, b1);
        b2MaskData.setReal(0, 0, b2);
        a0MaskData.setReal(0, 0, 1);
        a1MaskData.setReal(0, 0, a1);
        a2MaskData.setReal(0, 0, a2);
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("b0").setValue(b0MaskData.toFullString());
        this.getMaskParameter("b1").setValue(b1MaskData.toFullString());
        this.getMaskParameter("b2").setValue(b2MaskData.toFullString());
        this.getMaskParameter("a0").setValue(a0MaskData.toFullString());
        this.getMaskParameter("a1").setValue(a1MaskData.toFullString());
        this.getMaskParameter("a2").setValue(a2MaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
