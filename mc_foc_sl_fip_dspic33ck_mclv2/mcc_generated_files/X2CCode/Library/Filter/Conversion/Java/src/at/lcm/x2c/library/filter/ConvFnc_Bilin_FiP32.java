/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.filter;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
import at.lcm.x2c.utils.QFormat;
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_Bilin_FiP32 extends JavaConversionFunction {
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
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: b0                                                                                 
        TNumeric b0CtrVal = this.getImplementationParameterData("b0");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: sfrb0                                                                              
        TNumeric sfrb0CtrVal = this.getImplementationParameterData("sfrb0");
        // Implementation Parameter: sfrb1                                                                              
        TNumeric sfrb1CtrVal = this.getImplementationParameterData("sfrb1");
        // Implementation Parameter: sfra1                                                                              
        TNumeric sfra1CtrVal = this.getImplementationParameterData("sfra1");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        double b0, b1, a0, a1;
        int sfrb0, sfrb1, sfra1;
        final int BITS = 32;

        /* get coefficient a0 for normalization purposes */
        a0 = Double.valueOf(a0MaskVal.getValue());
        if (a0 == 0) {
            throw new Exception("Coefficient a0 must not be zero!");
        }

        /* get mask parameter values and normalize them */
        b0 = Double.valueOf(b0MaskVal.getValue()) / a0;
        b1 = Double.valueOf(b1MaskVal.getValue()) / a0;
        a1 = Double.valueOf(a1MaskVal.getValue()) / a0;

        /* calculate shift factor */
        sfrb0 = QFormat.getQFormat(b0, BITS, true);
        sfrb1 = QFormat.getQFormat(b1, BITS, true);
        sfra1 = QFormat.getQFormat(a1, BITS, true);

        /* set shift factors and Q values */
        sfrb0CtrVal.setReal(0, 0, sfrb0);
        sfrb1CtrVal.setReal(0, 0, sfrb1);
        sfra1CtrVal.setReal(0, 0, sfra1);
        b0CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b0, (int) (sfrb0CtrVal.getReal(0, 0)), BITS, true)));
        b1CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b1, (int) (sfrb1CtrVal.getReal(0, 0)), BITS, true)));
        a1CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(a1, (int) (sfra1CtrVal.getReal(0, 0)), BITS, true)));
// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("b0", b0CtrVal);
        this.setImplementationParameterData("b1", b1CtrVal);
        this.setImplementationParameterData("a1", a1CtrVal);
        this.setImplementationParameterData("sfrb0", sfrb0CtrVal);
        this.setImplementationParameterData("sfrb1", sfrb1CtrVal);
        this.setImplementationParameterData("sfra1", sfra1CtrVal);
        this.setImplementationParameterData("in_old", in_oldCtrVal);
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
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: b0                                                                                 
        TNumeric b0CtrVal = this.getImplementationParameterData("b0");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: sfrb0                                                                              
        TNumeric sfrb0CtrVal = this.getImplementationParameterData("sfrb0");
        // Implementation Parameter: sfrb1                                                                              
        TNumeric sfrb1CtrVal = this.getImplementationParameterData("sfrb1");
        // Implementation Parameter: sfra1                                                                              
        TNumeric sfra1CtrVal = this.getImplementationParameterData("sfra1");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        double b0, b1, a1, sfrb0, sfrb1, sfra1;
        final int BITS = 32;

        /* get implementation parameter */
        b0 = b0CtrVal.getReal(0, 0);
        b1 = b1CtrVal.getReal(0, 0);
        a1 = a1CtrVal.getReal(0, 0);
        sfrb0 = sfrb0CtrVal.getReal(0, 0);
        sfrb1 = sfrb1CtrVal.getReal(0, 0);
        sfra1 = sfra1CtrVal.getReal(0, 0);

        /* calculate coefficients */
        b0 = QFormat.getDecValue((long) b0, (int) sfrb0, BITS, true);
        b1 = QFormat.getDecValue((long) b1, (int) sfrb1, BITS, true);
        a1 = QFormat.getDecValue((long) a1, (int) sfra1, BITS, true);

        /* set mask parameter */
        /*
         * NOTE: coefficient a0 can not be calculated from implementation parameter -> a coefficient with value of 1 is
         * assumed
         */
        b0MaskData.setReal(0, 0, b0);
        b1MaskData.setReal(0, 0, b1);
        a0MaskData.setReal(0, 0, 1);
        a1MaskData.setReal(0, 0, a1);
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("b0").setValue(b0MaskData.toFullString());
        this.getMaskParameter("b1").setValue(b1MaskData.toFullString());
        this.getMaskParameter("a0").setValue(a0MaskData.toFullString());
        this.getMaskParameter("a1").setValue(a1MaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
