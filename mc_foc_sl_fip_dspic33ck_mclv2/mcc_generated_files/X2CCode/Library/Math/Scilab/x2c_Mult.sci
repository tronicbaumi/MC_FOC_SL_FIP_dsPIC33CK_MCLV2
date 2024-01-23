// This file was generated by createIFunction.sci on 30-08-2023 03:26

function [x_sci,y_sci,typ_sci] = x2c_Mult(job, arg1, arg2)

thisBlockData.Library = "Math";
thisBlockData.block_type_name = "Mult";
thisBlockData.block_xcosfilename = "x2c_Mult";

jimport("at.lcm.x2c.parameterEditor.X2cParameterEditor_Xcos");
jimport("at.lcm.x2c.utils.Utils");

x_sci = [];
y_sci = [];
typ_sci = [];
X2CRootDir = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");
X2CRootDir = strsubst(X2CRootDir, "\", "/");

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
    block_graphics = arg1.graphics;
    block_model = arg1.model;
    exprs = block_graphics.exprs;
    xcosBlockId = block_model.uid;
    while %t do
        if exists("X2C_sampleTime") then
            X2C_sampleTime_tmp = X2C_sampleTime;
        else
            X2C_sampleTime_tmp = -1;
        end
        x2cPEdit = jnewInstance(X2cParameterEditor_Xcos, exprs, xcosBlockId, X2C_sampleTime_tmp);
        thisBlock_isPartOfModel = jinvoke(x2cPEdit, "isBlockPartOfModel");
        if (~ exists("X2C_sampleTime")) & (~ thisBlock_isPartOfModel) then
            warning("X2C_sampleTime is not set; default is used");
        elseif (exists("X2C_sampleTime")) & (thisBlock_isPartOfModel) then
            warning("X2C_sampleTime is set; but model sampleTime is used");
        end
        if ~ exists("%scicos_prob") then
            // double click on icon
        
            ok = jinvoke(x2cPEdit, "runGUI");
        else
            ok = %t;
        end
        
        if ~ok then
            break;
        end
        
        used_impl = jinvoke(x2cPEdit, "getUsedImplementationName");
        block_model.sim = list("x2c_Mult_"  + used_impl + "_C", 4);
        
        xcp = jinvoke(x2cPEdit, "getControlerParameter");
        
        block_model.ipar = double(jinvoke(xcp, "getIntegerParameter_values"));
        block_model.rpar = double(jinvoke(xcp, "getDoubleParameter_values"));
        po = jinvoke(x2cPEdit, "getControlerParameter_DoubleArrayParameter_values");
        otab = list();
        
        for i=0:jinvoke(po, "size")-1
            otab($+1) = jinvoke(po, "get", i);
        end
        block_model.opar = otab;
        
        exprs = jinvoke(x2cPEdit, "getXcosExprs")';
        
        block_graphics.exprs = exprs;
        x_sci.graphics = block_graphics;
        x_sci.model = block_model;
    
// ++ BlockGenerator: Define Section
define_in_style = ["textOpacity=0";"textOpacity=0"];
define_out_style = "textOpacity=0";

// -- BlockGenerator: Define Section
    
        if isdef("define_style", "l")
            define_style_struct = string2struct(define_style);
            if isfield(define_style_struct, "image")
                image_link = getStyleImageLink(thisBlockData.Library, thisBlockData.block_type_name, define_style_struct.image)
                define_style_struct.image = image_link;
            end
            style_string = struct2string(define_style_struct);
            x_sci.graphics.style = thisBlockData.block_xcosfilename + ";" + style_string;
        end
        
        break;
    end
    
case "define" then
    if exists("X2C_sampleTime") then
        X2C_sampleTime_tmp = X2C_sampleTime;
    else
        X2C_sampleTime_tmp = -1;
    end
    x2cPEdit = jnewInstance(X2cParameterEditor_Xcos, thisBlockData.block_type_name, X2C_sampleTime_tmp);
    
    inport_labels = jinvoke(x2cPEdit, "getBlockInportNames");
    outport_labels = jinvoke(x2cPEdit, "getBlockOutportNames");
    
    // see: help scicos_model
    model = scicos_model();
    used_impl = jinvoke(x2cPEdit, "getUsedImplementationName");
    model.sim = list("x2c_Mult_"  + used_impl + "_C", 4);
    model.in = jinvoke(x2cPEdit, "getBlockInport_xcosDef");
    model.evtin = [];
    
    model.out = jinvoke(x2cPEdit, "getBlockOutport_xcosDef");
    model.state = [];   // continuous states
    model.dstate = [];  // discrete-time states
    
    model.ipar = double(jinvoke(x2cPEdit, "getControlerParameter_IntegerParameter_values")');
    model.rpar = double(jinvoke(x2cPEdit, "getControlerParameter_DoubleParameter_values")');
    model.blocktype = "c";
    model.nmode = 0;
    model.nzcross = 0;
    model.dep_ut = [%t %f];
    
    exprs = jinvoke(x2cPEdit, "getXcosExprs")';
    
// ++ BlockGenerator: BlockIconDefaultSize
    blockIconDefaultSize = [2 2];
// -- BlockGenerator: BlockIconDefaultSize
    
    gr_i = [];
    
    x_sci = standard_define(blockIconDefaultSize, model, exprs, gr_i);
    
    // see help: graphics structure
    x_sci.graphics.in_label = inport_labels; // labels of regular input ports
    x_sci.graphics.out_label = outport_labels; // labels of regular output ports
    style = struct();
    style.fillColor = "#61BDFC";
    style.gradientColor = "#61BDFC";
    style.rounded = "false";
    
    define_in_style = x_sci.graphics.in_style;
    define_out_style = x_sci.graphics.out_style;
    
// ++ BlockGenerator: Define Section
define_in_style = ["textOpacity=0";"textOpacity=0"];
define_out_style = "textOpacity=0";

// -- BlockGenerator: Define Section
    
    if isdef("define_style", "l")
        define_style_struct = string2struct(define_style);
        style = mergeStructures(style, define_style_struct);
    end
    
// ++ BlockGenerator: Style Section
style_tmp.image = "file:///" + pwd() + "/../Doc/Images/Mult.svg"

// -- BlockGenerator: Style Section
    
    if isdef("style_tmp", "l")
        // processing image member
        if isfield(style_tmp, "image")
            style_tmp.image = getStyleImageLink(thisBlockData.Library, thisBlockData.block_type_name, style_tmp.image, %t);
            if isempty(style_tmp.image)
                // removes image member if 'Dummy.svg' was used before
                style_tmp.image = null();
            end
        end
        
        // add style structure fields to style structure
        style = mergeStructures(style, style_tmp);
    end
    
    // try default image location if no explicit image location is defined
    if ~isfield(style, "image")
        image_link = getStyleImageLink(thisBlockData.Library, thisBlockData.block_type_name);
        if ~isempty(image_link)
            style.image = image_link;
        end
    end
    
    // Convert to Scilab 6 suitable format
    string_style = struct2string(style);
    x_sci.graphics.style = string_style;
    
    // Convert to Scilab 6 suitable format
    x_sci.graphics.in_style = getPortLabelStyle(define_in_style);
    x_sci.graphics.out_style = getPortLabelStyle(define_out_style);
end

endfunction
