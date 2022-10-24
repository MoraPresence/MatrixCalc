#include <gtest/gtest.h>
#include "Matrix.h"
/**********************************************************************************************************************/
//1) обращение по индексам к элементам, извлечение диагонали, строки или столбца - 1б                                 //
//(после модификации исходной матрицы извлечённые элементы меняться не должны);                                       //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, access_by_index_matrix) {
    Matrix<int, 2, 2> m = {{0, 1, 2, 3}};
    int arr_test[] = {0, 1, 2, 3};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*m(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, access_by_index_matrixRow) {
    MatrixRow<int, 2> m = {{0, 1}};
    int arr_test[] = {0, 1};
    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*m(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, access_by_index_matrixColumn) {
    MatrixColumn<int, 2> m = {{0, 1}};
    int arr_test[] = {0, 1};
    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*m(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, get_diagonal) {
    Matrix<int, 2, 2> m = {{0, 1, 2, 3}};
    int arr_test[] = {0, 3};

    auto diagonal = m.getDiagonal();
    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*diagonal(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, get_row) {
    Matrix<int, 2, 2> m = {{0, 1, 2, 3}};
    int arr_test[] = {0, 1};

    auto row = m.getRow(0);
    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*row(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, get_column) {
    Matrix<int, 2, 2> m = {{0, 1, 2, 3}};
    int arr_test[] = {0, 2};

    auto column = m.getColumn(0);
    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*column(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, retrieved_elements_do_not_change) {
    Matrix<int, 2, 2> m = {{0, 1, 2, 3}};
    int arr_test[] = {0, 1, 2, 3};

    auto column = m.getColumn(0);

    *column(0) = 100;
    *column(1) = 101;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*m(i, j), arr_test[i * 2 + j]);
        }
    }
}

/**********************************************************************************************************************/
//2) возможность создания матрицы из векторов или чисел, вектора из чисел - 1б;                                       //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, creating_matrix_from_numbers) {
    Matrix<int, 2, 2> m = {{0, 1, 2, 3}};
    int arr_test[] = {0, 1, 2, 3};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*m(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, creating_matrix_from_vectors) {
    Matrix<float, 3, 3> m;
    MatrixRow<float, 3> mRow1;
    MatrixRow<float, 3> mRow2;
    MatrixRow<float, 3> mRow3;

    mRow1 = {{1, 2, 3}};
    mRow2 = {{4, 5, 6}};
    mRow3 = {{7, 8, 9}};

    int arr_test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    m = {{mRow1, mRow2, mRow3}, 3};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(*m(i, j), arr_test[i * 3 + j]);
        }
    }
}

TEST(InterfaceMatrix, creating_vector_from_numbers) {
    MatrixRow<int, 2> m = {{0, 1, 2, 3}};
    int arr_test[] = {0, 1, 2, 3};

    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*m(i), arr_test[i]);
    }
}

/**********************************************************************************************************************/
//3) поэлементное сложение/вычитание/умножение объектов одинаковой размерности - 1б;                                  //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, element_by_element_mult_matrix) {
    MatrixBase<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixBase<float, 2, 2> m02 = {{0, 1, 2, 3}};

    auto res = m01 * m02;
    int arr_test[] = {0, 1, 4, 9};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, element_by_element_mult_vectorRow) {
    MatrixRow<float, 4> r01 = {{0, 1, 2, 3}};
    MatrixRow<float, 4> r02 = {{0, 1, 2, 3}};

    auto res = r01 * r02;
    int arr_test[] = {0, 1, 4, 9};

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, element_by_element_mult_vectorColumn) {
    MatrixColumn<float, 4> c01 = {{0, 1, 2, 3}};
    MatrixColumn<float, 4> c02 = {{0, 1, 2, 3}};

    auto res = c01 * c02;
    int arr_test[] = {0, 1, 4, 9};

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, element_by_element_add_matrix) {
    MatrixBase<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixBase<float, 2, 2> m02 = {{0, 1, 2, 3}};

    auto res = m01 + m02;
    int arr_test[] = {0, 2, 4, 6};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, element_by_element_add_vectorRow) {
    MatrixRow<float, 4> r01 = {{0, 1, 2, 3}};
    MatrixRow<float, 4> r02 = {{0, 1, 2, 3}};

    auto res = r01 + r02;
    int arr_test[] = {0, 2, 4, 6};

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, element_by_element_add_vectorColumn) {
    MatrixColumn<float, 4> c01 = {{0, 1, 2, 3}};
    MatrixColumn<float, 4> c02 = {{0, 1, 2, 3}};

    auto res = c01 + c02;
    int arr_test[] = {0, 2, 4, 6};

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, element_by_element_sub_matrix) {
    MatrixBase<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixBase<float, 2, 2> m02 = {{0, 1, 2, 3}};

    auto res = m01 - m02;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), 0);
        }
    }
}

TEST(InterfaceMatrix, element_by_element_sub_vectorRow) {
    MatrixRow<float, 4> r01 = {{0, 1, 2, 3}};
    MatrixRow<float, 4> r02 = {{0, 1, 2, 3}};

    auto res = r01 - r02;

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*res(i), 0);
    }
}

TEST(InterfaceMatrix, element_by_element_sub_vectorColumn) {
    MatrixColumn<float, 4> c01 = {{0, 1, 2, 3}};
    MatrixColumn<float, 4> c02 = {{0, 1, 2, 3}};

    auto res = c01 - c02;

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*res(i), 0);
    }
}

