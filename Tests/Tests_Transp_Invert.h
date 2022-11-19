// Copyright 2022 mora

#include "help_for_tests.h"

/*****************************************************************************/
// 6) получение транспонированной и обратной матриц - 1б;                    //
/*****************************************************************************/
TEST_F(matrix_elementsTests, transponce_matrix) {
    auto res = matrix.transpose();
    std::array<double, 9> test = {0, 3, 6, 1, 4, 7, 2, 5, 8};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, inverted_matrix) {
    Matrix<double, 3, 3> m01 = {1, 2, 3, 2, 3, 3, 2, 2, 2};

    auto res = m01.invert();
    std::array<double, 9> test = {-0, -1, 1.5, -1, 2, -1.5, 1, -1, 0.5};

    EXPECT_TRUE(res == test);
}
