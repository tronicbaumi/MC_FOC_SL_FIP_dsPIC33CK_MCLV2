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
import at.lcm.x2c.utils.QFormat;
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_IIR_FiP32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: CoeffB                                                                                       
        MaskDouble CoeffBMaskVal = 
            (MaskDouble)this.getMaskParameter("CoeffB").getMaskDataType();
        TNumeric CoeffBMaskData = 
            (TNumeric)CoeffBMaskVal.getData();
        // Mask Parameter: CoeffA                                                                                       
        MaskDouble CoeffAMaskVal = 
            (MaskDouble)this.getMaskParameter("CoeffA").getMaskDataType();
        TNumeric CoeffAMaskData = 
            (TNumeric)CoeffAMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: coeffB                                                                             
        TNumeric coeffBCtrVal = this.getImplementationParameterData("coeffB");
        // Implementation Parameter: coeffA                                                                             
        TNumeric coeffACtrVal = this.getImplementationParameterData("coeffA");
        // Implementation Parameter: sfrB                                                                               
        TNumeric sfrBCtrVal = this.getImplementationParameterData("sfrB");
        // Implementation Parameter: sfrA                                                                               
        TNumeric sfrACtrVal = this.getImplementationParameterData("sfrA");
        // Implementation Parameter: inputBuffer                                                                        
        TNumeric inputBufferCtrVal = this.getImplementationParameterData("inputBuffer");
        // Implementation Parameter: outputBuffer                                                                       
        TNumeric outputBufferCtrVal = this.getImplementationParameterData("outputBuffer");
        // Implementation Parameter: indexIn                                                                            
        TNumeric indexInCtrVal = this.getImplementationParameterData("indexIn");
        // Implementation Parameter: indexOut                                                                           
        TNumeric indexOutCtrVal = this.getImplementationParameterData("indexOut");
        // Implementation Parameter: orderN                                                                             
        TNumeric orderNCtrVal = this.getImplementationParameterData("orderN");
        // Implementation Parameter: orderD                                                                             
        TNumeric orderDCtrVal = this.getImplementationParameterData("orderD");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        final int BITS = 32;
        final int SIZE_COL = 32; /* maximum order */
        final int SIZE_ROW = 1;


        /* get order of numerator and denominator */
        int orderN = CoeffBMaskData.getNumColumns();
        int orderD = CoeffAMaskData.getNumColumns();

        /* check numerator input for correct size */
        if ((orderN > SIZE_COL) || (CoeffBMaskData.getNumRows() != SIZE_ROW)) {
            throw new Exception("Numerator size mismatch in column: expected=(" + SIZE_ROW + ", " + SIZE_COL + ") "
                    + "got=(" + CoeffBMaskData.getNumRows() + "," + orderN + ")");
        }
        /* check denominator input for correct size */
        if ((orderD > SIZE_COL) || (CoeffAMaskData.getNumRows() != SIZE_ROW)) {
            throw new Exception("Numerator size mismatch in column: expected=(" + SIZE_ROW + ", " + SIZE_COL + ") "
                    + "got=(" + CoeffAMaskData.getNumRows() + "," + orderD + ")");
        }
        /* check relation of order number between numerator and denominator */
        if (orderN > orderD) {
            throw new Exception("Order of numerator must not be higher than order of denominator!");
        }

        /* get coefficient a0 for normalization purposes */
        double a0 = CoeffAMaskData.getReal(0, 0);
        if (a0 == 0) {
            throw new Exception("Coefficient a0 must not be zero!");
        }

        /* get numerator coefficients */
        Double[] coeffB = new Double[SIZE_COL];
        int sfrB = BITS - 1;
        for (int i = 0; i < orderN; i++) {
            coeffB[i] = CoeffBMaskData.getReal(0, orderN - i - 1); /* read coefficients in reversed order */
            coeffB[i] = coeffB[i] / a0; /* normalization */
            /* search for minimum shift factor */
            int sfr = QFormat.getQFormat(coeffB[i], BITS, true);
            if (sfr < sfrB) {
                sfrB = sfr;
            }
        }
        /* fill coefficient array with controller parameter */
        for (int i = 0; i < orderN; i++) {
            coeffB[i] = (double) QFormat.getQValue(coeffB[i], sfrB, BITS, true);
        }
        for (int i = orderN; i < SIZE_COL; i++) {
            coeffB[i] = 0.0;
        }

        /* get denominator coefficients */
        Double[] coeffA = new Double[SIZE_COL - 1];
        int sfrA = BITS - 1;
        for (int i = 0; i < (orderD - 1); i++) {
            coeffA[i] = CoeffAMaskData.getReal(0, orderD - i - 1); /* read coefficients in reversed order and omit a0 */
            coeffA[i] = coeffA[i] / a0; /* normalization */
            /* search for minimum shift factor */
            int sfr = QFormat.getQFormat(coeffA[i], BITS, true);
            if (sfr < sfrA) {
                sfrA = sfr;
            }
        }
        /* fill coefficient array with controller parameter */
        for (int i = 0; i < (orderD - 1); i++) {
            coeffA[i] = (double) QFormat.getQValue(coeffA[i], sfrA, BITS, true);
        }
        for (int i = orderD - 1; i < (SIZE_COL - 1); i++) {
            coeffA[i] = 0.0;
        }

        /* set implementation parameter values */
        sfrBCtrVal.setReal(0, 0, sfrB);
        sfrACtrVal.setReal(0, 0, sfrA);
        coeffBCtrVal = new TNumeric(coeffB);
        coeffACtrVal = new TNumeric(coeffA);
        orderNCtrVal.setReal(0, 0, orderN);
        orderDCtrVal.setReal(0, 0,
                orderD - 1); /* due to normalization a0 is always 1 and hence doesn't have to be transfered */

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("coeffB", coeffBCtrVal);
        this.setImplementationParameterData("coeffA", coeffACtrVal);
        this.setImplementationParameterData("sfrB", sfrBCtrVal);
        this.setImplementationParameterData("sfrA", sfrACtrVal);
        this.setImplementationParameterData("inputBuffer", inputBufferCtrVal);
        this.setImplementationParameterData("outputBuffer", outputBufferCtrVal);
        this.setImplementationParameterData("indexIn", indexInCtrVal);
        this.setImplementationParameterData("indexOut", indexOutCtrVal);
        this.setImplementationParameterData("orderN", orderNCtrVal);
        this.setImplementationParameterData("orderD", orderDCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: CoeffB                                                                                       
        MaskDouble CoeffBMaskVal = 
            (MaskDouble)this.getMaskParameter("CoeffB").getMaskDataType();
        TNumeric CoeffBMaskData = 
            (TNumeric)CoeffBMaskVal.getData();
        // Mask Parameter: CoeffA                                                                                       
        MaskDouble CoeffAMaskVal = 
            (MaskDouble)this.getMaskParameter("CoeffA").getMaskDataType();
        TNumeric CoeffAMaskData = 
            (TNumeric)CoeffAMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: coeffB                                                                             
        TNumeric coeffBCtrVal = this.getImplementationParameterData("coeffB");
        // Implementation Parameter: coeffA                                                                             
        TNumeric coeffACtrVal = this.getImplementationParameterData("coeffA");
        // Implementation Parameter: sfrB                                                                               
        TNumeric sfrBCtrVal = this.getImplementationParameterData("sfrB");
        // Implementation Parameter: sfrA                                                                               
        TNumeric sfrACtrVal = this.getImplementationParameterData("sfrA");
        // Implementation Parameter: inputBuffer                                                                        
        TNumeric inputBufferCtrVal = this.getImplementationParameterData("inputBuffer");
        // Implementation Parameter: outputBuffer                                                                       
        TNumeric outputBufferCtrVal = this.getImplementationParameterData("outputBuffer");
        // Implementation Parameter: indexIn                                                                            
        TNumeric indexInCtrVal = this.getImplementationParameterData("indexIn");
        // Implementation Parameter: indexOut                                                                           
        TNumeric indexOutCtrVal = this.getImplementationParameterData("indexOut");
        // Implementation Parameter: orderN                                                                             
        TNumeric orderNCtrVal = this.getImplementationParameterData("orderN");
        // Implementation Parameter: orderD                                                                             
        TNumeric orderDCtrVal = this.getImplementationParameterData("orderD");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        if (true) {
            throw new Exception(
                    "Implementation-to-Mask conversion not implemented for Block 'IIR', Implementation 'FiP32' in Library 'Filter' due to ambiguous parameters");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("CoeffB").setValue(CoeffBMaskData.toFullString());
        this.getMaskParameter("CoeffA").setValue(CoeffAMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
