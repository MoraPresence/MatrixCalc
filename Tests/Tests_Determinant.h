// Copyright 2022 mora

#include "help_for_tests.h"

/*****************************************************************************/
// 7) подсчёт определителя матрицы - 1б.                                     //
/*****************************************************************************/
TEST_F(matrix_elementsTests, determinant_matrix) {
    Matrix<double, 4, 4> m01 =
            {1, 0, 2, -1, 3, 0, 0, 5, 2, 1, 4, -3, 1, 0, 5, 0};

    auto res = m01.getDeterminant(4);;

    EXPECT_EQ(res, 30);
}
