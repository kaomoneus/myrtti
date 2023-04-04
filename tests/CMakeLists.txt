if (MYRTTY_CLANG_ROOT)
    add_subdirectory(clang-plugin)
endif()

if (MYRTTI_ENABLE_TESTS_BENCHMARK)
    add_subdirectory(benchmark)
endif()