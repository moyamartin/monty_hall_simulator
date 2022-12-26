# Now simply link against gtest or gtest_main as needed. Eg
file(GLOB TEST_SRC_FILES *.cpp)

set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/inc/ )

include_directories( ${INCLUDE_DIRS} )

add_executable(hello_test ${TEST_SRC_FILES})
target_link_libraries(hello_test gmock_main)
add_test(NAME shared_test COMMAND hello_test)
