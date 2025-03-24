set(TESTS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests")

file(GLOB TESTS "${TESTS_PATH}/*" LIST_DIRECTORIES true)

foreach (TEST_DIR ${TESTS})
    cmake_path(GET TEST_DIR FILENAME TEST_NAME)
#    list(INSERT CMAKE_MODULE_PATH 0 ${TEST_DIR})
#    message("${CMAKE_MODULE_PATH}")
#    include("CMakeLists.txt" OPTIONAL RESULT_VARIABLE FOUND)

    if (EXISTS "${TEST_DIR}/CMakeLists.txt")
        add_subdirectory(${TEST_DIR})
#    add_custom_command(
#            TARGET ${TEST_NAME}
#            COMMENT "Run ${TEST_NAME} test"
#            POST_BUILD
#            COMMAND ${TEST_NAME}
#    )
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    else ()
        message("Test ${TEST_NAME} doesn't have CMakeLists.txt")
    endif ()

#    list(POP_FRONT CMAKE_MODULE_PATH)
endforeach ()