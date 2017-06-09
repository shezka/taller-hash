cmake_minimum_required(VERSION 3.6)
project(tallerHash)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    base_alumnos/base/DiccHashCerrado.hpp
    base_alumnos/base/Lista.h
    base_alumnos/base/tests.cpp)

add_executable(tallerHash ${SOURCE_FILES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runTests base_alumnos/base/tests.cpp base_alumnos/base/DiccHashCerrado.hpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)