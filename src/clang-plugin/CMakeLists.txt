# Copyright 2023 Stepan Dyatkovskiy at Kaspersky Lab.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# There is no document how to define cmake for clang plugin.
# So we ought to leave some credits to:
#   Alex Denisov: https://github.com/AlexDenisov/ToyClangPlugin
#   Yoshimasa Niwa: https://gist.github.com/niw/d46da15ba2904fbf0e9ea0549d8907f6

# Also consider forsing to use Clang as a compiler
# if (MYRTTI_CLANG_ROOT AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))

if (MYRTTI_CLANG_ROOT)

    message("Using CLANG dir: ${MYRTTI_CLANG_ROOT}")

    set(LLVM_ROOT "${Clang_ROOT}")
    set(Clang_ROOT "${Clang_ROOT}")

    find_package(LLVM REQUIRED PATHS ${MYRTTI_CLANG_ROOT} NO_DEFAULT_PATH)
    find_package(Clang REQUIRED PATHS ${MYRTTI_CLANG_ROOT} NO_DEFAULT_PATH)

    list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
    # Use `add_llvm_...` functions.
    include(AddLLVM)
    # Set compiler flags.
    include(HandleLLVMOptions)
    # Use LLVM and clang headers.
    include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})

    # FIXME: This part of code doesn't work. Linker fails with syntax error on line 1.
    #
    # if( NOT MSVC ) # MSVC mangles symbols differently, and
    #                # myrtti_plugin.exports contains C++ symbols.
    #     if( NOT LLVM_REQUIRES_RTTI )
    #         if( NOT LLVM_REQUIRES_EH )
    #             set(LLVM_EXPORTED_SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/impl/myrtti_plugin.exports)
    #         endif()
    #     endif()
    # endif()

    add_llvm_library(myrtti_clang MODULE impl/myrtti_plugin.cpp PLUGIN_TOOL clang)

else()

    message("clang plugin is disabled. There are following reasons:")
    if (NOT MYRTTI_CLANG_ROOT)
        message("    * in order to enable myrtti_plugin, you should provide MYRTTI_CLANG_ROOT")
    endif()

    # if (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    #     message("    * in order to enable myrtti_plugin, you should use clang as a compiler. Currently you use: ${MAKE_CXX_COMPILER_ID}")
    # endif()

endif()