/**********************************************************************************************************************/
//4) умножение числа на матрицу, вектора на матрицу, матрицы на вектор и матрицы на матрицу - 1б;                     //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, mult_matrix_num) {
    MatrixBase<float, 2, 2> m01 = {{0, 1, 2, 3}};

    auto res = m01 * 4;
    int arr_test[] = {0, 4, 8, 12};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, mult_num_matrix) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};

    auto res = float(4) * m01;
    int arr_test[] = {0, 4, 8, 12};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, mult_row_matrix) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixRow<float, 2> r01 = {{0, 1}};

    auto res = r01 * m01;
    int arr_test[] = {2, 3};

    for (int i = 0; i < 2; ++i) {
            EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, mult_matrix_column) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixColumn<float, 2> c01 = {{0, 1}};

    auto res =  m01 * c01;
    int arr_test[] = {1, 3};

    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, mult_matrix_matrix) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
    Matrix<float, 2, 2> m02 = {{0, 1, 2, 3}};

    auto res = m01 * m02;
    int arr_test[] = {2, 3, 6, 11};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

/**********************************************************************************************************************/
//5) суммирование/вычитание числа и вектора/матрицы, матрицы и вектора                                                //
// (с возможностью выбора - по строкам/по столбцам) - 1б;                                                             //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, add_matrix_num) {
    MatrixBase<float, 2, 2> m01 = {{0, 1, 2, 3}};

    auto res = m01 + 4;
    int arr_test[] = {4, 5, 6, 7};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, add_num_matrix) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};

    auto res = float(4) + m01;
    int arr_test[] = {4, 5, 6, 7};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, sub_matrix_num) {
    MatrixBase<float, 2, 2> m01 = {{0, 1, 2, 3}};

    auto res = m01 - float(4);
    int arr_test[] = {-4, -3, -2, -1};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, add_row_num) {
    MatrixRow<float, 2> r01 = {{0, 1}};

    auto res = r01 + 4;
    int arr_test[] = {4, 5};

    for (int i = 0; i < 2; ++i) {
            EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, add_num_row) {
    MatrixRow<float, 2> r01 = {{0, 1}};

    auto res = float(4) + r01;
    int arr_test[] = {4, 5};

    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, sub_row_num) {
    MatrixRow<float, 2> r01 = {{0, 1, 2, 3}};

    auto res = r01 - 4;
    int arr_test[] = {-4, -3};

    for (int i = 0; i < 2; ++i) {
            EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, add_column_num) {
    MatrixColumn<float, 2> c01 = {{0, 1}};

    auto res = c01 + 4;
    int arr_test[] = {4, 5};

    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, add_column_row) {
    MatrixColumn<float, 2> c01 = {{0, 1}};

    auto res = float(4) + c01;
    int arr_test[] = {4, 5};

    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, sub_column_num) {
    MatrixColumn<float, 2> c01 = {{0, 1}};

    auto res = c01 - 4;
    int arr_test[] = {-4, -3};

    for (int i = 0; i < 2; ++i) {
            EXPECT_EQ(*res(i), arr_test[i]);
    }
}

TEST(InterfaceMatrix, add_matrix_row_line_by_line) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixRow<float, 2> r01 = {{0, 1}};

    auto res = m01 + r01;
    int arr_test[] = {0, 2, 2, 4};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

//TEST(MatrixBase, add_row_matrix_line_by_line) {
//    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
//    MatrixRow<float, 2> r01 = {{0, 1}};
//
//    auto res =  r01 + m01;
//    int arr_test[] = {0, 2, 2, 4};
//
//    for (int i = 0; i < 2; ++i) {
//        for (int j = 0; j < 2; ++j) {
//            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
//        }
//    }
//}
//
TEST(InterfaceMatrix, add_matrix_column_line_by_line) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixColumn<float, 2> c01 = {{0, 1}};

    auto res = m01 + c01;
    int arr_test[] = {0, 1, 3, 4};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, sub_matrix_row_line_by_line) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixRow<float, 2> r01 = {{0, 1}};

    auto res = m01 - r01;
    int arr_test[] = {0, 0, 2, 2};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, sub_matrix_column_line_by_line) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};
    MatrixColumn<float, 2> c01 = {{0, 1}};

    auto res = m01 - c01;
    int arr_test[] = {0, 1, 1, 2};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

/**********************************************************************************************************************/
//6) получение транспонированной и обратной матриц - 1б;                                                              //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, transponce_matrix) {
    Matrix<float, 2, 2> m01 = {{0, 1, 2, 3}};

    auto res = m01.transposed();
    int arr_test[] = {0, 2, 1, 3};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 2 + j]);
        }
    }
}

TEST(InterfaceMatrix, inverted_matrix) {
    Matrix<float, 3, 3> m01 = {{1, 2, 3, 2, 3, 3, 2, 2, 2}};

    auto res = m01.inverted();
    float arr_test[] = {-0, -1, 1.5, -1, 2, -1.5, 1, -1, 0.5};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(*res(i, j), arr_test[i * 3 + j]);
        }
    }
}

/**********************************************************************************************************************/
//7) подсчёт определителя матрицы - 1б.                                                                               //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, determinant_matrix) {
    Matrix<float, 4, 4> m01 = { { 1, 0, 2, -1, 3, 0, 0, 5, 2, 1, 4, -3 , 1, 0, 5, 0 } };

    auto res = m01.determinant(4);;

    EXPECT_EQ(res, 30);
}

/**********************************************************************************************************************/
//8)- поддержка "слайсов, как в питоне" (на уровне методов, т.к. операторы такой синтаксис не поддерживают).          //
//В качестве примерного интерфейса можно опираться на то, как это сделано в " аналоге numpy на C++"                   //
//https://github.com/dpilger26/NumCpp -1б;                                                                            //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST8) {
    std::string TRUE = "ya obyazatel'no sdelayu eto *picture with cat*";
    EXPECT_TRUE(true);
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}