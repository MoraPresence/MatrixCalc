// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXROW_H
#define MATRIXCALC_MATRIXROW_H

#include "MatrixBase.h"

#define ROW 1

template<typename T, size_t columnsCount>
class MatrixRow : public MatrixBase<T, ROW, columnsCount> {
    using MatrixBase<T, ROW, columnsCount>::cells;
    using MatrixBase<T, ROW, columnsCount>::MatrixBase;
    using MatrixBase<T, ROW, columnsCount>::getColumnsCount;

public:

    using MatrixBase<T, ROW, columnsCount>::operator+=;

    MatrixRow() : MatrixBase<T, ROW, columnsCount>() {};

    MatrixRow(const MatrixRow &other) : MatrixBase<T, ROW, columnsCount>(other) {};

    explicit MatrixRow(std::array<T, columnsCount> &arr) : MatrixBase<T, ROW, columnsCount>(arr) {};

    [[nodiscard]] typename std::array<T, ROW * columnsCount>::iterator Begin() { return cells.begin(); }

    [[nodiscard]] typename std::array<T, ROW * columnsCount>::iterator End() { return cells.end(); }

    T *operator()(size_t i);

    MatrixRow operator*=(MatrixBase<T, columnsCount, columnsCount> &other);

    MatrixRow operator*(MatrixBase<T, columnsCount, columnsCount> &other);

    MatrixRow operator*=(MatrixRow &other);

    MatrixRow operator*(MatrixRow &other);

    MatrixRow operator+=(MatrixRow &other);

    MatrixRow operator+(MatrixRow &other);

    MatrixRow operator-=(MatrixRow &other);

    MatrixRow operator-(MatrixRow &other);

    MatrixRow operator+=(const T &num);

    MatrixRow operator+(const T &num);

    MatrixRow operator-=(const T &num);

    MatrixRow operator-(const T &num);
};

template<typename T, size_t columnsCount>
T *MatrixRow<T, columnsCount>::operator()(size_t i) {
    return MatrixBase<T, ROW, columnsCount>::operator()(0, i);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator*=(MatrixRow<T, columnsCount> &other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::multiplies<>{});
    return *this;
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator*(MatrixRow<T, columnsCount> &other) {
    return operator*=(other);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator+=(MatrixRow<T, columnsCount> &other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::plus<>{});
    return *this;
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator+(MatrixRow<T, columnsCount> &other) {
    return operator+=(other);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator-=(MatrixRow<T, columnsCount> &other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::minus<>{});
    return *this;
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator-(MatrixRow<T, columnsCount> &other) {
    return operator-=(other);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator+=(const T &num) {
    for (auto &i: this->cells) {
        i += num;
    }
    return *this;
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator+(const T &num) {
    return *this += num;
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> operator+=(const T &num, MatrixRow<T, columnsCount> &matrix) {
    return matrix.operator+=(num);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> operator+(const T &num, MatrixRow<T, columnsCount> &matrix) {
    return operator+=(num, matrix);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator-=(const T &num) {
    for (auto &i: this->cells) {
        i -= num;
    }
    return *this;
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator-(const T &num) {
    return *this -= num;
}

#endif //MATRIXCALC_MATRIXROW_H
