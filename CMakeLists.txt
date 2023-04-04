cmake_minimum_required(VERSION 3.12)
project(rtti)

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

set(CMAKE_CXX_FLAGS "-fno-rtti")

option(MYRTTI_CLANG_ROOT "Root to clang and llvm dirs.")
option(MYRTTI_ENABLE_TESTS "Enable tests" ON)

add_subdirectory (src/myrtti)
add_subdirectory (src/demo)
add_subdirectory (src/clang-plugin)
add_subdirectory (tests)
