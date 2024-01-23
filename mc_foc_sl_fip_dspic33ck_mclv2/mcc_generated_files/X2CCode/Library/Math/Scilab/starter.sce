// This file was generated by createLibraryStarter.sce on 30-08-2023 03:26

mprintf("+++ Loading X2C library Math\n");
scilab_dir = getLibraryScilabPath(fullfile(get_absolute_file_path("starter.sce"), ".."));

// load and add help chapter
if or(getscilabmode() == ["NW";"STD"]) then
    path_addchapter = fullfile(scilab_dir, "jar");
    if isdir(path_addchapter) then
        add_help_chapter("X2C Math Library", path_addchapter, %F);
    end
end

// load interface functions
exec("x2c_uSub.sci", -1);
exec("x2c_uAdd.sci", -1);
exec("x2c_Sum.sci", -1);
exec("x2c_Sub.sci", -1);
exec("x2c_Sqrt.sci", -1);
exec("x2c_Sin.sci", -1);
exec("x2c_Sign.sci", -1);
exec("x2c_Negation.sci", -1);
exec("x2c_Mult.sci", -1);
exec("x2c_L2Norm.sci", -1);
exec("x2c_Exp.sci", -1);
exec("x2c_Div.sci", -1);
exec("x2c_Cos.sci", -1);
exec("x2c_Average.sci", -1);
exec("x2c_Atan2.sci", -1);
exec("x2c_Asin.sci", -1);
exec("x2c_Add.sci", -1);
exec("x2c_Acos.sci", -1);
exec("x2c_Abs.sci", -1);

palette_file = fullfile(scilab_dir, "Math.xpal");
// load/create palette for library
if isfile(palette_file) then
    // palette already exists -> load saved palette
    xcosPalAdd(palette_file, "X2C");
else
    
    // load blocks and build palette
    pal = xcosPal("Math");
    allIconsAvailable = %t;
    
    icon_dir = fullfile(scilab_dir, "Icons");
    
    // Abs
    mprintf("Loading block Abs...");
    o = x2c_Abs("define");
    pal_icon = fullfile(icon_dir, "Abs.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Acos
    mprintf("Loading block Acos...");
    o = x2c_Acos("define");
    pal_icon = fullfile(icon_dir, "Acos.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Add
    mprintf("Loading block Add...");
    o = x2c_Add("define");
    pal_icon = fullfile(icon_dir, "Add.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Asin
    mprintf("Loading block Asin...");
    o = x2c_Asin("define");
    pal_icon = fullfile(icon_dir, "Asin.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Atan2
    mprintf("Loading block Atan2...");
    o = x2c_Atan2("define");
    pal_icon = fullfile(icon_dir, "Atan2.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Average
    mprintf("Loading block Average...");
    o = x2c_Average("define");
    pal_icon = fullfile(icon_dir, "Average.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Cos
    mprintf("Loading block Cos...");
    o = x2c_Cos("define");
    pal_icon = fullfile(icon_dir, "Cos.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Div
    mprintf("Loading block Div...");
    o = x2c_Div("define");
    pal_icon = fullfile(icon_dir, "Div.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Exp
    mprintf("Loading block Exp...");
    o = x2c_Exp("define");
    pal_icon = fullfile(icon_dir, "Exp.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // L2Norm
    mprintf("Loading block L2Norm...");
    o = x2c_L2Norm("define");
    pal_icon = fullfile(icon_dir, "L2Norm.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Mult
    mprintf("Loading block Mult...");
    o = x2c_Mult("define");
    pal_icon = fullfile(icon_dir, "Mult.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Negation
    mprintf("Loading block Negation...");
    o = x2c_Negation("define");
    pal_icon = fullfile(icon_dir, "Negation.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Sign
    mprintf("Loading block Sign...");
    o = x2c_Sign("define");
    pal_icon = fullfile(icon_dir, "Sign.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Sin
    mprintf("Loading block Sin...");
    o = x2c_Sin("define");
    pal_icon = fullfile(icon_dir, "Sin.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Sqrt
    mprintf("Loading block Sqrt...");
    o = x2c_Sqrt("define");
    pal_icon = fullfile(icon_dir, "Sqrt.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Sub
    mprintf("Loading block Sub...");
    o = x2c_Sub("define");
    pal_icon = fullfile(icon_dir, "Sub.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // Sum
    mprintf("Loading block Sum...");
    o = x2c_Sum("define");
    pal_icon = fullfile(icon_dir, "Sum.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // uAdd
    mprintf("Loading block uAdd...");
    o = x2c_uAdd("define");
    pal_icon = fullfile(icon_dir, "uAdd.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    // uSub
    mprintf("Loading block uSub...");
    o = x2c_uSub("define");
    pal_icon = fullfile(icon_dir, "uSub.png");
    if ~isfile(pal_icon) then
        pal_icon = [];
        allIconsAvailable = %f;
    end
    pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
    clear("o");
    mprintf("done\n");
    
    

    // load palette
    xcosPalAdd(pal, "X2C");
    
    // save palette if all icons are available
    if allIconsAvailable then
        // create directory for XPAL file if it does not exist
        if ~isdir(scilab_dir) then
            mkdir(scilab_dir);
        end
        xcosPalExport(pal, palette_file);
    end
    
end

// cleanup
clear("pal", "pal_icon", "style", "allIconsAvailable", "icon_dir", "scilab_dir");
clear("path_addchapter", "palette_file");

mprintf("---\n");
