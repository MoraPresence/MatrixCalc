// Copyright 2022 mora

#include "help_for_tests.h"

/*****************************************************************************/
// 5) суммирование/вычитание числа и вектора/матрицы, матрицы и вектора      //
// (с возможностью выбора - по строкам/по столбцам) - 1б;                    //
/*****************************************************************************/
TEST_F(matrix_elementsTests, add_matrix_num) {
    auto res = matrix + 4;
    std::array<double, 9> test = {4, 5, 6, 7, 8, 9, 10, 11, 12};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, add_num_matrix) {
    auto res = 4. + matrix;
    std::array<double, 9> test = {4, 5, 6, 7, 8, 9, 10, 11, 12};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, sub_matrix_num) {
    auto res = matrix - 4;
    std::array<double, 9> test = {-4, -3, -2, -1, 0, 1, 2, 3, 4};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, add_row_num) {
    MatrixRow res = matrixRow + 4;
    std::array<double, 3> test = {4, 5, 6};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, add_num_row) {
    MatrixRow res = 4. + matrixRow;
    std::array<double, 3> test = {4, 5, 6};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, sub_row_num) {
    MatrixRow res = matrixRow - 4;
    std::array<double, 3> test = {-4, -3, -2};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, add_column_num) {
    MatrixColumn res = matrixColumn + 4;
    std::array<double, 3> test = {4, 7, 10};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, add_column_row) {
    MatrixColumn res = 4. + matrixColumn;
    std::array<double, 3> test = {4, 7, 10};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, sub_column_num) {
    MatrixColumn res = matrixColumn - 4;
    std::array<double, 3> test = {-4, -1, 2};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, add_matrix_row_line_by_line) {
    auto res = matrix + matrixRow;
    std::array<double, 9> test = {0, 2, 4, 3, 5, 7, 6, 8, 10};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, add_matrix_column_line_by_line) {
    auto res = matrix + matrixColumn;
    std::array<double, 9> test = {0, 1, 2, 6, 7, 8, 12, 13, 14};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, sub_matrix_row_line_by_line) {
    auto res = matrix - matrixRow;
    std::array<double, 9> test = {0, 0, 0, 3, 3, 3, 6, 6, 6};

    EXPECT_TRUE(res == test);
}

TEST_F(matrix_elementsTests, sub_matrix_column_line_by_line) {
    auto res = matrix - matrixColumn;
    std::array<double, 9> test = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    EXPECT_TRUE(res == test);
}
