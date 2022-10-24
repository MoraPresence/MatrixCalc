// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXBASE_H
#define MATRIXCALC_MATRIXBASE_H

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

template<typename T, size_t rowsCount, size_t columnsCount>
class MatrixBase;

template<typename T, size_t rowsCount, size_t columnsCount>
void swap(MatrixBase<T, rowsCount, columnsCount> &first, MatrixBase<T, rowsCount, columnsCount> &second);

template<typename T, size_t rowsCount, size_t columnsCount>
std::ostream &operator<<(std::ostream &, MatrixBase<T, rowsCount, columnsCount> &);

template<typename T, size_t rowsCount, size_t columnsCount>
class MatrixBase {
protected:
    std::array<T, rowsCount * columnsCount> cells = {0};
public:
/************************************************constructors**********************************************************/
    MatrixBase() = default;

    MatrixBase(const MatrixBase &other);

    MatrixBase(MatrixBase &&other) noexcept;

    MatrixBase(std::initializer_list<T> list);

    explicit MatrixBase(std::array<T, columnsCount> &arr);

    ~MatrixBase();
/**********************************************************************************************************************/


/************************************************operators*************************************************************/
    MatrixBase &operator=(MatrixBase const &other);

    MatrixBase &operator=(MatrixBase &&other) noexcept;

    MatrixBase operator+(MatrixBase other);

    MatrixBase operator+=(MatrixBase other);

    MatrixBase operator-(MatrixBase other);

    MatrixBase operator-=(MatrixBase other);

    virtual MatrixBase operator*(MatrixBase other);

    virtual MatrixBase operator*=(MatrixBase other);

    MatrixBase operator*=(const T &num);

    MatrixBase operator*(const T &num);

    MatrixBase operator+=(const T &num);

    MatrixBase operator+(const T &num);

    MatrixBase operator-=(const T &num);

    MatrixBase operator-(const T &num);

    T *operator()(size_t i, size_t j);
/**********************************************************************************************************************/


/************************************************getters***************************************************************/
    [[nodiscard]] size_t getRowsCount() const { return rowsCount; }

    [[nodiscard]] size_t getColumnsCount() const { return columnsCount; }

    virtual typename std::array<T, rowsCount * columnsCount>::iterator Begin() { return cells.begin(); }

    virtual typename std::array<T, rowsCount * columnsCount>::iterator End() { return cells.end(); }
/**********************************************************************************************************************/


/************************************************friends***************************************************************/
    friend std::ostream &operator<<<T, rowsCount, columnsCount>
            (std::ostream &, MatrixBase<T, rowsCount, columnsCount> &);

    friend void swap<T, rowsCount, columnsCount>
            (MatrixBase<T, rowsCount, columnsCount> &first, MatrixBase<T, rowsCount, columnsCount> &second);
/**********************************************************************************************************************/
};


/************************************************constructors**********************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount>::MatrixBase(std::initializer_list<T> list) {
    std::copy(list.begin(), list.end(), cells.begin());
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount>::MatrixBase(const MatrixBase &other) {
    std::copy(other.cells.begin(), other.cells.end(), cells.begin());
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount>::MatrixBase(MatrixBase &&other) noexcept {
    *this = other;
    delete other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount>::MatrixBase(std::array<T, columnsCount> &arr) {
    std::copy(arr.begin(), arr.end(), cells.begin());
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount>::~MatrixBase() = default;
/**********************************************************************************************************************/


/************************************************operators*************************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator=(MatrixBase const &other) {
    MatrixBase<T, rowsCount, columnsCount> tmp(other);
    swap(*this, tmp);
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator=(MatrixBase &&other) noexcept {
    swap(*this, other);
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixBase<T, rows, columns> MatrixBase<T, rows, columns>::operator+(MatrixBase other) {
    return *this += other;
}

template<typename T, size_t rows, size_t columns>
MatrixBase<T, rows, columns> MatrixBase<T, rows, columns>::operator+=(MatrixBase other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::plus<>{});
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixBase<T, rows, columns> MatrixBase<T, rows, columns>::operator-(MatrixBase other) {
    return *this -= other;
}

template<typename T, size_t rows, size_t columns>
MatrixBase<T, rows, columns> MatrixBase<T, rows, columns>::operator-=(MatrixBase other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::minus<>{});
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixBase<T, rows, columns> MatrixBase<T, rows, columns>::operator*=(MatrixBase other) {
    std::transform(this->Begin(), this->End(), other.Begin(), this->Begin(), std::multiplies<>{});
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixBase<T, rows, columns> MatrixBase<T, rows, columns>::operator*(MatrixBase other) {
    return *this *= other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
T *MatrixBase<T, rowsCount, columnsCount>::operator()(size_t i, size_t j) {
    return cells.begin() + (i * columnsCount + j);
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator*=(const T &num) {
    for (auto &i: this->cells) {
        i *= num;
    }
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator*(const T &num) {
    return *this *= num;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> operator*=(const T &num, MatrixBase<T, rowsCount, columnsCount> &matrix) {
    return matrix.operator*=(num);
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> operator*(const T &num, MatrixBase<T, rowsCount, columnsCount> &matrix) {
    return operator*=(num, matrix);
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator+=(const T &num) {
    for (auto &i: this->cells) {
        i += num;
    }
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator+(const T &num) {
    return *this += num;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> operator+=(const T &num, MatrixBase<T, rowsCount, columnsCount> &matrix) {
    return matrix.operator+=(num);
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> operator+(const T &num, MatrixBase<T, rowsCount, columnsCount> &matrix) {
    return operator+=(num, matrix);
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator-=(const T &num) {
    for (auto &i: this->cells) {
        i -= num;
    }
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator-(const T &num) {
    return *this -= num;
}
/**********************************************************************************************************************/


/************************************************friends***************************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
std::ostream &operator<<(std::ostream &out, MatrixBase<T, rowsCount, columnsCount> &matrix) {
    for (size_t i = 0; i < rowsCount; ++i) {
        out << "{ ";
        for (size_t j = 0; j < columnsCount; ++j) {
            out << *matrix(i, j) << " ";
        }
        out << "}\n";
    }
    return out;
}

template<typename T, size_t rowsCount, size_t columnsCount>
void swap(MatrixBase<T, rowsCount, columnsCount> &first, MatrixBase<T, rowsCount, columnsCount> &second) {
    first.cells.swap(second.cells);
}
/**********************************************************************************************************************/
#endif //MATRIXCALC_MATRIXBASE_H
