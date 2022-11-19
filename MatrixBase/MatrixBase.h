// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXBASE_H
#define MATRIXCALC_MATRIXBASE_H

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

template<typename T, size_t row_num, size_t column_num>
class MatrixBase;

template<typename T, size_t row_num, size_t column_num>
void swap(MatrixBase<T, row_num, column_num> &first, MatrixBase<T, row_num, column_num> &second);

template<typename T, size_t row_num, size_t column_num>
std::ostream &operator<<(std::ostream &, MatrixBase<T, row_num, column_num> &);

template<typename T, size_t row_num, size_t column_num>
class MatrixBase {
protected:
    std::array<T, row_num *column_num> cells = {0};

public:
    MatrixBase() = default;
    MatrixBase(const MatrixBase &other);
    MatrixBase(MatrixBase &&other) noexcept;
    MatrixBase(std::initializer_list<T> list);
    explicit MatrixBase(std::array<T, column_num> &arr);
    ~MatrixBase();

    constexpr MatrixBase &operator=(MatrixBase const &other);
    constexpr MatrixBase &operator=(MatrixBase &&other) noexcept;
    constexpr MatrixBase &operator=(std::initializer_list<T> list);
    constexpr MatrixBase operator+(const MatrixBase &other);
    constexpr MatrixBase &operator+=(const MatrixBase &other);
    constexpr MatrixBase operator-(const MatrixBase &other);
    constexpr MatrixBase &operator-=(const MatrixBase &other);
    virtual MatrixBase operator*(const MatrixBase &other);
    virtual MatrixBase &operator*=(const MatrixBase &other);
    constexpr MatrixBase &operator*=(const T &num);
    constexpr MatrixBase operator*(const T &num);
    constexpr MatrixBase &operator+=(const T &num);
    constexpr MatrixBase operator+(const T &num);
    constexpr MatrixBase &operator-=(const T &num);
    constexpr MatrixBase operator-(const T &num);
    typename std::array<T, row_num * column_num>
            ::const_iterator operator()(const size_t &i, const size_t &j) const;
    typename std::array<T, row_num * column_num>
            ::iterator operator()(const size_t &i, const size_t &j);
    bool operator==(const MatrixBase &other);
    bool operator==(const std::array<T, row_num * column_num> &arr);

