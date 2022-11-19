// Copyright 2022 mora

#pragma once

#include "Matrix.h"

#include <gtest/gtest.h>

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
