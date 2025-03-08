cmake_minimum_required(VERSION 3.28)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# List of source files for the test executable
set(TEST_SOURCE_FILES runAllTests.cpp TodoListTest.cpp ../Activity.cpp ../TodoList.cpp)

# Create test executable
add_executable(runLabProgrammazioneTest ${TEST_SOURCE_FILES})
target_link_libraries(runLabProgrammazioneTest gtest gtest_main)