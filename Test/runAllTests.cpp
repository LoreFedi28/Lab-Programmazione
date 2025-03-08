#include "gtest/gtest.h"

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv); // Initialize GoogleTest framework
    return RUN_ALL_TESTS(); // Run all test cases
}