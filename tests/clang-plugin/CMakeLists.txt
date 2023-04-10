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

find_program(LIT lit)
find_program(FILECHECK FileCheck)
if(LIT AND FILECHECK)
    message("clang_plugin tests are enabled.")

    add_custom_target(clang-plugin
        DEPENDS myrtti_clang
        COMMAND ${CMAKE_COMMAND} -E env
        MYRTTI_CLANG_ROOT=${MYRTTI_CLANG_ROOT}
        FILECHECK=${FILECHECK}
        MYRTTI_BIN_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        MYRTTI_LIB_DIR=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        "${LIT}"
        -v ${CMAKE_CURRENT_SOURCE_DIR}
        # TODO: set custom LIT artifacts
        # -o ${CMAKE_CURRENT_BINARY_DIR}
    )

    # TODO
else()
    if (NOT LIT)
        message("'lit' is not installed. clang_plugin tests are disabled."
                " you can install it with pip.")
    endif()

    if(NOT FILECHECK)
        message(
            "'FileCheck' is not installed. Either build it from LLVM"
            " source, or you can install it within llvm package sometimes."
        )
    endif()

    message("clang-plugin tests are disabled due to absence or required tools.")
    message("    env: $ENV{PATH}")
endif()