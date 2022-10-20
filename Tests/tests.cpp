#include <gtest/gtest.h>
#include "Matrix.h"
/**********************************************************************************************************************/
//1) обращение по индексам к элементам, извлечение диагонали, строки или столбца - 1б                                 //
//(после модификации исходной матрицы извлечённые элементы меняться не должны);                                       //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST1) {
    Matrix<float> m(2, 2);
    float arr[] = {1, 2, 3, 4,};
    m.fill(4, arr);

    EXPECT_EQ(m[0][0], arr[0]);
    EXPECT_EQ(m[0][1], arr[1]);

    auto row = m.getRow(0);
    EXPECT_EQ(row[0], arr[0]);
    EXPECT_EQ(row[1], arr[1]);

    auto column = m.getColumn(0);
    EXPECT_EQ(column[0], arr[0]);
    EXPECT_EQ(column[1], arr[2]);

    auto diagonal = m.getDiagonal();
    EXPECT_EQ(diagonal[0], arr[0]);
    EXPECT_EQ(diagonal[1], arr[3]);

    row[0] = 99;
    column[0] = 99;
    diagonal[0] = 99;

    EXPECT_EQ(m[0][0], arr[0]);
}

/**********************************************************************************************************************/
//2) возможность создания матрицы из векторов или чисел, вектора из чисел - 1б;                                       //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST2) {
    Matrix<float> m(2, 2);
    float arr[] = {1, 2, 3, 4};
    m.fill(4, arr);

    EXPECT_EQ(m[0][0], arr[0]);
    EXPECT_EQ(m[0][1], arr[1]);
    EXPECT_EQ(m[1][0], arr[2]);
    EXPECT_EQ(m[1][1], arr[3]);

    float arrRow[] = {9, 8, 7};
    Matrix<float>::MatrixInstance<float &> row(3);
    row.fill(3, arrRow);
    EXPECT_EQ(row[0], arrRow[0]);
    EXPECT_EQ(row[1], arrRow[1]);
    EXPECT_EQ(row[2], arrRow[2]);

    m.fill(1, row);
    EXPECT_EQ(m[0][1], arrRow[0]);
    EXPECT_EQ(m[1][0], arrRow[1]);
    EXPECT_EQ(m[1][1], arrRow[2]);
}

/**********************************************************************************************************************/
//3) поэлементное сложение/вычитание/умножение объектов одинаковой размерности - 1б;                                  //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST3_1) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    Matrix<float> m02(2, 2);
    m02.fill(4, arr);

    auto resAdd = m01 + m02;
    EXPECT_EQ(resAdd[0][0], 2);
    EXPECT_EQ(resAdd[0][1], 4);
    EXPECT_EQ(resAdd[1][0], 6);
    EXPECT_EQ(resAdd[1][1], 8);
}

TEST(InterfaceMatrix, TEST3_2) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    Matrix<float> m02(2, 2);
    m02.fill(4, arr);

    auto resSub = m01 - m02;
    EXPECT_EQ(resSub[0][0], 0);
    EXPECT_EQ(resSub[0][1], 0);
    EXPECT_EQ(resSub[1][0], 0);
    EXPECT_EQ(resSub[1][1], 0);
}

TEST(InterfaceMatrix, TEST3_3) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    Matrix<float> m02(2, 2);
    m02.fill(4, arr);

    auto resMult = m01 * m02;
    EXPECT_EQ(resMult[0][0], 1);
    EXPECT_EQ(resMult[0][1], 4);
    EXPECT_EQ(resMult[1][0], 9);
    EXPECT_EQ(resMult[1][1], 16);
}

/**********************************************************************************************************************/
//4) умножение числа на матрицу, вектора на матрицу, матрицы на вектор и матрицы на матрицу - 1б;                     //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST4) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    Matrix<float> m02(2, 2);
    m02.fill(4, arr);

    auto res = m01.multiply(m02);
    EXPECT_EQ(res[0][0], 7);
    EXPECT_EQ(res[0][1], 10);
    EXPECT_EQ(res[1][0], 15);
    EXPECT_EQ(res[1][1], 22);


    auto row = m02.getRow(0);
    auto resRow = m01.multiply(row);
    EXPECT_EQ(resRow[0], 5);
    EXPECT_EQ(resRow[1], 11);


    auto column = m02.getColumn(0);
    auto resColumn = m01.multiply(column);
    EXPECT_EQ(resColumn[0], 7);
    EXPECT_EQ(resColumn[1], 15);

    auto resNum = m01.multiply(2);
    EXPECT_EQ(resNum[0][0], 2);
    EXPECT_EQ(resNum[0][1], 4);
    EXPECT_EQ(resNum[1][0], 6);
    EXPECT_EQ(resNum[1][1], 8);

    auto resRowRow = row.multiply(column);
    EXPECT_EQ(resRowRow[0][0], 1);
    EXPECT_EQ(resRowRow[0][1], 3);
    EXPECT_EQ(resRowRow[1][0], 2);
    EXPECT_EQ(resRowRow[1][1], 6);
}

/**********************************************************************************************************************/
//5) суммирование/вычитание числа и вектора/матрицы, матрицы и вектора                                                //
// (с возможностью выбора - по строкам/по столбцам) - 1б;                                                             //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST5_1) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    auto diagonal = m01.getDiagonal();

    auto res = diagonal.addition(3);

    EXPECT_EQ(res[0][0], 4);
    EXPECT_EQ(res[0][1], 7);
}

