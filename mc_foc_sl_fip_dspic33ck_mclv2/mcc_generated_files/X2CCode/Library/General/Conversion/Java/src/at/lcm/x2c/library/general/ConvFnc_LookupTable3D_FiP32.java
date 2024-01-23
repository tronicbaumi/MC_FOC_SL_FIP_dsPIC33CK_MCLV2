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
 * $LastChangedRevision: 2543 $
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.general;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
import at.lcm.x2c.utils.QFormat;
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_LookupTable3D_FiP32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: TableData                                                                                    
        MaskDouble TableDataMaskVal = 
            (MaskDouble)this.getMaskParameter("TableData").getMaskDataType();
        TNumeric TableDataMaskData = 
            (TNumeric)TableDataMaskVal.getData();
        // Mask Parameter: DimX                                                                                         
        MaskComboBox DimXMaskVal = 
            (MaskComboBox)this.getMaskParameter("DimX").getMaskDataType();
        TString DimXMaskData = 
            (TString)DimXMaskVal.getData();
        // Mask Parameter: x_min                                                                                        
        MaskDouble x_minMaskVal = 
            (MaskDouble)this.getMaskParameter("x_min").getMaskDataType();
        TNumeric x_minMaskData = 
            (TNumeric)x_minMaskVal.getData();
        // Mask Parameter: x_max                                                                                        
        MaskDouble x_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("x_max").getMaskDataType();
        TNumeric x_maxMaskData = 
            (TNumeric)x_maxMaskVal.getData();
        // Mask Parameter: DimY                                                                                         
        MaskComboBox DimYMaskVal = 
            (MaskComboBox)this.getMaskParameter("DimY").getMaskDataType();
        TString DimYMaskData = 
            (TString)DimYMaskVal.getData();
        // Mask Parameter: y_max                                                                                        
        MaskDouble y_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("y_max").getMaskDataType();
        TNumeric y_maxMaskData = 
            (TNumeric)y_maxMaskVal.getData();
        // Mask Parameter: y_min                                                                                        
        MaskDouble y_minMaskVal = 
            (MaskDouble)this.getMaskParameter("y_min").getMaskDataType();
        TNumeric y_minMaskData = 
            (TNumeric)y_minMaskVal.getData();
        // Mask Parameter: DimZ                                                                                         
        MaskComboBox DimZMaskVal = 
            (MaskComboBox)this.getMaskParameter("DimZ").getMaskDataType();
        TString DimZMaskData = 
            (TString)DimZMaskVal.getData();
        // Mask Parameter: z_min                                                                                        
        MaskDouble z_minMaskVal = 
            (MaskDouble)this.getMaskParameter("z_min").getMaskDataType();
        TNumeric z_minMaskData = 
            (TNumeric)z_minMaskVal.getData();
        // Mask Parameter: z_max                                                                                        
        MaskDouble z_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("z_max").getMaskDataType();
        TNumeric z_maxMaskData = 
            (TNumeric)z_maxMaskVal.getData();

        // Implementation Parameter: Table                                                                              
        TNumeric TableCtrVal = this.getImplementationParameterData("Table");
        // Implementation Parameter: sfrX                                                                               
        TNumeric sfrXCtrVal = this.getImplementationParameterData("sfrX");
        // Implementation Parameter: sfrY                                                                               
        TNumeric sfrYCtrVal = this.getImplementationParameterData("sfrY");
        // Implementation Parameter: sfrZ                                                                               
        TNumeric sfrZCtrVal = this.getImplementationParameterData("sfrZ");
        // Implementation Parameter: maskX                                                                              
        TNumeric maskXCtrVal = this.getImplementationParameterData("maskX");
        // Implementation Parameter: maskY                                                                              
        TNumeric maskYCtrVal = this.getImplementationParameterData("maskY");
        // Implementation Parameter: maskZ                                                                              
        TNumeric maskZCtrVal = this.getImplementationParameterData("maskZ");
        // Implementation Parameter: idxOffsetX                                                                         
        TNumeric idxOffsetXCtrVal = this.getImplementationParameterData("idxOffsetX");
        // Implementation Parameter: idxOffsetY                                                                         
        TNumeric idxOffsetYCtrVal = this.getImplementationParameterData("idxOffsetY");
        // Implementation Parameter: idxOffsetZ                                                                         
        TNumeric idxOffsetZCtrVal = this.getImplementationParameterData("idxOffsetZ");
        // Implementation Parameter: sizeX                                                                              
        TNumeric sizeXCtrVal = this.getImplementationParameterData("sizeX");
        // Implementation Parameter: sizeY                                                                              
        TNumeric sizeYCtrVal = this.getImplementationParameterData("sizeY");
        // Implementation Parameter: sizeXY                                                                             
        TNumeric sizeXYCtrVal = this.getImplementationParameterData("sizeXY");
        // Implementation Parameter: gainX                                                                              
        TNumeric gainXCtrVal = this.getImplementationParameterData("gainX");
        // Implementation Parameter: gainY                                                                              
        TNumeric gainYCtrVal = this.getImplementationParameterData("gainY");
        // Implementation Parameter: gainZ                                                                              
        TNumeric gainZCtrVal = this.getImplementationParameterData("gainZ");
        // Implementation Parameter: gainXsfr                                                                           
        TNumeric gainXsfrCtrVal = this.getImplementationParameterData("gainXsfr");
        // Implementation Parameter: gainYsfr                                                                           
        TNumeric gainYsfrCtrVal = this.getImplementationParameterData("gainYsfr");
        // Implementation Parameter: gainZsfr                                                                           
        TNumeric gainZsfrCtrVal = this.getImplementationParameterData("gainZsfr");
        // Implementation Parameter: offsetX                                                                            
        TNumeric offsetXCtrVal = this.getImplementationParameterData("offsetX");
        // Implementation Parameter: offsetY                                                                            
        TNumeric offsetYCtrVal = this.getImplementationParameterData("offsetY");
        // Implementation Parameter: offsetZ                                                                            
        TNumeric offsetZCtrVal = this.getImplementationParameterData("offsetZ");
        // Implementation Parameter: minX                                                                               
        TNumeric minXCtrVal = this.getImplementationParameterData("minX");
        // Implementation Parameter: maxX                                                                               
        TNumeric maxXCtrVal = this.getImplementationParameterData("maxX");
        // Implementation Parameter: minY                                                                               
        TNumeric minYCtrVal = this.getImplementationParameterData("minY");
        // Implementation Parameter: maxY                                                                               
        TNumeric maxYCtrVal = this.getImplementationParameterData("maxY");
        // Implementation Parameter: minZ                                                                               
        TNumeric minZCtrVal = this.getImplementationParameterData("minZ");
        // Implementation Parameter: maxZ                                                                               
        TNumeric maxZCtrVal = this.getImplementationParameterData("maxZ");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        int size_x;
        int size_y;
        int size_z;
        final int SIZE_ROW = 1;
        final int BITS = 32;
        double sfrX, sfrY, sfrZ;
        double x_min, x_max, offsetX, gainX, y_min, y_max, offsetY, gainY, z_min, z_max, offsetZ, gainZ;

        /* get table size */
        size_x = Integer.valueOf(DimXMaskVal.getValue());
        size_y = Integer.valueOf(DimYMaskVal.getValue());
        size_z = Integer.valueOf(DimZMaskVal.getValue());

        /* check table data for correct size */
        if ((TableDataMaskData.getNumColumns() != (size_x * size_y * size_z)) || (TableDataMaskData.getNumRows() != SIZE_ROW)) {
            throw new Exception("Lookup Table Size mismatch in column: expected=(" + SIZE_ROW + ", " + (size_x * size_y * size_z) + ") " + "got=("
                    + TableDataMaskData.getNumRows() + "," + TableDataMaskData.getNumColumns() + ")");
        }

        /* convert dimension value */
        sizeXCtrVal.setReal(0, 0, size_x);
        sizeYCtrVal.setReal(0, 0, size_y);
        sizeXYCtrVal.setReal(0, 0, size_x * size_y);

        /* convert input scaling */
        x_min = Double.valueOf(x_minMaskVal.getValue());
        x_max = Double.valueOf(x_maxMaskVal.getValue());
        if (x_min >= x_max) {
            throw new Exception("Scaling of x-dimension not possible: x_max must be greater than x_min!)");
        }
        offsetX = x_min + ((x_max - x_min) / 2);
        gainX = 2 / (x_max - x_min);
        offsetXCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(offsetX, BITS - 1, BITS, true)));
        gainXsfrCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(gainX, BITS, true)));
        gainXCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(gainX, (int) (gainXsfrCtrVal.getReal(0, 0)), BITS, true)));

        y_min = Double.valueOf(y_minMaskVal.getValue());
        y_max = Double.valueOf(y_maxMaskVal.getValue());
        if (y_min >= y_max) {
            throw new Exception("Scaling of y-dimension not possible: y_max must be greater than y_min!)");
        }
        offsetY = y_min + ((y_max - y_min) / 2);
        gainY = 2 / (y_max - y_min);
        offsetYCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(offsetY, BITS - 1, BITS, true)));
        gainYsfrCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(gainY, BITS, true)));
        gainYCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(gainY, (int) (gainYsfrCtrVal.getReal(0, 0)), BITS, true)));

        z_min = Double.valueOf(z_minMaskVal.getValue());
        z_max = Double.valueOf(z_maxMaskVal.getValue());
        if (z_min >= z_max) {
            throw new Exception("Scaling of z-dimension not possible: z_max must be greater than z_min!)");
        }
        offsetZ = z_min + ((z_max - z_min) / 2);
        gainZ = 2 / (z_max - z_min);
        offsetZCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(offsetZ, BITS - 1, BITS, true)));
        gainZsfrCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(gainZ, BITS, true)));
        gainZCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(gainZ, (int) (gainZsfrCtrVal.getReal(0, 0)), BITS, true)));

        /* convert boundaries */
        minXCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(x_min, BITS - 1, BITS, true)));
        maxXCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(x_max, BITS - 1, BITS, true)));

        minYCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(y_min, BITS - 1, BITS, true)));
        maxYCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(y_max, BITS - 1, BITS, true)));

        minZCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(z_min, BITS - 1, BITS, true)));
        maxZCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(z_max, BITS - 1, BITS, true)));

        /* convert FiP scaling */
        sfrX = Double.valueOf(QFormat.getQFormat(size_x - 1, BITS + 2, true));
        sfrXCtrVal.setReal(0, 0, sfrX);
        maskXCtrVal.setReal(0, 0, Math.pow(2, sfrX) - 1);
        idxOffsetXCtrVal.setReal(0, 0, Math.pow(2, BITS - 1 - sfrX));

        sfrY = Double.valueOf(QFormat.getQFormat(size_y - 1, BITS + 2, true));
        sfrYCtrVal.setReal(0, 0, sfrY);
        maskYCtrVal.setReal(0, 0, Math.pow(2, sfrY) - 1);
        idxOffsetYCtrVal.setReal(0, 0, Math.pow(2, BITS - 1 - sfrY));

        sfrZ = Double.valueOf(QFormat.getQFormat(size_z - 1, BITS + 2, true));
        sfrZCtrVal.setReal(0, 0, sfrZ);
        maskZCtrVal.setReal(0, 0, Math.pow(2, sfrZ) - 1);
        idxOffsetZCtrVal.setReal(0, 0, Math.pow(2, BITS - 1 - sfrZ));

        /* convert table data */
        Double[] tmpData = new Double[size_x * size_y * size_z];
        for (int z = 0; z < size_z; z++) {
            for (int y = 0; y < size_y; y++) {
                for (int x = 0; x < size_x; x++) {
                    tmpData[x + (size_x * y) + (size_x * size_y * z)] = Double.valueOf(QFormat.getQValue(
                            TableDataMaskData.getReal(0, x + (size_x * y) + (size_x * size_y * z)), BITS - 1, BITS, true));
                }
            }
        }

        TableCtrVal = new TNumeric(tmpData);

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("Table", TableCtrVal);
        this.setImplementationParameterData("sfrX", sfrXCtrVal);
        this.setImplementationParameterData("sfrY", sfrYCtrVal);
        this.setImplementationParameterData("sfrZ", sfrZCtrVal);
        this.setImplementationParameterData("maskX", maskXCtrVal);
        this.setImplementationParameterData("maskY", maskYCtrVal);
        this.setImplementationParameterData("maskZ", maskZCtrVal);
        this.setImplementationParameterData("idxOffsetX", idxOffsetXCtrVal);
        this.setImplementationParameterData("idxOffsetY", idxOffsetYCtrVal);
        this.setImplementationParameterData("idxOffsetZ", idxOffsetZCtrVal);
        this.setImplementationParameterData("sizeX", sizeXCtrVal);
        this.setImplementationParameterData("sizeY", sizeYCtrVal);
        this.setImplementationParameterData("sizeXY", sizeXYCtrVal);
        this.setImplementationParameterData("gainX", gainXCtrVal);
        this.setImplementationParameterData("gainY", gainYCtrVal);
        this.setImplementationParameterData("gainZ", gainZCtrVal);
        this.setImplementationParameterData("gainXsfr", gainXsfrCtrVal);
        this.setImplementationParameterData("gainYsfr", gainYsfrCtrVal);
        this.setImplementationParameterData("gainZsfr", gainZsfrCtrVal);
        this.setImplementationParameterData("offsetX", offsetXCtrVal);
        this.setImplementationParameterData("offsetY", offsetYCtrVal);
        this.setImplementationParameterData("offsetZ", offsetZCtrVal);
        this.setImplementationParameterData("minX", minXCtrVal);
        this.setImplementationParameterData("maxX", maxXCtrVal);
        this.setImplementationParameterData("minY", minYCtrVal);
        this.setImplementationParameterData("maxY", maxYCtrVal);
        this.setImplementationParameterData("minZ", minZCtrVal);
        this.setImplementationParameterData("maxZ", maxZCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: TableData                                                                                    
        MaskDouble TableDataMaskVal = 
            (MaskDouble)this.getMaskParameter("TableData").getMaskDataType();
        TNumeric TableDataMaskData = 
            (TNumeric)TableDataMaskVal.getData();
        // Mask Parameter: DimX                                                                                         
        MaskComboBox DimXMaskVal = 
            (MaskComboBox)this.getMaskParameter("DimX").getMaskDataType();
        TString DimXMaskData = 
            (TString)DimXMaskVal.getData();
        // Mask Parameter: x_min                                                                                        
        MaskDouble x_minMaskVal = 
            (MaskDouble)this.getMaskParameter("x_min").getMaskDataType();
        TNumeric x_minMaskData = 
            (TNumeric)x_minMaskVal.getData();
        // Mask Parameter: x_max                                                                                        
        MaskDouble x_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("x_max").getMaskDataType();
        TNumeric x_maxMaskData = 
            (TNumeric)x_maxMaskVal.getData();
        // Mask Parameter: DimY                                                                                         
        MaskComboBox DimYMaskVal = 
            (MaskComboBox)this.getMaskParameter("DimY").getMaskDataType();
        TString DimYMaskData = 
            (TString)DimYMaskVal.getData();
        // Mask Parameter: y_max                                                                                        
        MaskDouble y_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("y_max").getMaskDataType();
        TNumeric y_maxMaskData = 
            (TNumeric)y_maxMaskVal.getData();
        // Mask Parameter: y_min                                                                                        
        MaskDouble y_minMaskVal = 
            (MaskDouble)this.getMaskParameter("y_min").getMaskDataType();
        TNumeric y_minMaskData = 
            (TNumeric)y_minMaskVal.getData();
        // Mask Parameter: DimZ                                                                                         
        MaskComboBox DimZMaskVal = 
            (MaskComboBox)this.getMaskParameter("DimZ").getMaskDataType();
        TString DimZMaskData = 
            (TString)DimZMaskVal.getData();
        // Mask Parameter: z_min                                                                                        
        MaskDouble z_minMaskVal = 
            (MaskDouble)this.getMaskParameter("z_min").getMaskDataType();
        TNumeric z_minMaskData = 
            (TNumeric)z_minMaskVal.getData();
        // Mask Parameter: z_max                                                                                        
        MaskDouble z_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("z_max").getMaskDataType();
        TNumeric z_maxMaskData = 
            (TNumeric)z_maxMaskVal.getData();

        // Implementation Parameter: Table                                                                              
        TNumeric TableCtrVal = this.getImplementationParameterData("Table");
        // Implementation Parameter: sfrX                                                                               
        TNumeric sfrXCtrVal = this.getImplementationParameterData("sfrX");
        // Implementation Parameter: sfrY                                                                               
        TNumeric sfrYCtrVal = this.getImplementationParameterData("sfrY");
        // Implementation Parameter: sfrZ                                                                               
        TNumeric sfrZCtrVal = this.getImplementationParameterData("sfrZ");
        // Implementation Parameter: maskX                                                                              
        TNumeric maskXCtrVal = this.getImplementationParameterData("maskX");
        // Implementation Parameter: maskY                                                                              
        TNumeric maskYCtrVal = this.getImplementationParameterData("maskY");
        // Implementation Parameter: maskZ                                                                              
        TNumeric maskZCtrVal = this.getImplementationParameterData("maskZ");
        // Implementation Parameter: idxOffsetX                                                                         
        TNumeric idxOffsetXCtrVal = this.getImplementationParameterData("idxOffsetX");
        // Implementation Parameter: idxOffsetY                                                                         
        TNumeric idxOffsetYCtrVal = this.getImplementationParameterData("idxOffsetY");
        // Implementation Parameter: idxOffsetZ                                                                         
        TNumeric idxOffsetZCtrVal = this.getImplementationParameterData("idxOffsetZ");
        // Implementation Parameter: sizeX                                                                              
        TNumeric sizeXCtrVal = this.getImplementationParameterData("sizeX");
        // Implementation Parameter: sizeY                                                                              
        TNumeric sizeYCtrVal = this.getImplementationParameterData("sizeY");
        // Implementation Parameter: sizeXY                                                                             
        TNumeric sizeXYCtrVal = this.getImplementationParameterData("sizeXY");
        // Implementation Parameter: gainX                                                                              
        TNumeric gainXCtrVal = this.getImplementationParameterData("gainX");
        // Implementation Parameter: gainY                                                                              
        TNumeric gainYCtrVal = this.getImplementationParameterData("gainY");
        // Implementation Parameter: gainZ                                                                              
        TNumeric gainZCtrVal = this.getImplementationParameterData("gainZ");
        // Implementation Parameter: gainXsfr                                                                           
        TNumeric gainXsfrCtrVal = this.getImplementationParameterData("gainXsfr");
        // Implementation Parameter: gainYsfr                                                                           
        TNumeric gainYsfrCtrVal = this.getImplementationParameterData("gainYsfr");
        // Implementation Parameter: gainZsfr                                                                           
        TNumeric gainZsfrCtrVal = this.getImplementationParameterData("gainZsfr");
        // Implementation Parameter: offsetX                                                                            
        TNumeric offsetXCtrVal = this.getImplementationParameterData("offsetX");
        // Implementation Parameter: offsetY                                                                            
        TNumeric offsetYCtrVal = this.getImplementationParameterData("offsetY");
        // Implementation Parameter: offsetZ                                                                            
        TNumeric offsetZCtrVal = this.getImplementationParameterData("offsetZ");
        // Implementation Parameter: minX                                                                               
        TNumeric minXCtrVal = this.getImplementationParameterData("minX");
        // Implementation Parameter: maxX                                                                               
        TNumeric maxXCtrVal = this.getImplementationParameterData("maxX");
        // Implementation Parameter: minY                                                                               
        TNumeric minYCtrVal = this.getImplementationParameterData("minY");
        // Implementation Parameter: maxY                                                                               
        TNumeric maxYCtrVal = this.getImplementationParameterData("maxY");
        // Implementation Parameter: minZ                                                                               
        TNumeric minZCtrVal = this.getImplementationParameterData("minZ");
        // Implementation Parameter: maxZ                                                                               
        TNumeric maxZCtrVal = this.getImplementationParameterData("maxZ");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        /* TODO Add Implementation- to Mask conversion */
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("TableData").setValue(TableDataMaskData.toFullString());
        this.getMaskParameter("DimX").setValue(DimXMaskData.getString());
        this.getMaskParameter("x_min").setValue(x_minMaskData.toFullString());
        this.getMaskParameter("x_max").setValue(x_maxMaskData.toFullString());
        this.getMaskParameter("DimY").setValue(DimYMaskData.getString());
        this.getMaskParameter("y_max").setValue(y_maxMaskData.toFullString());
        this.getMaskParameter("y_min").setValue(y_minMaskData.toFullString());
        this.getMaskParameter("DimZ").setValue(DimZMaskData.getString());
        this.getMaskParameter("z_min").setValue(z_minMaskData.toFullString());
        this.getMaskParameter("z_max").setValue(z_maxMaskData.toFullString());
    }
}
