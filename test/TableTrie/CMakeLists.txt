cmake_minimum_required(VERSION 3.7)

set(TEST_NAME tabletrie)

add_executable(${TEST_NAME} main.cpp)

set(LINK_FILES
        gtest
        gtest_main
        pthread
        )

target_link_libraries(${TEST_NAME} ${LINK_FILES})

add_test(
    NAME ${TEST_NAME}
    COMMAND $<TARGET_FILE:${TEST_NAME}>
    )

# run with: ctest -L sample
set_property(
    TEST ${TEST_NAME}
    PROPERTY LABELS all ${TEST_NAME}
    )