TEST(InterfaceMatrix, TEST5_2) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    auto diagonal = m01.getDiagonal();

    auto res = diagonal.subtraction(3);

    EXPECT_EQ(res[0][0], -2);
    EXPECT_EQ(res[0][1], 1);
}

TEST(InterfaceMatrix, TEST5_3) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);


    auto res = m01.addition(3);

    EXPECT_EQ(res[0][0], 4);
    EXPECT_EQ(res[0][1], 5);
    EXPECT_EQ(res[1][0], 6);
    EXPECT_EQ(res[1][1], 7);
}

TEST(InterfaceMatrix, TEST5_4) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);


    auto res = m01.subtraction(3);

    EXPECT_EQ(res[0][0], -2);
    EXPECT_EQ(res[0][1], -1);
    EXPECT_EQ(res[1][0], 0);
    EXPECT_EQ(res[1][1], 1);
}

TEST(InterfaceMatrix, TEST5_5) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    auto row = m01.getRow(0);

    auto res = m01.addition(row, ROW);

    EXPECT_EQ(res[0][0], 2);
    EXPECT_EQ(res[0][1], 4);
    EXPECT_EQ(res[1][0], 4);
    EXPECT_EQ(res[1][1], 6);
}

TEST(InterfaceMatrix, TEST5_6) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    auto row = m01.getRow(0);

    auto res = m01.addition(row, COLUMN);

    EXPECT_EQ(res[0][0], 2);
    EXPECT_EQ(res[0][1], 3);
    EXPECT_EQ(res[1][0], 5);
    EXPECT_EQ(res[1][1], 6);
}

TEST(InterfaceMatrix, TEST5_7) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    auto row = m01.getRow(0);

    auto res = m01.subtraction(row, ROW);

    EXPECT_EQ(res[0][0], 0);
    EXPECT_EQ(res[0][1], 0);
    EXPECT_EQ(res[1][0], 2);
    EXPECT_EQ(res[1][1], 2);
}

TEST(InterfaceMatrix, TEST5_8) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);

    auto row = m01.getRow(0);

    auto res = m01.subtraction(row, COLUMN);

    EXPECT_EQ(res[0][0], 0);
    EXPECT_EQ(res[0][1], 1);
    EXPECT_EQ(res[1][0], 1);
    EXPECT_EQ(res[1][1], 2);
}

/**********************************************************************************************************************/
//6) получение транспонированной и обратной матриц - 1б;                                                              //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST6_1) {
    Matrix<float> m01(2, 2);
    float arr[] = {1, 2, 3, 4};
    m01.fill(4, arr);


    auto res = m01.transposed();

    EXPECT_EQ(res[0][0], 1);
    EXPECT_EQ(res[0][1], 3);
    EXPECT_EQ(res[1][0], 2);
    EXPECT_EQ(res[1][1], 4);
}

TEST(InterfaceMatrix, TEST6_2) {
    Matrix<float> m01(3, 3);
    float m01_arr[] = {1,2,3,2,3,3, 2,2,2};
    m01.fill(9, m01_arr);


    auto res = m01.inverted();

    EXPECT_EQ(res[0][0], -0);
    EXPECT_EQ(res[0][1], -1);
    EXPECT_EQ(res[0][2], 1.5);
    EXPECT_EQ(res[1][0], -1);
    EXPECT_EQ(res[1][1], 2);
    EXPECT_EQ(res[1][2], -1.5);
    EXPECT_EQ(res[2][0], 1);
    EXPECT_EQ(res[2][1], -1);
    EXPECT_EQ(res[2][2], 0.5);

}

/**********************************************************************************************************************/
//7) подсчёт определителя матрицы - 1б.                                                                               //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST7) {
    Matrix<float> m01(2, 2);
    float arr[] = {3, 4, 5, 18};
    m01.fill(4, arr);


    auto res = m01.determinant();

    EXPECT_EQ(res, 34);

}

/**********************************************************************************************************************/
//8)- поддержка "слайсов, как в питоне" (на уровне методов, т.к. операторы такой синтаксис не поддерживают).          //
//В качестве примерного интерфейса можно опираться на то, как это сделано в " аналоге numpy на C++"                   //
//https://github.com/dpilger26/NumCpp -1б;                                                                            //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST8) {
    Matrix<float, 3, 3> m01;

    float m01_arr[] = {1,2,3,2,3,3, 2,2,2};
    m01.fill(9, m01_arr);


    auto res = m01.Slice(4, 8);

    EXPECT_EQ(res[0], 3);
    EXPECT_EQ(res[1], 3);
    EXPECT_EQ(res[2], 2);
    EXPECT_EQ(res[3], 2);
    EXPECT_EQ(res[4], 2);
}

/**********************************************************************************************************************/
//9) размерность матриц может задаваться с помощью шаблонных параметров -2б;                                                                               //
/**********************************************************************************************************************/
TEST(InterfaceMatrix, TEST9) {
    Matrix<float, 3, 3> m01;

    float m01_arr[] = {1,2,3,2,3,3, 2,2,2};
    m01.fill(9, m01_arr);


    auto res = m01.determinant();

    EXPECT_EQ(res, -2);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}