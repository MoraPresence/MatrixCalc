// Copyright 2022 mora

#include "help_for_tests.h"

/*****************************************************************************/
// 4) умножение числа на матрицу, вектора на матрицу,                        //
// матрицы на вектор и матрицы на матрицу - 1б;                              //
/*****************************************************************************/
TEST_F(matrix_elementsTests, mult_matrix_num) {
    auto res = matrix * 2;
    std::array<double, 9> test = {0, 2, 4, 6, 8, 10, 12, 14, 16};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, mult_num_matrix) {
    auto res = 2. * matrix;
    std::array<double, 9> test = {0, 2, 4, 6, 8, 10, 12, 14, 16};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, mult_row_matrix) {
    MatrixRow res = matrixRow * matrix;
    std::array<double, 3> test = {15, 18, 21};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, mult_matrix_column) {
    MatrixColumn res = matrix * matrixColumn;
    std::array<double, 3> test = {15, 42, 69};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, mult_matrix_matrix) {
    // да, я знаю, что основная операция произведения != произведение Адамара
    // просто так красивше...
    auto res = matrix.multiply(matrix);
    std::array<double, 9> test = {15, 18, 21, 42, 54, 66, 69, 90, 111};

    EXPECT_TRUE(res == test);
}
