// This file is released under the 3-clause BSD license. See COPYING-BSD.
// Generated by builder.sce : Please, do not edit this file
// ----------------------------------------------------------------------------
//
if win64() then
  warning(_("This module requires a Windows x86 platform."));
  return
end
//
Basic_x86_path = get_absolute_file_path('loader_x86.sce');
//
// ulink previous function with same name
[bOK, ilib] = c_link('x2c_DoNothing_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_EnableSuperblock_C');
if bOK then
  ulink(ilib);
end
//
link(Basic_x86_path + 'libBasic_x86' + getdynlibext(), ['x2c_DoNothing_C','x2c_EnableSuperblock_C'],'c');
// remove temp. variables on stack
clear Basic_x86_path;
clear bOK;
clear ilib;
// ----------------------------------------------------------------------------
