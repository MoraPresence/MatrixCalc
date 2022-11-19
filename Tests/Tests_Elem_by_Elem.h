// Copyright 2022 mora

#include "help_for_tests.h"

/*****************************************************************************/
// 3) поэлементное сложение/вычитание/умножение                              //
// объектов одинаковой размерности - 1б;                                     //
/*****************************************************************************/
TEST_F(matrix_elementsTests, element_by_element_mult_matrix) {
    auto res = matrix * matrix;

    std::array<double, 9> test = {0, 1, 4, 9, 16, 25, 36, 49, 64};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, element_by_element_mult_vectorRow) {
    MatrixRow res = matrixRow * matrixRow;
    std::array<double, 3> test = {0, 1, 4};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, element_by_element_mult_vectorColumn) {
    MatrixColumn res = matrixColumn * matrixColumn;
    std::array<double, 3> test = {0, 9, 36};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, element_by_element_add_matrix) {
    auto res = matrix + matrix;
    std::array<double, 9> test = {0, 2, 4, 6, 8, 10, 12, 14, 16};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, element_by_element_add_vectorRow) {
    MatrixRow res = matrixRow + matrixRow;
    std::array<double, 3> test = {0, 2, 4};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, element_by_element_add_vectorColumn) {
    MatrixColumn res = matrixColumn + matrixColumn;
    std::array<double, 3> test = {0, 6, 12};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, element_by_element_sub_matrix) {
    auto res = matrix - matrix;

    EXPECT_TRUE(std::all_of(res.begin(), res.end(),
                            [](int i) { return i == 0; }));
}

TEST_F(matrix_elementsTests, element_by_element_sub_vectorRow) {
    MatrixRow res = matrixRow - matrixRow;

    EXPECT_TRUE(std::all_of(res.begin(),
                            res.end(), [](int i) { return i == 0; }));
}

TEST_F(matrix_elementsTests, element_by_element_sub_vectorColumn) {
    MatrixColumn res = matrixColumn - matrixColumn;

    EXPECT_TRUE(std::all_of(res.begin(), res.end(),
                            [](int i) { return i == 0; }));
}
