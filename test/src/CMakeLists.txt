# Now simply link against gtest or gtest_main as needed. Eg
file(GLOB TEST_SRC_FILES *.cpp)
file(GLOB DEPS_SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM DEPS_SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/inc/ )

include_directories( ${INCLUDE_DIRS} )

add_executable(player_test player_test.cpp ${DEPS_SRC_FILES})
add_executable(monty_hall_test monty_hall_test.cpp ${DEPS_SRC_FILES})
target_link_libraries(player_test gmock_main)
target_link_libraries(monty_hall_test gmock_main)
add_test(NAME player_test_suite COMMAND player_test)
add_test(NAME monty_hall_test_suite COMMAND monty_hall_test)
