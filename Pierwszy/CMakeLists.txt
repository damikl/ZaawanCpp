cmake_minimum_required (VERSION 2.6)
project (Projekt1)
add_executable(Projekt1 number.cpp)

#Enable CMake's built-in testing subsystem:

# For make-based builds, defines make target named test.
# For Visual Studio builds, defines Visual Studio project named RUN_TESTS.
enable_testing()

#Compile an executable that will run your unit tests and link it with gtest #and gtest_main:

add_executable(runUnitTests
    number_unittests.cpp
)
target_link_libraries(runUnitTests gtest gtest_main)

#Add a test which runs this executable:

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)


