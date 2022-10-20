cmake_minimum_required(VERSION 3.0)
project(MatrixCalc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS --coverage)

add_subdirectory(InterfaceMatrix)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${INTERFACE_MATRIX_INCLUDE_DIRS}
)

target_link_libraries(
        ${PROJECT_NAME}
        INTERFACE
        ${INTERFACE_MATRIX_LIBRARIES}
)
add_subdirectory(Tests)

enable_testing()
add_test(NAME MatrixCalc_tests COMMAND MatrixCalc_tests)