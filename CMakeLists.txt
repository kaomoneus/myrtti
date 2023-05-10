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

cmake_minimum_required(VERSION 3.12)
project(rtti)

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set(RTTI_SHARE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/share )

if (NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
    set(CMAKE_CXX_FLAGS "-Werror")
else()
    # Use standard conforming preprocessor when compiling with MSVC.
    set(CMAKE_CXX_FLAGS "/Zc:preprocessor")
endif()

option(MYRTTI_ENABLE_CLANG_PLUGIN "Enable clang plugin (not implemented yet)" OFF)
option(MYRTTI_CLANG_ROOT "Root to clang and llvm dirs (required for clang plugin only).")

add_subdirectory (src/myrtti)
add_subdirectory (src/demo)

if (MYRTTI_ENABLE_CLANG_PLUGIN)
    add_subdirectory (src/clang-plugin)
endif()

add_subdirectory (tests)
