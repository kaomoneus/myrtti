set(TARGET demo)

add_executable(
    ${TARGET}
    impl/main.cpp
)

target_link_libraries(
    ${TARGET}

    libmyrtti
)
