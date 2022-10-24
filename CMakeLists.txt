cmake_minimum_required(VERSION 3.0)
project(MatrixCalc CXX)

option(BUILD_FOR_TEST "Build for test" OFF)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(MatrixBase)

add_subdirectory(Tests)
