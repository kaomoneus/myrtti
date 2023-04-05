set(BENCHMARK_TARGET myrtti_benchamrk)

find_package(benchmark REQUIRED)

macro(benchmark_frtti benchmark_name)
    add_executable(${benchmark_name} ${benchmark_name}.cpp)
    target_link_libraries(${benchmark_name} benchmark::benchmark myrtti_frtti)
    target_compile_options(${benchmark_name} PRIVATE "-frtti")
endmacro()

macro(benchmark_fnortti benchmark_name)
    add_executable(${benchmark_name} ${benchmark_name}.cpp)
    target_link_libraries(${benchmark_name} benchmark::benchmark myrtti)
    target_compile_options(${benchmark_name} PRIVATE "-fno-rtti")
endmacro()

macro(benchmark_profile benchmark_name)
    add_executable(${benchmark_name} ${benchmark_name}.cpp)
    target_link_libraries(${benchmark_name} benchmark::benchmark myrtti_profile)
    target_compile_options(${benchmark_name} PRIVATE -fno-rtti -g -pg)
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

benchmark_frtti(compare_casts)
benchmark_frtti(rtti_ops)

benchmark_frtti(legacy_casts)
benchmark_fnortti(myrtti_casts)

benchmark_disasm(myrtti_to_base -DDEBUG_REPORT_CROSS_PTRS)
