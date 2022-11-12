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

    MatrixBase(std::array<T, columnsCount> &arr);

    ~MatrixBase();
/**********************************************************************************************************************/


/************************************************operators*************************************************************/
    constexpr MatrixBase &operator=(MatrixBase const &other);

    constexpr MatrixBase &operator=(MatrixBase &&other) noexcept;

    constexpr MatrixBase &operator=(std::initializer_list<T> list);

    constexpr MatrixBase operator+(MatrixBase &other);

    constexpr MatrixBase &operator+=(MatrixBase &other);

    constexpr MatrixBase operator-(MatrixBase &other);

    constexpr MatrixBase &operator-=(MatrixBase &other);

    virtual MatrixBase operator*(MatrixBase &other);

    virtual MatrixBase &operator*=(MatrixBase &other);

    constexpr MatrixBase &operator*=(const T &num);

    constexpr MatrixBase operator*(const T &num);

    constexpr MatrixBase &operator+=(const T &num);

    constexpr MatrixBase operator+(const T &num);

    constexpr MatrixBase &operator-=(const T &num);

    constexpr MatrixBase operator-(const T &num);

    constexpr T *operator()(size_t i, size_t j);

    bool operator==(MatrixBase &other);

    bool operator==(std::array<T, rowsCount * columnsCount> &arr);
/**********************************************************************************************************************/


/************************************************getters***************************************************************/
    [[nodiscard]] size_t getRowsCount() const;

    [[nodiscard]] size_t getColumnsCount() const;

    typename std::array<T, rowsCount * columnsCount>::iterator begin();

    typename std::array<T, rowsCount * columnsCount>::iterator end();
/**********************************************************************************************************************/


/************************************************friends***************************************************************/
    friend std::ostream &operator << <>(std::ostream &, MatrixBase<T, rowsCount, columnsCount> &);

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
MatrixBase<T, rowsCount, columnsCount>::MatrixBase(MatrixBase &&other) noexcept : cells(other.cells) {
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
constexpr MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator=(MatrixBase const &other) {
    MatrixBase<T, rowsCount, columnsCount> tmp(other);
    swap(*this, tmp);
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator=(MatrixBase &&other) noexcept {
    swap(*this, other);
    delete other;
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator=(std::initializer_list<T> list) {
    std::copy(list.begin(), list.end(), cells.begin());
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator+(MatrixBase &other) {
    return MatrixBase<T, rowsCount, columnsCount>(*this) += other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator+=(MatrixBase &other) {
    std::transform(this->begin(), this->end(), other.begin(), this->begin(), std::plus<>{});
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator-(MatrixBase &other) {
    return MatrixBase<T, rowsCount, columnsCount>(*this) -= other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator-=(MatrixBase &other) {
    std::transform(this->begin(), this->end(), other.begin(), this->begin(), std::minus<>{});
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> &
MatrixBase<T, rowsCount, columnsCount>::operator*=(MatrixBase &other) {
    std::transform(this->begin(), this->end(), other.begin(), this->begin(), std::multiplies<>{});
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator*(MatrixBase &other) {
    return MatrixBase<T, rowsCount, columnsCount>(*this) *= other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr T *MatrixBase<T, rowsCount, columnsCount>::operator()(size_t i, size_t j) {
    return cells.begin() + (i * columnsCount + j);
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> &MatrixBase<T, rowsCount, columnsCount>::operator*=(const T &num) {
    std::transform(this->begin(), this->end(), this->begin(), [&num](T &i) { return i *= num; });
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator*(const T &num) {
    return MatrixBase<T, rowsCount, columnsCount>(*this) *= num;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> operator*=(const T &num, MatrixBase<T, rowsCount, columnsCount> &matrix) {
    return matrix *= num;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixBase<T, rowsCount, columnsCount> operator*(const T &num, MatrixBase<T, rowsCount, columnsCount> &matrix) {
    return operator*=(num, matrix);
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> &MatrixBase<T, rowsCount, columnsCount>::operator+=(const T &num) {
    std::transform(this->begin(), this->end(), this->begin(), [&num](T &i) { return i += num; });
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator+(const T &num) {
    return MatrixBase<T, rowsCount, columnsCount>(*this) += num;
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
constexpr MatrixBase<T, rowsCount, columnsCount> &MatrixBase<T, rowsCount, columnsCount>::operator-=(const T &num) {
    std::transform(this->begin(), this->end(), this->begin(), [&num](T &i) { return i -= num; });
    return *this;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixBase<T, rowsCount, columnsCount> MatrixBase<T, rowsCount, columnsCount>::operator-(const T &num) {
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

template<typename T, size_t rowsCount, size_t columnsCount>
size_t MatrixBase<T, rowsCount, columnsCount>::getRowsCount() const {
    return rowsCount;
}

template<typename T, size_t rowsCount, size_t columnsCount>
size_t MatrixBase<T, rowsCount, columnsCount>::getColumnsCount() const {
    return columnsCount;
}

template<typename T, size_t rowsCount, size_t columnsCount>
typename std::array<T, rowsCount * columnsCount>::iterator MatrixBase<T, rowsCount, columnsCount>::begin() {
    return cells.begin();
}

template<typename T, size_t rowsCount, size_t columnsCount>
typename std::array<T, rowsCount * columnsCount>::iterator MatrixBase<T, rowsCount, columnsCount>::end() {
    return cells.end();
}

template<typename T, size_t rowsCount, size_t columnsCount>
bool MatrixBase<T, rowsCount, columnsCount>::operator==(MatrixBase &other) {
    return this->cells == other.cells;
}

template<typename T, size_t rowsCount, size_t columnsCount>
bool MatrixBase<T, rowsCount, columnsCount>::operator==(std::array<T, rowsCount * columnsCount> &arr) {
    return this->cells == arr;
}
/**********************************************************************************************************************/

#endif //MATRIXCALC_MATRIXBASE_H
