// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXCOLUMN_H
#define MATRIXCALC_MATRIXCOLUMN_H

#include "MatrixBase.h"

#define COLUMN 1

template<typename T, size_t rowCount>
class MatrixColumn : public MatrixBase<T, rowCount, COLUMN> {
    using MatrixBase<T, rowCount, COLUMN>::cells;

    using MatrixBase<T, rowCount, COLUMN>::MatrixBase;
public:
    using MatrixBase<T, rowCount, COLUMN>::operator+=;

    using MatrixBase<T, rowCount, COLUMN>::operator+;

    using MatrixBase<T, rowCount, COLUMN>::operator-=;

    using MatrixBase<T, rowCount, COLUMN>::operator-;

    using MatrixBase<T, rowCount, COLUMN>::operator*=;

    using MatrixBase<T, rowCount, COLUMN>::operator*;

    using MatrixBase<T, rowCount, COLUMN>::operator=;

    using MatrixBase<T, rowCount, COLUMN>::operator==;

    using MatrixBase<T, rowCount, COLUMN>::begin;

    using MatrixBase<T, rowCount, COLUMN>::end;

    MatrixColumn() : MatrixBase<T, rowCount, COLUMN>() {};

    MatrixColumn(const MatrixColumn &other) : MatrixBase<T, rowCount, COLUMN>(other) {};

    MatrixColumn(const MatrixBase<T, rowCount, COLUMN> &other) : MatrixBase<T, rowCount, COLUMN>(other) {};

    MatrixColumn(const MatrixBase<T, rowCount, COLUMN> &&other) : MatrixBase<T, rowCount, COLUMN>(other) {};

    constexpr T *operator()(size_t i);
};

template<typename T, size_t rowsCount>
constexpr T *MatrixColumn<T, rowsCount>::operator()(size_t i) {
    return MatrixBase<T, rowsCount, COLUMN>::operator()(i, 0);
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> operator+=(const T &num, MatrixColumn<T, rowCount> &matrix) {
    return matrix += num;
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> operator+(const T &num, MatrixColumn<T, rowCount> &matrix) {
    return operator+=(num, matrix);
}

#endif //MATRIXCALC_MATRIXCOLUMN_H
