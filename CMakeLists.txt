cmake_minimum_required(VERSION 3.10)
project(lab2) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)


add_library(${PROJECT_NAME}_lib src/bitstring.cpp)
add_executable(${PROJECT_NAME}_exe main.cpp)

target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)


enable_testing()

add_executable(${PROJECT_NAME}_tests test/tests_l2.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)

add_test(NAME ${PROJECT_NAME}_MyProjectTests COMMAND ${PROJECT_NAME}_tests)
