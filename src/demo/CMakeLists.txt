set(BASIC basic_demo)
set(VISITOR visitor_demo)

add_executable(
    ${BASIC}
    impl/basic_demo.cpp
)

target_link_libraries(
    ${BASIC}
    myrtti
)

add_executable(
    ${VISITOR}
    impl/visitor_demo.cpp
)

target_link_libraries(
    ${VISITOR}
    myrtti
)
