// Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
// All rights reserved.
//
// This file is licensed according to the BSD 3-clause license as follows:
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
//       the names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This file is part of X2C. http://x2c.lcm.at/
// $LastChangedRevision: 2465 $
// $LastChangedDate:: 2022-02-15 15:12:58 +0100#$

function [x,y,typ] = x2c_ModelTransformation(job, arg1, arg2)
    // import necessary java classes
    jimport at.lcm.x2c.utils.Utils;
    
    // get file separator
    fs = filesep();
    
    // get X2C root directory
    X2CRootDir = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");

    x = [];
    y = [];
    typ = [];

    select job
    case "plot" then
        standard_draw(arg1)

    case "getinputs" then
        [x,y,typ] = standard_inputs(arg1)

    case "getoutputs" then
        [x,y,typ] = standard_outputs(arg1)

    case "getorigin" then
        [x,y] = standard_origin(arg1)

    case "set" then
        x = arg1
        while %t do
            if ~ exists("%scicos_prob") then
                w = createWindow();
                w.axes_size = [500,150];
                w.figure_name = "Model Transformation (%d)";
                w.icon = X2CRootDir + "Documentation" + fs + "General" + fs + "Styles" + fs + "X2C" + fs + "AppIcon.png";
                tf = uicontrol(w, "style", "text", "units", "normalized", "position", [0 0.5 1 0.5], "horizontalalignment", "center", "verticalalignment", "bottom");
                tf.string = "Model transformation in progress...";
                disp(tf.string);    // display string in console
                tf2 = uicontrol(w, "style", "text", "units", "normalized", "position", [0 0 1 0.5], "horizontalalignment", "center","verticalalignment", "top");
                tf2.string = "(If transformation is successful, this window will be automatically closed.)";

                try
                    x2c_transformModel_Comm();
                    tf.string = "Model transformation done!";
                    tf2.string = "";
                    disp(tf.string);    // display string in console
                    sleep(500);         // wait a little before closing the window
                    close(w);           // close window
                catch
                    errorStr = lasterror();
                    tf.string = "Model transformation failed!";
                    disp(tf.string);            // display string in console
                    tf2.string = errorStr(2);   // second line of error string should contain the most useful information
                    tf3 = uicontrol(w, "style", "text", "units", "normalized", "position", [0 0 1 0.3], "horizontalalignment", "center","verticalalignment", "middle");
                    tf3.string = "(See console output for more information.)";
                    disp(errorStr);     // display full error message in console
                    // do not close window - user has to close it manually
                end

            end
            break
        end

    case "define" then
        // see: help scicos_model
        model = scicos_model()
        model.sim = list("x2c_DoNothing_C", 4);
        model.in = [];
        model.evtin = []
        model.out = [];
        model.state = []   // continuous states
        model.dstate = []  // discrete-time states
        model.ipar = [] //contrParamVals
        model.blocktype = "c"
        model.nmode = 0
        model.nzcross = 0
        model.dep_ut = [%f %f]
        exprs = [""]
        gr_i=[];
        x=standard_define([7 3],model, exprs, gr_i);
        x.graphics.style = "fillColor=#ff8c00;gradientColor=#ff8c00;rounded=false;noLabel=false;displayedLabel=transform Model and<BR>push to Communicator;align=center";
    end

endfunction
