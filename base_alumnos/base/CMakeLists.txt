cmake_minimum_required(VERSION 3.6)
project(base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    DiccHashCerrado.hpp
    Lista.h
    tests.cpp)

add_executable(base ${SOURCE_FILES})


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runTests tests.cpp DiccHashCerrado.hpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)