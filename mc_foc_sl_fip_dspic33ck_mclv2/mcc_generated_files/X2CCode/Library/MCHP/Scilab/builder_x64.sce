// This file was generated by createLibraryBuilder.sce on 01-06-2023 12:51

jimport at.lcm.x2c.utils.Utils;
jimport java.io.File;
if(findmsvccompiler() ~= "unknown") then
    configure_msvc();
end
if ~haveacompiler() then
    mprintf("Building MCHP library for x64 system skipped (no compiler found).\n");
    return;
end

X2C_ROOT = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");
X2C_LIB_PATH = get_absolute_file_path("builder_x64.sce");
X2C_LIB_PATH = jinvoke(jnewInstance(File, X2C_LIB_PATH), "getParent");

try
    // delete "is-compiled" marker
    mdelete("Library_is_compiled_for_x64.*");

    // prepare names and flags for building command
    names = [];
    files = [];
    names = [names,  "x2c_BEMF_MCHP_FiP16_C" "x2c_BEMF_MCHP_FiP32_C" "x2c_BEMF_MCHP_Float32_C"];
    files = [files,  "x2c_BEMF_MCHP_FiP16_C.c" "x2c_BEMF_MCHP_FiP32_C.c" "x2c_BEMF_MCHP_Float32_C.c"];
    names = [names,  "x2c_BEMF_PLL_MCH_FiP16_C" "x2c_BEMF_PLL_MCH_FiP32_C" "x2c_BEMF_PLL_MCH_Float32_C"];
    files = [files,  "x2c_BEMF_PLL_MCH_FiP16_C.c" "x2c_BEMF_PLL_MCH_FiP32_C.c" "x2c_BEMF_PLL_MCH_Float32_C.c"];
    names = [names,  "x2c_Clarke_inv_M_FiP16_C" "x2c_Clarke_inv_M_FiP32_C" "x2c_Clarke_inv_M_Float32_C"];
    files = [files,  "x2c_Clarke_inv_M_FiP16_C.c" "x2c_Clarke_inv_M_FiP32_C.c" "x2c_Clarke_inv_M_Float32_C.c"];
    names = [names,  "x2c_Clarke_MCHP_FiP16_C" "x2c_Clarke_MCHP_FiP32_C" "x2c_Clarke_MCHP_Float32_C"];
    files = [files,  "x2c_Clarke_MCHP_FiP16_C.c" "x2c_Clarke_MCHP_FiP32_C.c" "x2c_Clarke_MCHP_Float32_C.c"];
    names = [names,  "x2c_Clarke_Park__FiP16_C" "x2c_Clarke_Park__FiP32_C" "x2c_Clarke_Park__Float32_C"];
    files = [files,  "x2c_Clarke_Park__FiP16_C.c" "x2c_Clarke_Park__FiP32_C.c" "x2c_Clarke_Park__Float32_C.c"];
    names = [names,  "x2c_Park_Clarke__FiP16_C" "x2c_Park_Clarke__FiP32_C" "x2c_Park_Clarke__Float32_C"];
    files = [files,  "x2c_Park_Clarke__FiP16_C.c" "x2c_Park_Clarke__FiP32_C.c" "x2c_Park_Clarke__Float32_C.c"];
    names = [names,  "x2c_Park_inv_MCH_FiP16_C" "x2c_Park_inv_MCH_FiP32_C" "x2c_Park_inv_MCH_Float32_C"];
    files = [files,  "x2c_Park_inv_MCH_FiP16_C.c" "x2c_Park_inv_MCH_FiP32_C.c" "x2c_Park_inv_MCH_Float32_C.c"];
    names = [names,  "x2c_Park_MCHP_FiP16_C" "x2c_Park_MCHP_FiP32_C" "x2c_Park_MCHP_Float32_C"];
    files = [files,  "x2c_Park_MCHP_FiP16_C.c" "x2c_Park_MCHP_FiP32_C.c" "x2c_Park_MCHP_Float32_C.c"];
    names = [names,  "x2c_Perturbation_FiP16_C" "x2c_Perturbation_FiP32_C" "x2c_Perturbation_Float32_C" "x2c_Perturbation_Float64_C"];
    files = [files,  "x2c_Perturbation_FiP16_C.c" "x2c_Perturbation_FiP32_C.c" "x2c_Perturbation_Float32_C.c" "x2c_Perturbation_Float64_C.c"];
    names = [names,  "x2c_RandomGen_FiP16_C" "x2c_RandomGen_FiP32_C" "x2c_RandomGen_Float32_C" "x2c_RandomGen_Float64_C"];
    files = [files,  "x2c_RandomGen_FiP16_C.c" "x2c_RandomGen_FiP32_C.c" "x2c_RandomGen_Float32_C.c" "x2c_RandomGen_Float64_C.c"];
    names = [names,  "x2c_SquareGen_FiP16_C" "x2c_SquareGen_FiP32_C" "x2c_SquareGen_Float32_C" "x2c_SquareGen_Float64_C"];
    files = [files,  "x2c_SquareGen_FiP16_C.c" "x2c_SquareGen_FiP32_C.c" "x2c_SquareGen_Float32_C.c" "x2c_SquareGen_Float64_C.c"];
    names = [names,  "x2c_SVM_MCHP_FiP32_C" "x2c_SVM_MCHP_FiP16_C" "x2c_SVM_MCHP_Float32_C"];
    files = [files,  "x2c_SVM_MCHP_FiP32_C.c" "x2c_SVM_MCHP_FiP16_C.c" "x2c_SVM_MCHP_Float32_C.c"];
    files = [files, "x2c_Utils.c"];
    flag = "c";
    loadername = "loader_x64.sce";
    libname = "MCHP_x64";
    ldflags = fullfile(SCI, "bin", "scicos.lib");
    cflags = "-I" + fullfile(SCI, "modules", "scicos_blocks", "includes") + " -I" + fullfile(SCI, "modules", "scicos", "includes") + " -I" + fullfile(X2C_ROOT, "Controller", "Common") + " -I" + fullfile(X2C_LIB_PATH, "Controller", "src") + " -I" + fullfile(X2C_LIB_PATH, "Controller", "inc");

    // Support for Scilab 5 build in different directory
    if isMajorVersionLessThan(6) then
        scilab5_path = fullfile(X2C_LIB_PATH, "Scilab5");
        if ~isdir(scilab5_path) then
            mkdir(scilab5_path);
        end
        // copy C source files
        num_files = size(files, 2);
        for i = 1:num_files
            copyfile(files(i), scilab5_path);
        end
        // switch to Scilab 5 directory to start build there
        cd(scilab5_path);
    end

    // build library
    ilib_for_link(names, files, [], flag, "", loadername, libname, ldflags, cflags);

    // delete temporary C files for Scilab 5 build
    if isMajorVersionLessThan(6) then
        mdelete(fullfile(scilab5_path, "*.c"));
    end
    // delete temporary files
    if isdir("Debug") then
      rmdir("Debug","s");
    end
    if isdir("Release") then
      rmdir("Release","s");
    end
    mdelete("Makelib.mak")

    // create "is-compiled" marker
    currentTime=clock();
    save("Library_is_compiled_for_x64.hdf5", "currentTime");

    mprintf("Library MCHP for x64 system built.\n");

catch
    mprintf("Error building library MCHP for x64 system: %s\n", lasterror());
end
