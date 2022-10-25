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

    MatrixColumn() : MatrixBase<T, rowCount, COLUMN>() {};

    MatrixColumn(const MatrixColumn &other) : MatrixBase<T, rowCount, COLUMN>(other) {};

    [[nodiscard]] typename std::array<T, COLUMN * rowCount>::iterator Begin() { return cells.begin(); }

    [[nodiscard]] typename std::array<T, COLUMN * rowCount>::iterator End() { return cells.end(); }

    T *operator()(size_t i);

    MatrixColumn<T, rowCount> operator*=(MatrixColumn<T, rowCount> &other);

    MatrixColumn<T, rowCount> operator*(MatrixColumn<T, rowCount> &other);

    MatrixColumn<T, rowCount> operator+=(MatrixColumn<T, rowCount> &other);

    MatrixColumn<T, rowCount> operator+(MatrixColumn<T, rowCount> &other);

    MatrixColumn<T, rowCount> operator-=(MatrixColumn<T, rowCount> &other);

    MatrixColumn<T, rowCount> operator-(MatrixColumn<T, rowCount> &other);

    MatrixColumn operator+=(const T &num);

    MatrixColumn operator+(const T &num);

    MatrixColumn operator-=(const T &num);

    MatrixColumn operator-(const T &num);
};

template<typename T, size_t rowsCount>
T *MatrixColumn<T, rowsCount>::operator()(size_t i) {
    return MatrixBase<T, rowsCount, COLUMN>::operator()(i, 0);
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator*=(MatrixColumn<T, rowCount> &other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::multiplies<>{});
    return *this;
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator*(MatrixColumn<T, rowCount> &other) {
    return operator*=(other);
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator+=(MatrixColumn<T, rowCount> &other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::plus<>{});
    return *this;
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator+(MatrixColumn<T, rowCount> &other) {
    return operator+=(other);
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator-=(MatrixColumn<T, rowCount> &other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::minus<>{});
    return *this;
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator-(MatrixColumn<T, rowCount> &other) {
    return operator-=(other);
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator+=(const T &num) {
    for (auto &i: this->cells) {
        i += num;
    }
    return *this;
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator+(const T &num) {
    return MatrixColumn<T, rowCount>(*this) += num;
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> operator+=(const T &num, MatrixColumn<T, rowCount> &matrix) {
    return matrix.operator+=(num);
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> operator+(const T &num, MatrixColumn<T, rowCount> &matrix) {
    return operator+=(num, matrix);
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator-=(const T &num) {
    for (auto &i: this->cells) {
        i -= num;
    }
    return *this;
}

template<typename T, size_t rowCount>
MatrixColumn<T, rowCount> MatrixColumn<T, rowCount>::operator-(const T &num) {
    return MatrixColumn<T, rowCount>(*this) -= num;
}

#endif //MATRIXCALC_MATRIXCOLUMN_H
