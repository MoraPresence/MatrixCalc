// Copyright 2022 mora

#include "help_for_tests.h"

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
    MatrixSlice<0, 2, double, 4 * 4> slice = m01.slice<0, 2, double>();
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(*slice(i), test[i]);
    }
}
