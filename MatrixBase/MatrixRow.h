// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXROW_H
#define MATRIXCALC_MATRIXROW_H

#include "MatrixBase.h"

#define ROW 1

template<typename T, size_t columnsCount>
class MatrixRow : public MatrixBase<T, ROW, columnsCount> {
    using MatrixBase<T, ROW, columnsCount>::cells;
    using MatrixBase<T, ROW, columnsCount>::MatrixBase;
public:
    using MatrixBase<T, ROW, columnsCount>::operator+=;
    using MatrixBase<T, ROW, columnsCount>::operator+;
    using MatrixBase<T, ROW, columnsCount>::operator-=;
    using MatrixBase<T, ROW, columnsCount>::operator-;
    using MatrixBase<T, ROW, columnsCount>::operator*=;
    using MatrixBase<T, ROW, columnsCount>::operator*;
    using MatrixBase<T, ROW, columnsCount>::operator=;
    using MatrixBase<T, ROW, columnsCount>::Begin;
    using MatrixBase<T, ROW, columnsCount>::End;

    MatrixRow() : MatrixBase<T, ROW, columnsCount>() {};

    MatrixRow(const MatrixRow &other) : MatrixBase<T, ROW, columnsCount>(other) {};

    MatrixRow(std::array<T, columnsCount> &arr) : MatrixBase<T, ROW, columnsCount>(arr) {};

    MatrixRow(const MatrixBase<T, ROW, columnsCount> &other) : MatrixBase<T, ROW, columnsCount>(other) {};

    MatrixRow operator*=(MatrixBase<T, columnsCount, columnsCount> &other);

    MatrixRow operator*(MatrixBase<T, columnsCount, columnsCount> &other);

    virtual T *operator()(size_t i);
};

template<typename T, size_t columnsCount>
T *MatrixRow<T, columnsCount>::operator()(size_t i) {
    return MatrixBase<T, ROW, columnsCount>::operator()(0, i);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> operator+=(const T &num, MatrixRow<T, columnsCount> &matrix) {
    return matrix.operator+=(num);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> operator+(const T &num, MatrixRow<T, columnsCount> &matrix) {
    return operator+=(num, matrix);
}
#endif //MATRIXCALC_MATRIXROW_H
