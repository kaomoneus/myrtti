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
