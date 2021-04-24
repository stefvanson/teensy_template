CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
SET(PROJECT_NAME tests)

# Gather all the test files
FILE(GLOB_RECURSE TEST_FILES "*.cpp")
INCLUDE_DIRECTORIES(/usr/local/include)

# Target for compiling the tests
ADD_EXECUTABLE(tests ${TEST_FILES})

# Compiler/linker flags for testing (override the ones for the embedded target)
SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_CXX_FLAGS "-std=gnu++11")
SET(CMAKE_EXE_LINKER_FLAGS)
TARGET_LINK_LIBRARIES(tests gtest gmock gtest_main pthread)

# Target 'test' for running the tests
ADD_CUSTOM_TARGET(test)
ADD_DEPENDENCIES(test tests)
ADD_CUSTOM_COMMAND(TARGET test
                   COMMAND ${CMAKE_BINARY_DIR}/test/tests)
