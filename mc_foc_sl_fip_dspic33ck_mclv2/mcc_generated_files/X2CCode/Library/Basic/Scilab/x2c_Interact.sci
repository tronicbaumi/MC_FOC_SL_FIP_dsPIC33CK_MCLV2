// Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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

function [x_sci,y_sci,typ_sci] = x2c_Interact(job, arg1, arg2)
x_sci = [];
y_sci = [];
typ_sci = [];

select job
case "plot" then
// ++ BlockGenerator: Plot Section
    standard_draw(arg1);
// -- BlockGenerator: Plot Section

case "getinputs" then
    [x_sci,y_sci,typ_sci] = standard_inputs(arg1);

case "getoutputs" then
    [x_sci,y_sci,typ_sci] = standard_outputs(arg1);

case "getorigin" then
    [x_sci,y_sci] = standard_origin(arg1);

case "set" then
    x_sci = arg1;
    if ~ exists("%scicos_prob") then
        // double click on icon     
        fName = "doInteraction";    // name of file to execute, without extension
        fullName = strsubst(pwd(), "\", "/") +"/" + fName + ".sci";
        exec(fullName, -1);
        
        [str, expr] = doInteraction(x_sci.model.label, x_sci.graphics.exprs);
        x_sci.graphics.style = str;
        x_sci.graphics.exprs = expr;
    end

    
case "define" then 
    // see: help scicos_model
    model = scicos_model();
    model.sim = list("x2c_DoNothing_C", 4);
    model.in = [];
    model.evtin = [];
    model.out = [];
    model.state = [];   // continuous states
    model.dstate = [];  // discrete-time states
    model.ipar = [];    //contrParamVals
    model.blocktype = "c";
    model.nmode = 0;
    model.nzcross = 0;
    model.dep_ut = [%f %f];
    exprs = "0";
    gr_i=[];
    
    x_sci = standard_define([5 3],model, exprs, gr_i);
    x_sci.graphics.style = "fillColor=#ff8c00;gradientColor=#ff8c00;rounded=false;noLabel=false;displayedLabel=interact;align=center;";
   
end

endfunction
