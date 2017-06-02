cmake_minimum_required(VERSION 3.6)
project(base_alumnos)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    base/DiccHashCerrado.hpp
    base/Lista.h
    base/tests.cpp
    data/gauss.txt
    data/libretas.txt
    data/uniforme.txt)

add_executable(base_alumnos ${SOURCE_FILES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runTests base/tests.cpp base/DiccHashCerrado.hpp)

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)