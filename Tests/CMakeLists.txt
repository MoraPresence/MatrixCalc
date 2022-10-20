cmake_minimum_required(VERSION 3.0)
project(MatrixCalc_tests CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} tests.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_MATRIX_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${INTERFACE_MATRIX_LIBRARIES} gtest_main)