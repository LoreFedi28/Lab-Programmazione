cmake_minimum_required(VERSION 3.29)
project(LabProgrammazione)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test)

# Main executable (application)
add_executable(LabProgrammazione main.cpp Activity.cpp TodoList.cpp)

# Link Google Test to unit tests
target_link_libraries(runLabProgrammazioneTest gtest gtest_main)
