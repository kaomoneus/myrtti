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

set(TARGET myrtti)

set(LIBMYRTTI_SOURCES
    impl/myrtti/class_id.cpp
    impl/myrtti/hierarchy.cpp
    impl/myrtti/runtime.cpp
    impl/rtti_lib.cpp
)

set(libmyrtti_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${TARGET} STATIC ${LIBMYRTTI_SOURCES})
target_compile_options(${TARGET} PRIVATE "-fno-rtti")
target_include_directories(${TARGET} PUBLIC ${libmyrtti_INCLUDE})

add_library(${TARGET}_profile STATIC ${LIBMYRTTI_SOURCES})
target_compile_options(${TARGET}_profile PRIVATE -fno-rtti -g -pg)
target_link_options(${TARGET}_profile PRIVATE -fno-rtti -g -pg)
target_include_directories(${TARGET}_profile PUBLIC ${libmyrtti_INCLUDE})

# We need this library for comparison benchmarks
add_library(${TARGET}_frtti STATIC ${LIBMYRTTI_SOURCES})
target_compile_options(${TARGET}_frtti PRIVATE "-frtti")
target_include_directories(${TARGET}_frtti PUBLIC ${libmyrtti_INCLUDE})
