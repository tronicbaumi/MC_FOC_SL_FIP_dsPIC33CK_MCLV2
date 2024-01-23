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
// $LastChangedRevision: 2498 $
// $LastChangedDate:: 2022-03-01 09:56:55 +0100#$
//
// Starter script for Basic library

mprintf("+++ Loading X2C library Basic\n");
scilab_dir = fullfile(get_absolute_file_path("starter.sce"), "..", "Scilab");
scilab_spec_dir = getLibraryScilabPath(fullfile(get_absolute_file_path("starter.sce"), ".."));
err = %f;       // error flag

// load and add help chapter
if or(getscilabmode() == ["NW";"STD"]) then
    path_addchapter = fullfile(scilab_dir, "jar");
    if isdir(path_addchapter) then
        add_help_chapter("X2C Basic Library", path_addchapter, %F);
    end
end

block_names = ["ProjectDocumentation", "ModelTransformation", "CommunicatorStart", "Interact"];
//block_names = ["ProjectDocumentation", "ModelTransformation", "CommunicatorStart", "Interact", "EnableSuperblock"];

// load interface functions
for cur_block = block_names
    exec("x2c_" + cur_block + ".sci", -1);
end

palette_file = fullfile(scilab_spec_dir, "Basic.xpal");
// load/create palette for library
if isfile(palette_file) then
    // palette already exists -> load saved palette
    xcosPalAdd(palette_file, "X2C");
else
    // load blocks and build palette
    pal = xcosPal("Basic");
    
    for cur_block = block_names
        cur_block_identifier = "x2c_" + cur_block;
    
        mprintf("Loading block %s...\n", cur_block_identifier);
        try
            o = evstr(cur_block_identifier + "('"define'");");
            pal_icon = fullfile("..", "Doc", "Icons", cur_block + ".png");
            pal = xcosPalAddBlock(pal, o, pal_icon, o.graphics.style);
            clear("o");
            mprintf("done\n");
        catch
            err = %t;
            mprintf("ERROR: %s\n", lasterror());
        end
    end
    
    // load palette
    xcosPalAdd(pal, "X2C");
  
    // save palette
    if ~err then
        // create directory for XPAL file if it does not exist
        if ~isdir(scilab_spec_dir) then
            mkdir(scilab_spec_dir);
        end
        xcosPalExport(pal, palette_file);
    end
end

// cleanup
clear("pal", "pal_icon", "style", "scilab_spec_dir", "palette_file");
clear("err", "path_addchapter");
clear("block_names", "cur_block", "cur_block_identifier");

mprintf("---\n");
