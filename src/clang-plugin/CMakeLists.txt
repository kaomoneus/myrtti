# There is no document how to define cmake for clang plugin.
# So we ought to leave some credits to:
#   Alex Denisov: https://github.com/AlexDenisov/ToyClangPlugin
#   Yoshimasa Niwa: https://gist.github.com/niw/d46da15ba2904fbf0e9ea0549d8907f6
if (MYRTTI_CLANG_ROOT)

    message("Using CLANG dir: ${MYRTTI_CLANG_ROOT}")

    set(LLVM_ROOT "${Clang_ROOT}")
    set(Clang_ROOT "${Clang_ROOT}")

    find_package(LLVM REQUIRED PATHS ${MYRTTI_CLANG_ROOT} NO_DEFAULT_PATH)
    find_package(Clang REQUIRED PATHS ${MYRTTI_CLANG_ROOT} NO_DEFAULT_PATH)

    # Use given `clang` toolchain.
    set(CMAKE_CXX_COMPILER "${LLVM_TOOLS_BINARY_DIR}/clang++")
    set(CMAKE_C_COMPILER "${LLVM_TOOLS_BINARY_DIR}/clang")

    list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
    # Use `add_llvm_...` functions.
    include(AddLLVM)
    # Set compiler flags.
    include(HandleLLVMOptions)
    # Use LLVM and clang headers.
    include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})


    macro(add_clang_plugin name)
        set (srcs ${ARGN})

        add_library( ${name} SHARED ${srcs} )

        target_include_directories(${name} PUBLIC ${LLVM_INCLUDE_DIRS})
        if (LLVM IN_LIST LLVM_AVAILABLE_LIBS)
            target_link_libraries(${name} LLVM clangTooling)
        else()
            target_link_libraries(${name} LLVMSupport clangTooling)
        endif()

        set_target_properties( ${name} PROPERTIES LINK_FlAGS
            "-exported_symbols_list ${name}.exports")

        foreach (user_lib ${USER_LIBS})
            target_link_libraries( ${name} ${user_lib} )
        endforeach()

    endmacro(add_clang_plugin)

    add_llvm_library(myrtti_clang MODULE
        impl/main.cpp
        PLUGIN_TOOL clang
    )

    # add_clang_plugin(myrtti_clang
    #     impl/main.cpp
    # )

endif()
