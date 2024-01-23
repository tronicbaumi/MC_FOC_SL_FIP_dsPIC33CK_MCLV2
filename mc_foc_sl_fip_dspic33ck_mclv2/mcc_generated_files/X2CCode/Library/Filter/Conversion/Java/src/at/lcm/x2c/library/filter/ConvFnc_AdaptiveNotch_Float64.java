/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2118 $
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
public class ConvFnc_AdaptiveNotch_Float64 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: Q                                                                                            
        MaskDouble QMaskVal = 
            (MaskDouble)this.getMaskParameter("Q").getMaskDataType();
        TNumeric QMaskData = 
            (TNumeric)QMaskVal.getData();
        // Mask Parameter: n_thresh                                                                                     
        MaskDouble n_threshMaskVal = 
            (MaskDouble)this.getMaskParameter("n_thresh").getMaskDataType();
        TNumeric n_threshMaskData = 
            (TNumeric)n_threshMaskVal.getData();
        // Mask Parameter: n_max                                                                                        
        MaskDouble n_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("n_max").getMaskDataType();
        TNumeric n_maxMaskData = 
            (TNumeric)n_maxMaskVal.getData();
        // Mask Parameter: p                                                                                            
        MaskDouble pMaskVal = 
            (MaskDouble)this.getMaskParameter("p").getMaskDataType();
        TNumeric pMaskData = 
            (TNumeric)pMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();
        // Mask Parameter: method                                                                                       
        MaskComboBox methodMaskVal = 
            (MaskComboBox)this.getMaskParameter("method").getMaskDataType();
        TString methodMaskData = 
            (TString)methodMaskVal.getData();

        // Implementation Parameter: a_fact                                                                             
        TNumeric a_factCtrVal = this.getImplementationParameterData("a_fact");
        // Implementation Parameter: b_fact                                                                             
        TNumeric b_factCtrVal = this.getImplementationParameterData("b_fact");
        // Implementation Parameter: c_fact                                                                             
        TNumeric c_factCtrVal = this.getImplementationParameterData("c_fact");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: a2                                                                                 
        TNumeric a2CtrVal = this.getImplementationParameterData("a2");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: k                                                                                  
        TNumeric kCtrVal = this.getImplementationParameterData("k");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");
        // Implementation Parameter: in_very_old                                                                        
        TNumeric in_very_oldCtrVal = this.getImplementationParameterData("in_very_old");
        // Implementation Parameter: out_old                                                                            
        TNumeric out_oldCtrVal = this.getImplementationParameterData("out_old");
        // Implementation Parameter: out_very_old                                                                       
        TNumeric out_very_oldCtrVal = this.getImplementationParameterData("out_very_old");
        // Implementation Parameter: n_old                                                                              
        TNumeric n_oldCtrVal = this.getImplementationParameterData("n_old");
        // Implementation Parameter: n_thresh                                                                           
        TNumeric n_threshCtrVal = this.getImplementationParameterData("n_thresh");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        /* get mask parameter values */
        double n_thresh = Double.valueOf(n_threshMaskVal.getValue()); /* speed threshold */
        double p = Double.valueOf(pMaskVal.getValue()); /* number of pole pairs */
        double Q = Double.valueOf(QMaskVal.getValue()); /* Q-factor */
        // double n_max = Double.valueOf(n_maxMaskVal.getValue()); /* speed scaling */

        double ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();

        /* validation */
        if (ts_fact < 1) {
            throw new Exception("Sample time factor must not be smaller than one!");
        }
        if (p < 1) {
            throw new Exception("Number of pole pairs must not be smaller than one!");
        }
        if (n_thresh <= 0) {
            throw new Exception("Speed threshold must be greater than zero!");
        }
        if (Q < 0.5) {
            throw new Exception(
                    "Q-factor must not be smaller than 0.5!"); /* to prevent complex multiplication factors */
        }

        /* calculate multiplication factors for filter coefficients */
        double Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();
        double a_fact = ((((-2 * Math.PI) / 60) * p) / 2 / Q) * Ts;
        double b_fact = ((((-2 * Math.PI) / 60) * p) / 2 / Q) * Ts * Math.sqrt((4 * Q * Q) - 1);
        double c_fact = ((2 * Math.PI) / 60) * p * Ts;

        /* set implementation parameter values */
        n_threshCtrVal.setReal(0, 0, n_thresh);
        a_factCtrVal.setReal(0, 0, a_fact);
        b_factCtrVal.setReal(0, 0, b_fact);
        c_factCtrVal.setReal(0, 0, c_fact);

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("a_fact", a_factCtrVal);
        this.setImplementationParameterData("b_fact", b_factCtrVal);
        this.setImplementationParameterData("c_fact", c_factCtrVal);
        this.setImplementationParameterData("a1", a1CtrVal);
        this.setImplementationParameterData("a2", a2CtrVal);
        this.setImplementationParameterData("b1", b1CtrVal);
        this.setImplementationParameterData("k", kCtrVal);
        this.setImplementationParameterData("in_old", in_oldCtrVal);
        this.setImplementationParameterData("in_very_old", in_very_oldCtrVal);
        this.setImplementationParameterData("out_old", out_oldCtrVal);
        this.setImplementationParameterData("out_very_old", out_very_oldCtrVal);
        this.setImplementationParameterData("n_old", n_oldCtrVal);
        this.setImplementationParameterData("n_thresh", n_threshCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: Q                                                                                            
        MaskDouble QMaskVal = 
            (MaskDouble)this.getMaskParameter("Q").getMaskDataType();
        TNumeric QMaskData = 
            (TNumeric)QMaskVal.getData();
        // Mask Parameter: n_thresh                                                                                     
        MaskDouble n_threshMaskVal = 
            (MaskDouble)this.getMaskParameter("n_thresh").getMaskDataType();
        TNumeric n_threshMaskData = 
            (TNumeric)n_threshMaskVal.getData();
        // Mask Parameter: n_max                                                                                        
        MaskDouble n_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("n_max").getMaskDataType();
        TNumeric n_maxMaskData = 
            (TNumeric)n_maxMaskVal.getData();
        // Mask Parameter: p                                                                                            
        MaskDouble pMaskVal = 
            (MaskDouble)this.getMaskParameter("p").getMaskDataType();
        TNumeric pMaskData = 
            (TNumeric)pMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();
        // Mask Parameter: method                                                                                       
        MaskComboBox methodMaskVal = 
            (MaskComboBox)this.getMaskParameter("method").getMaskDataType();
        TString methodMaskData = 
            (TString)methodMaskVal.getData();

        // Implementation Parameter: a_fact                                                                             
        TNumeric a_factCtrVal = this.getImplementationParameterData("a_fact");
        // Implementation Parameter: b_fact                                                                             
        TNumeric b_factCtrVal = this.getImplementationParameterData("b_fact");
        // Implementation Parameter: c_fact                                                                             
        TNumeric c_factCtrVal = this.getImplementationParameterData("c_fact");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: a2                                                                                 
        TNumeric a2CtrVal = this.getImplementationParameterData("a2");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: k                                                                                  
        TNumeric kCtrVal = this.getImplementationParameterData("k");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");
        // Implementation Parameter: in_very_old                                                                        
        TNumeric in_very_oldCtrVal = this.getImplementationParameterData("in_very_old");
        // Implementation Parameter: out_old                                                                            
        TNumeric out_oldCtrVal = this.getImplementationParameterData("out_old");
        // Implementation Parameter: out_very_old                                                                       
        TNumeric out_very_oldCtrVal = this.getImplementationParameterData("out_very_old");
        // Implementation Parameter: n_old                                                                              
        TNumeric n_oldCtrVal = this.getImplementationParameterData("n_old");
        // Implementation Parameter: n_thresh                                                                           
        TNumeric n_threshCtrVal = this.getImplementationParameterData("n_thresh");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        if (true) {
            throw new Exception(
                    "Implementation-to-Mask conversion not implemented for Block 'AdaptiveNotch', Implementation 'Float64' in Library 'Filter'");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("Q").setValue(QMaskData.toFullString());
        this.getMaskParameter("n_thresh").setValue(n_threshMaskData.toFullString());
        this.getMaskParameter("n_max").setValue(n_maxMaskData.toFullString());
        this.getMaskParameter("p").setValue(pMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
        this.getMaskParameter("method").setValue(methodMaskData.getString());
    }
}
