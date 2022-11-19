// Copyright 2022 mora

#include "help_for_tests.h"

/*****************************************************************************/
// 2) возможность создания матрицы из векторов или чисел, вектора из чисел;  //
/*****************************************************************************/
TEST_F(matrix_elementsTests, creating_matrix_from_numbers) {
    Matrix<double, 3, 3> m = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    EXPECT_TRUE(m == matrix);
}

TEST_F(matrix_elementsTests, creating_matrix_from_vectors) {
    Matrix<double, 3, 3> m;
    MatrixRow<double, 3> mRow1;
    MatrixRow<double, 3> mRow2;
    MatrixRow<double, 3> mRow3;

    mRow1 = {0, 1, 2};
    mRow2 = {3, 4, 5};
    mRow3 = {6, 7, 8};


    m = {mRow1, mRow2, mRow3};

    EXPECT_TRUE(m == matrix);
}

TEST_F(matrix_elementsTests, creating_vector_from_numbers) {
    MatrixRow<double, 3> row = {0, 1, 2};

    EXPECT_TRUE(row == matrixRow);
}
