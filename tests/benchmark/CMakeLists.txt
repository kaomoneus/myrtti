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

set(BENCHMARK_TARGET myrtti_benchamrk)

find_package(benchmark REQUIRED)

macro(benchmark_frtti benchmark_name)
    add_executable(${benchmark_name} ${benchmark_name}.cpp)
    target_link_libraries(${benchmark_name} benchmark::benchmark myrtti_frtti)
    target_compile_options(${benchmark_name} PRIVATE "-frtti" ${ARGN})
endmacro()

macro(benchmark_fnortti benchmark_name)
    add_executable(${benchmark_name} ${benchmark_name}.cpp)
    target_link_libraries(${benchmark_name} benchmark::benchmark myrtti)
    target_compile_options(${benchmark_name} PRIVATE "-fno-rtti" ${ARGN})
endmacro()

macro(benchmark_profile benchmark_name)
    add_executable(${benchmark_name} ${benchmark_name}.cpp)
    target_link_libraries(${benchmark_name} benchmark::benchmark myrtti_profile)
    target_compile_options(${benchmark_name} PRIVATE -fno-rtti -g -pg ${ARGN})
    target_link_options(${benchmark_name} PRIVATE -fno-rtti -g -pg)
endmacro()

macro(benchmark_disasm benchmark_name)
    add_executable(${benchmark_name} ${benchmark_name}.cpp)
    target_link_libraries(${benchmark_name} benchmark::benchmark myrtti)
    target_compile_options(${benchmark_name} PRIVATE "-fno-rtti" ${ARGN})

    add_custom_target(${benchmark_name}_ll
        DEPENDS myrtti
        COMMAND ${CMAKE_CXX_COMPILER} -std=c++17 -S -emit-llvm -O3
        ${CMAKE_CURRENT_SOURCE_DIR}/${benchmark_name}.cpp -I${CMAKE_SOURCE_DIR}/src/myrtti/include
        -o ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${benchmark_name}.ll
    )
    add_custom_target(${benchmark_name}_s
        DEPENDS myrtti
        COMMAND ${CMAKE_CXX_COMPILER} -std=c++17 -S -O3
        ${CMAKE_CURRENT_SOURCE_DIR}/${benchmark_name}.cpp -I${CMAKE_SOURCE_DIR}/src/myrtti/include
        -o ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${benchmark_name}.s
    )
endmacro()

function(benchmark_plot benchmark_name)
    set(REPORT_FILE ${benchmark_name}.json)
    set(PLOT_FILE ${RTTI_SHARE_OUTPUT_DIRECTORY}/${benchmark_name}.png)
    set(REQUIREMENTS ${CMAKE_CURRENT_SOURCE_DIR}/plotmaker/requirements.txt)
    set(PLOT_MAKER ${CMAKE_CURRENT_SOURCE_DIR}/plotmaker/plotmaker.py)

    if (PLOTS_ENABLED)
        add_custom_command(
            COMMENT "Running benchmark '${benchmark_name}'..."

            DEPENDS ${benchmark_name}
            OUTPUT ${REPORT_FILE}
            COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${benchmark_name}
                    --benchmark_out_format=json
                    --benchmark_out=${REPORT_FILE}
        )
        add_custom_command(
            COMMENT "Checking requirements..."

            DEPENDS ${REQUIREMENTS}

            OUTPUT .requirements_installed
            COMMAND ${PYTHON} -m venv .venv
            COMMAND .venv/bin/pip3 install -r ${REQUIREMENTS}
            COMMAND touch .requirements_installed
        )
        add_custom_command(
            COMMENT "Making plot for benchmark '${REPORT_FILE}'..."

            OUTPUT ${PLOT_FILE}
            DEPENDS ${REPORT_FILE} .requirements_installed ${PLOT_MAKER}
            COMMAND .venv/bin/python3 ${PLOT_MAKER}
                --benchmark=${REPORT_FILE}
                --output=${PLOT_FILE}
        )
        add_custom_target(
            ${benchmark_name}_plot
            DEPENDS ${PLOT_FILE}
        )

        set_property(
            TARGET ${benchmark_name}_plot
            APPEND
            PROPERTY ADDITIONAL_CLEAN_FILES
                .requirements_installed
                ${PLOT_FILE}
                .venv
                ${REPORT_FILE}
        )
    endif()
endfunction()

find_program(PYTHON python3)

set (PLOTS_ENABLED OFF)
if (PYTHON)
    set(PLOTS_ENABLED ON)
    message("Found python3, plots are enabled.")
else()
    message("Unable to find python3, plots will be disabled.")
endif()


benchmark_frtti(compare_casts)
# benchmark_frtti(compare_casts -DDEBUG_REPORT_CROSS_PTRS)
benchmark_plot(compare_casts)

benchmark_frtti(rtti_ops)

benchmark_frtti(legacy_casts)
benchmark_fnortti(myrtti_casts)

benchmark_disasm(myrtti_to_base)