    typename std::array<T, row_num * column_num>::const_iterator begin() const;
    typename std::array<T, row_num * column_num>::const_iterator end() const;
    typename std::array<T, row_num * column_num>::iterator begin();
    typename std::array<T, row_num * column_num>::iterator end();
};

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>::MatrixBase(std::initializer_list<T> list) {
    std::copy(list.begin(), list.end(), cells.begin());
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>::MatrixBase(const MatrixBase &other) {
    std::copy(other.cells.begin(), other.cells.end(), cells.begin());
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>::MatrixBase(MatrixBase &&other) noexcept : cells(other.cells) {
    delete other;
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>::MatrixBase(std::array<T, column_num> &arr) {
    std::copy(arr.begin(), arr.end(), cells.begin());
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>::~MatrixBase() = default;

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num> &
MatrixBase<T, row_num, column_num>::operator=(MatrixBase const &other) {
    MatrixBase<T, row_num, column_num> tmp(other);
    swap(*this, tmp);
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num> &
MatrixBase<T, row_num, column_num>::operator=(MatrixBase &&other) noexcept {
    swap(*this, other);
    delete other;
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num> &
MatrixBase<T, row_num, column_num>::operator=(std::initializer_list<T> list) {
    std::copy(list.begin(), list.end(), cells.begin());
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
MatrixBase<T, row_num, column_num>::operator+(const MatrixBase &other) {
    return MatrixBase<T, row_num, column_num>(*this) += other;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num> &
MatrixBase<T, row_num, column_num>::operator+=(const MatrixBase &other) {
    std::transform(begin(), end(), other.begin(), begin(), std::plus<>{});
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
MatrixBase<T, row_num, column_num>::operator-(const MatrixBase &other) {
    return MatrixBase<T, row_num, column_num>(*this) -= other;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num> &
MatrixBase<T, row_num, column_num>::operator-=(const MatrixBase &other) {
    std::transform(begin(), end(), other.begin(), begin(), std::minus<>{});
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num> &
MatrixBase<T, row_num, column_num>::operator*=(const MatrixBase &other) {
    std::transform(begin(), end(), other.begin(), begin(), std::multiplies<>{});
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>
MatrixBase<T, row_num, column_num>::operator*(const MatrixBase &other) {
    return MatrixBase<T, row_num, column_num>(*this) *= other;
}

template<typename T, size_t row_num, size_t column_num>
typename std::array<T, row_num * column_num>
        ::const_iterator MatrixBase<T, row_num, column_num>::operator()(const size_t &i, const size_t &j) const {
    return cells.begin() + (i * column_num + j);
}

template<typename T, size_t row_num, size_t column_num>
typename std::array<T, row_num * column_num>
        ::iterator MatrixBase<T, row_num, column_num>::operator()(const size_t &i, const size_t &j) {
    return cells.begin() + (i * column_num + j);
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
        &MatrixBase<T, row_num, column_num>::operator*=(const T &num) {
    std::transform(begin(), end(), begin(), [&num](T &i) { return i *= num; });
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
MatrixBase<T, row_num, column_num>::operator*(const T &num) {
    return MatrixBase<T, row_num, column_num>(*this) *= num;
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>
operator*=(const T &num, MatrixBase<T, row_num, column_num> &matrix) {
    return matrix *= num;
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>
operator*(const T &num, MatrixBase<T, row_num, column_num> &matrix) {
    return operator*=(num, matrix);
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
        &MatrixBase<T, row_num, column_num>::operator+=(const T &num) {
    std::transform(begin(), end(), begin(), [&num](T &i) { return i += num; });
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
MatrixBase<T, row_num, column_num>::operator+(const T &num) {
    return MatrixBase<T, row_num, column_num>(*this) += num;
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>
operator+=(const T &num, MatrixBase<T, row_num, column_num> &matrix) {
    return matrix += num;
}

template<typename T, size_t row_num, size_t column_num>
MatrixBase<T, row_num, column_num>
operator+(const T &num, MatrixBase<T, row_num, column_num> &matrix) {
    return operator+=(num, matrix);
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
        &MatrixBase<T, row_num, column_num>::operator-=(const T &num) {
    std::transform(begin(), end(), begin(), [&num](T &i) { return i -= num; });
    return *this;
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixBase<T, row_num, column_num>
MatrixBase<T, row_num, column_num>::operator-(const T &num) {
    return *this -= num;
}

template<typename T, size_t row_num, size_t column_num>
std::ostream &operator<<(std::ostream &out, MatrixBase<T, row_num, column_num> &matrix) {
    for (size_t i = 0; i < row_num; ++i) {
        out << "{ ";
        for (size_t j = 0; j < column_num; ++j) {
            out << *matrix(i, j) << " ";
        }
        out << "}\n";
    }
    return out;
}

template<typename T, size_t row_num, size_t column_num>
void swap(MatrixBase<T, row_num, column_num> &first,
          MatrixBase<T, row_num, column_num> &second) {
    first.cells.swap(second.cells);
}

template<typename T, size_t row_num, size_t column_num>
typename std::array<T, row_num * column_num>::const_iterator MatrixBase<T, row_num, column_num>::begin() const {
    return cells.begin();
}

template<typename T, size_t row_num, size_t column_num>
typename std::array<T, row_num * column_num>::const_iterator MatrixBase<T, row_num, column_num>::end() const {
    return cells.end();
}

template<typename T, size_t row_num, size_t column_num>
typename std::array<T, row_num * column_num>::iterator MatrixBase<T, row_num, column_num>::begin() {
    return cells.begin();
}

template<typename T, size_t row_num, size_t column_num>
typename std::array<T, row_num * column_num>::iterator MatrixBase<T, row_num, column_num>::end() {
    return cells.end();
}

template<typename T, size_t row_num, size_t column_num>
bool MatrixBase<T, row_num, column_num>::operator==(const MatrixBase &other) {
    return cells == other.cells;
}

template<typename T, size_t row_num, size_t column_num>
bool MatrixBase<T, row_num, column_num>::operator==(const std::array<T, row_num * column_num> &arr) {
    return cells == arr;
}

#endif//MATRIXCALC_MATRIXBASE_H
