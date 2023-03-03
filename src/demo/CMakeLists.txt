set(BASIC basic_demo)

add_executable(
    ${BASIC}
    impl/basic_demo.cpp
)

target_link_libraries(
    ${BASIC}
    libmyrtti
)
