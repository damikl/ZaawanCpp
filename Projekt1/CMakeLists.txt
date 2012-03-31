cmake_minimum_required(VERSION 2.6)
project(ToDos)
enable_testing()
find_package (Threads)
include_directories(
  "${ToDos_SOURCE_DIR}/src"
  "${ToDos_SOURCE_DIR}")

# Where Google Test's libraries can be found.
link_directories("${ToDos_BINARY_DIR}/src")

add_executable(TodosList task.cpp todos.cpp datamanager.cpp cmdinterface.cpp)

add_executable(TaskTest task.cpp task1_unittest.cpp)
add_executable(TodosTest todos.cpp task.cpp todos1_unittest.cpp)
add_executable(DataManagerTest todos.cpp task.cpp datamanager.cpp datamanager1_unittest.cpp)

target_link_libraries(TaskTest gtest gtest_main pthread)
target_link_libraries(TodosTest gtest gtest_main pthread)
target_link_libraries(DataManagerTest gtest gtest_main pthread)

add_test(NAME Task COMMAND TaskTest)
add_test(NAME Todos COMMAND TodosTest)
add_test(NAME DataManager COMMAND DataManagerTest)
