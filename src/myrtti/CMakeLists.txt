set(TARGET myrtti)

add_library(
    ${TARGET} STATIC
    impl/myrtti/class_id.cpp
    impl/myrtti/hierarchy.cpp
    impl/myrtti/runtime.cpp
    impl/rtti_lib.cpp
)

target_compile_options(${TARGET} PRIVATE "-fno-rtti")

set(libmyrtti_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(${TARGET} PUBLIC ${libmyrtti_INCLUDE})
