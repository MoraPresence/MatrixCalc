cmake_minimum_required(VERSION 3.0)
project(MatrixCalc_tests CXX)

set(CMAKE_CXX_STANDARD 17)

if (BUILD_FOR_TEST)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${MATRIX_LIBRARIES} GTest::gtest_main)

enable_testing()
add_test(NAME MatrixCalc_tests COMMAND MatrixCalc_tests)
