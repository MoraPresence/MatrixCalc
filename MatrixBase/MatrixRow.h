// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXROW_H
#define MATRIXCALC_MATRIXROW_H

#include "MatrixBase.h"

template<typename T, size_t column_num>
class MatrixRow : public MatrixBase<T, 1, column_num> {
    using MatrixBase<T, 1, column_num>::cells;
    using MatrixBase<T, 1, column_num>::MatrixBase;

public:
    using MatrixBase<T, 1, column_num>::operator+=;
    using MatrixBase<T, 1, column_num>::operator+;
    using MatrixBase<T, 1, column_num>::operator-=;
    using MatrixBase<T, 1, column_num>::operator-;
    using MatrixBase<T, 1, column_num>::operator*=;
    using MatrixBase<T, 1, column_num>::operator*;
    using MatrixBase<T, 1, column_num>::operator=;
    using MatrixBase<T, 1, column_num>::operator==;
    using MatrixBase<T, 1, column_num>::begin;
    using MatrixBase<T, 1, column_num>::end;

    MatrixRow() : MatrixBase<T, 1, column_num>(){};
    MatrixRow(const MatrixRow &other) : MatrixBase<T, 1, column_num>(other){};
    MatrixRow(std::array<T, column_num> &arr) : MatrixBase<T, 1, column_num>(arr){};
    MatrixRow(const MatrixBase<T, 1, column_num> &other) : MatrixBase<T, 1, column_num>(other){};
    MatrixRow(const MatrixBase<T, 1, column_num> &&other) : MatrixBase<T, 1, column_num>(other){};
    MatrixRow operator*=(MatrixBase<T, column_num, column_num> &other);
    MatrixRow operator*(MatrixBase<T, column_num, column_num> &other);

    constexpr T *operator()(size_t i);
};

template<typename T, size_t column_num>
constexpr T *MatrixRow<T, column_num>::operator()(size_t i) {
    return MatrixBase<T, 1, column_num>::operator()(0, i);
}

template<typename T, size_t column_num>
MatrixRow<T, column_num>
        operator+=(const T &num, MatrixRow<T, column_num> &matrix) {
    return matrix.operator+=(num);
}

template<typename T, size_t column_num>
MatrixRow<T, column_num>
        operator+(const T &num, MatrixRow<T, column_num> &matrix) {
    return operator+=(num, matrix);
}
#endif//MATRIXCALC_MATRIXROW_H
