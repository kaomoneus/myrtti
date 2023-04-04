cmake_minimum_required(VERSION 3.12)
project(rtti)

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

set(CMAKE_CXX_FLAGS "-Werror")

option(MYRTTI_ENABLE_TESTS "Enable tests" ON)
option(MYRTTI_ENABLE_TESTS_BENCHMARK "Enable benchmark test (requires google/benchmark lib to be installed)" OFF)

option(MYRTTI_ENABLE_CLANG_PLUGIN "Enable clang plugin (not implemented yet)" OFF)
option(MYRTTI_CLANG_ROOT "Root to clang and llvm dirs (required for clang plugin only).")

add_subdirectory (src/myrtti)
add_subdirectory (src/demo)

if (MYRTTI_ENABLE_CLANG_PLUGIN)
    add_subdirectory (src/clang-plugin)
endif()

if (MYRTTI_ENABLE_TESTS)
    add_subdirectory (tests)
endif()
