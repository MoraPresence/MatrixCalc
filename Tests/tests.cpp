// Copyright 2022 mora

#include <gtest/gtest.h>
#include "Matrix.h"

class matrix_elementsTests : public testing::Test {
protected:
    void SetUp() override {
        matrix = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        matrixRow = {0, 1, 2};
        matrixColumn = {0, 3, 6};
    }

    Matrix<double, 3, 3> matrix;
    MatrixRow<double, 3> matrixRow;
    MatrixColumn<double, 3> matrixColumn;
};

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

    EXPECT_TRUE(std::all_of(res.begin(), res.end(), [](int i) { return i == 0; }));
}

TEST_F(matrix_elementsTests, element_by_element_sub_vectorRow) {
    MatrixRow res = matrixRow - matrixRow;

    EXPECT_TRUE(std::all_of(res.begin(), res.end(), [](int i) { return i == 0; }));
}

TEST_F(matrix_elementsTests, element_by_element_sub_vectorColumn) {
    MatrixColumn res = matrixColumn - matrixColumn;

    EXPECT_TRUE(std::all_of(res.begin(), res.end(), [](int i) { return i == 0; }));
}

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

/*****************************************************************************/
// 7) подсчёт определителя матрицы - 1б.                                     //
/*****************************************************************************/
TEST_F(matrix_elementsTests, determinant_matrix) {
    Matrix<double, 4, 4> m01 =
            {1, 0, 2, -1, 3, 0, 0, 5, 2, 1, 4, -3, 1, 0, 5, 0};

    auto res = m01.getDeterminant(4);;

    EXPECT_EQ(res, 30);
}

/*****************************************************************************/
// 8)- поддержка "слайсов, как в питоне" (на уровне методов,                  //
// т.к. операторы такой синтаксис не поддерживают).                          //
// В качестве примерного интерфейса можно опираться на то,                    //
// как это сделано в " аналоге numpy на C++"                                 //
// https://github.com/dpilger26/NumCpp -1б;                                   //
/*****************************************************************************/
TEST_F(matrix_elementsTests, matrix_slices) {
    Matrix<double, 4, 4> m01 =
            {1, 0, 2, -1, 3, 0, 0, 5, 2, 1, 4, -3, 1, 0, 5, 0};
    std::array<double, 2> test = {1, 0};
    auto slice = m01.slice(0, 2);
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(slice(i), test[i]);
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
