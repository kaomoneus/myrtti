set(TARGET libmyrtti)

add_library(
    ${TARGET} STATIC
    impl/rtti_lib.cpp
    impl/hierarchy.cpp
)

set(libmyrtti_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(${TARGET} PUBLIC ${libmyrtti_INCLUDE})
