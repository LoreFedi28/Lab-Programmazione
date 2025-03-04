cmake_minimum_required(VERSION 3.29)
project(LabProgrammazione)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test)

add_executable(LabProgrammazione main.cpp
        Activity.cpp
        Activity.h
        TodoList.cpp
        TodoList.h
        Test/TodoListTest.cpp
        Test/runAllTests.cpp
)

target_link_libraries(LabProgrammazione gtest gtest_main)