// Copyright 2022 mora

#include "help_for_tests.h"

/*****************************************************************************/
// 1) обращение по индексам к элементам, извлечение диагонали,               //
// строки или столбца - 1б                                                   //
// (после модификации исходной матрицы                                       //
// извлечённые элементы меняться не должны);                                 //
/*****************************************************************************/
TEST_F(matrix_elementsTests, access_by_index_matrix) {
    Matrix<double, 3, 3> m = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    EXPECT_TRUE(m == matrix);
}

TEST_F(matrix_elementsTests, access_by_index_matrixRow) {
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(*matrix(0, i), *matrixRow(i));
    }
}

TEST_F(matrix_elementsTests, access_by_index_matrixColumn) {
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(*matrix(i, 0), *matrixColumn(i));
    }
}

TEST_F(matrix_elementsTests, get_diagonal) {
    auto diagonal = matrix.getDiagonal();

    EXPECT_EQ(*diagonal(0), 0);
    EXPECT_EQ(*diagonal(1), 4);
    EXPECT_EQ(*diagonal(2), 8);
}

TEST_F(matrix_elementsTests, get_row) {
    auto row = matrix.getRow(0);

    EXPECT_TRUE(row == matrixRow);
}

TEST_F(matrix_elementsTests, get_column) {
    auto column = matrix.getColumn(0);

    EXPECT_TRUE(column == matrixColumn);
}

TEST_F(matrix_elementsTests, retrieved_elements_do_not_change) {
    auto column = matrix.getColumn(0);

    *column(0) = 100;
    *column(1) = 101;

    EXPECT_EQ(*matrix(0, 0), 0);
    EXPECT_EQ(*matrix(1, 0), 3);
}
