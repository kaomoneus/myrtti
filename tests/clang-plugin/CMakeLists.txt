find_program(LIT lit)
find_program(FILECHECK FileCheck)
if(LIT AND FILECHECK)
    message("clang_plugin tests are enabled.")

    add_custom_target(clang-plugin
        DEPENDS myrtti_clang
        COMMAND ${CMAKE_COMMAND} -E env
        MYRTTI_CLANG_ROOT=${MYRTTI_CLANG_ROOT}
        FILECHECK=${FILECHECK}
        MYRTTI_BIN_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        MYRTTI_LIB_DIR=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        "${LIT}"
        -v ${CMAKE_CURRENT_SOURCE_DIR}
        # TODO: set custom LIT artifacts
        # -o ${CMAKE_CURRENT_BINARY_DIR}
    )

    # TODO
else()
    if (NOT LIT)
        message("'lit' is not installed. clang_plugin tests are disabled."
                " you can install it with pip.")
    endif()

    if(NOT FILECHECK)
        message(
            "'FileCheck' is not installed. Either build it from LLVM"
            " source, or you can install it within llvm package sometimes."
        )
    endif()

    message("clang-plugin tests are disabled due to absence or required tools.")
    message("    env: $ENV{PATH}")
endif()