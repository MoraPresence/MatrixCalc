// Copyright 2022 mora

#ifndef MATRIXBASE_MATRIX_H_
#define MATRIXBASE_MATRIX_H_

#include "MatrixBase.h"
#include "MatrixColumn.h"
#include "MatrixRow.h"
#include "MatrixSlice.h"

#include <algorithm>
#include <iostream>
#include <utility>

template<typename T, size_t row_num, size_t column_num>
class Matrix : public MatrixBase<T, row_num, column_num> {
 private:
    using MatrixBase<T, row_num, column_num>::MatrixBase;

 public:
    using MatrixBase<T, row_num, column_num>::operator+=;
    using MatrixBase<T, row_num, column_num>::operator+;
    using MatrixBase<T, row_num, column_num>::operator-=;
    using MatrixBase<T, row_num, column_num>::operator-;
    using MatrixBase<T, row_num, column_num>::operator*=;
    using MatrixBase<T, row_num, column_num>::operator*;
    using MatrixBase<T, row_num, column_num>::operator=;
    using MatrixBase<T, row_num, column_num>::operator==;
    using MatrixBase<T, row_num, column_num>::begin;
    using MatrixBase<T, row_num, column_num>::end;

    Matrix() : MatrixBase<T, row_num, column_num>() {}
    Matrix(const Matrix &other)
        : MatrixBase<T, row_num, column_num>(other) {}
    explicit Matrix(const MatrixBase<T, row_num, column_num> &other)
        : MatrixBase<T, row_num, column_num>(other) {}
    explicit Matrix(const MatrixBase<T, row_num, column_num> &&other)
        : MatrixBase<T, row_num, column_num>(other) {}
    Matrix(std::initializer_list<MatrixRow<T, column_num>> list);
    ~Matrix();


    constexpr MatrixColumn<T, row_num> operator*=
            (const MatrixColumn<T, row_num> &other);
    constexpr MatrixColumn<T, row_num> operator*
            (const MatrixColumn<T, row_num> &other);
    constexpr Matrix operator+=(const MatrixRow<T, column_num> &other);
    constexpr Matrix operator+(const MatrixRow<T, column_num> &other);
    constexpr Matrix operator-=(const MatrixRow<T, column_num> &other);
    constexpr Matrix operator-(const MatrixRow<T, column_num> &other);
    constexpr Matrix operator+=(const MatrixColumn<T, row_num> &other);
    constexpr Matrix operator+(const MatrixColumn<T, row_num> &other);
    constexpr Matrix operator-=(const MatrixColumn<T, row_num> &other);
    constexpr Matrix operator-(const MatrixColumn<T, row_num> &other);
    constexpr Matrix &operator=
            (std::initializer_list<MatrixRow<T, column_num>> list);


    MatrixRow<T, column_num> getRow(const size_t rowNum);
    MatrixColumn<T, row_num> getColumn(const size_t columnNum);
    MatrixRow<T, column_num> getDiagonal();
    Matrix<T, row_num, column_num> transpose();
    MatrixColumn<T, row_num> multiply(const MatrixColumn<T, row_num> &other);
    MatrixRow<T, column_num> multiply(const MatrixRow<T, column_num> &other);
    Matrix<T, row_num, column_num> add
            (const MatrixRow<T, column_num> &other);
    Matrix<T, row_num, column_num> add
            (const MatrixColumn<T, column_num> &other);
    Matrix<T, row_num, column_num> subtract
            (const MatrixRow<T, column_num> &other);
    Matrix<T, row_num, column_num> subtract
            (const MatrixColumn<T, column_num> &other);
    MatrixSlice<T> slice(const size_t start, const size_t stop);
    T getDeterminant(const size_t size);
    Matrix getAdjoint();
    Matrix invert();
    Matrix multiply(const Matrix &other);
};


template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num>
        ::Matrix(std::initializer_list<MatrixRow<T, column_num>> list) {
    *this = list;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num>::~Matrix() = default;

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixColumn<T, row_num>
        Matrix<T, row_num, column_num>
                ::operator*=(const MatrixColumn<T, row_num> &other) {
    return multiply(other);
}

template<typename T, size_t row_num, size_t column_num>
constexpr MatrixColumn<T, row_num>
        Matrix<T, row_num, column_num>
                ::operator*(const MatrixColumn<T, row_num> &other) {
    return *this *= other;
}

template<typename T, size_t column_num>
MatrixRow<T, column_num>
        MatrixRow<T, column_num>::operator*=
                (const MatrixBase<T, column_num, column_num> &other) {
    return Matrix<T, column_num, column_num>(other).multiply(*this);
}

template<typename T, size_t column_num>
MatrixRow<T, column_num> MatrixRow<T, column_num>::operator*
        (const MatrixBase<T, column_num, column_num> &other) {
    return *this *= other;
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator+=(const MatrixRow<T, column_num> &other) {
    return add(other);
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator+(const MatrixRow<T, column_num> &other) {
    return *this += other;
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator-=(const MatrixRow<T, column_num> &other) {
    return subtract(other);
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator-(const MatrixRow<T, column_num> &other) {
    return *this -= other;
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator+=(const MatrixColumn<T, row_num> &other) {
    return add(other);
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator+(const MatrixColumn<T, row_num> &other) {
    return *this += other;
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator-=(const MatrixColumn<T, row_num> &other) {
    return subtract(other);
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::operator-(const MatrixColumn<T, row_num> &other) {
    return *this -= other;
}

template<typename T, size_t row_num, size_t column_num>
constexpr Matrix<T, row_num, column_num> &
Matrix<T, row_num, column_num>::operator=
        (const std::initializer_list<MatrixRow<T, column_num>> list) {
    size_t i = 0;
    for (MatrixRow<T, column_num> row : list) {
        std::copy(row.begin(), row.end(), this->begin() + row_num * i);
        ++i;
    }
    return *this;
}

void single_loop_(
        size_t start_i,
        const size_t &size_i,
        const std::function<void(size_t)> &func) {
    for (size_t i = start_i; i < size_i; ++i) {
        func(i);
    }
}

void double_loop_(
        size_t start_i,
        size_t start_j,
        const size_t &size_i,
        const size_t &size_j,
        const std::function<void(size_t, size_t)> &func) {
    for (size_t i = start_i; i < size_i; ++i) {
        for (size_t j = start_j; j < size_j; ++j) {
            func(i, j);
        }
    }
}

void triple_loop_(
        size_t start_i,
        size_t start_j,
        size_t start_k,
        const size_t &size_i,
        const size_t &size_j,
        const size_t &size_k,
        const std::function<void(size_t, size_t, size_t)> &func) {
    for (size_t i = start_i; i < size_i; ++i) {
        for (size_t j = start_j; j < size_j; ++j) {
            for (size_t k = start_k; k < size_k; ++k) {
                func(i, j, k);
            }
        }
    }
}

template<typename T, size_t row_num, size_t column_num>
MatrixRow<T, column_num> Matrix<T, row_num, column_num>
        ::getRow(const size_t rowNum) {
    MatrixRow<T, column_num> tmp;

    if (row_num > rowNum) {
        std::copy(this->begin() + (rowNum * row_num),
                  this->begin() + (rowNum * row_num + column_num),
                  tmp.begin());
    }

    return tmp;
}

template<typename T, size_t row_num, size_t column_num>
MatrixColumn<T, row_num> Matrix<T, row_num, column_num>
        ::getColumn(const size_t columnNum) {
    MatrixColumn<T, column_num> tmp;

    if (column_num > columnNum) {
        auto transposed = this->transpose();

        std::copy(transposed.begin() + (columnNum * row_num),
                  transposed.begin() + (columnNum * row_num + column_num),
                  tmp.begin());
    }

    return tmp;
}

template<typename T, size_t row_num, size_t column_num>
MatrixRow<T, column_num> Matrix<T, row_num, column_num>::getDiagonal() {
    static_assert(row_num == column_num);
    MatrixRow<T, column_num> diagonal;
    single_loop_(0,  row_num, [&](size_t i)
                 { *diagonal(i) = *(*this)(i, i); });
    return diagonal;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::transpose() {
    Matrix<T, column_num, row_num> transposed(*this);
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = i + 1; j < column_num; ++j) {
            std::swap(*(transposed(j, i)), *(transposed(i, j)));
        }
    }
    return transposed;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::multiply(const Matrix &other) {
    Matrix<T, row_num, column_num> res;
    triple_loop_(0, 0, 0,
                 row_num, column_num, column_num,
                 [&](size_t i, size_t j, size_t k)
                 { *res(i, j) += *(*this)(i, k) * *other(k, j); });
    return res;
}


template<typename T, size_t row_num, size_t column_num>
MatrixColumn<T, row_num> Matrix<T, row_num, column_num>
        ::multiply(const MatrixColumn<T, row_num> &other) {
    MatrixColumn<T, row_num> res;
    double_loop_(0, 0, row_num, column_num,
                 [&](size_t i, size_t j)
                 { *res(i) += *(*this)(i, j) * *other(j); });
    return res;
}

template<typename T, size_t row_num, size_t column_num>
MatrixRow<T, column_num> Matrix<T, row_num, column_num>
        ::multiply(const MatrixRow<T, column_num> &other) {
    MatrixRow<T, column_num> res;
    double_loop_(0, 0, row_num, column_num,
                 [&](size_t i, size_t j)
                 { *res(i) += *(*this)(j, i) * *other(j); });
    return res;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::add(const MatrixRow<T, column_num> &other) {
    Matrix<T, row_num, column_num> res;
    double_loop_(0, 0, row_num, column_num,
                 [&](size_t i, size_t j)
                 { *res(i, j) += *(*this)(i, j) + *other(j); });
    return res;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::add(const MatrixColumn<T, column_num> &other) {
    Matrix<T, row_num, column_num> res;
    double_loop_(0, 0, row_num, column_num,
                 [&](size_t i, size_t j)
                 { *res(j, i) += *(*this)(j, i) + *other(j); });
    return res;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::subtract(const MatrixRow<T, column_num> &other) {
    Matrix<T, row_num, column_num> res;
    double_loop_(0, 0, row_num, column_num,
                 [&](size_t i, size_t j)
                 { *res(i, j) += *(*this)(i, j) - *other(j); });
    return res;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num>
Matrix<T, row_num, column_num>
        ::subtract(const MatrixColumn<T, column_num> &other) {
    Matrix<T, row_num, column_num> res;
    double_loop_(0, 0, row_num, column_num,
                 [&](size_t i, size_t j)
                 { *res(j, i) += *(*this)(j, i) - *other(j); });
    return res;
}

template<typename T, size_t row_num, size_t column_num>
MatrixSlice<T> Matrix<T, row_num, column_num>
        ::slice(size_t start, size_t stop) {
    if (stop > row_num * column_num) {
        throw std::runtime_error("slice out of range");
    }

    return MatrixSlice<T>(this->begin() + start, start, stop,
                          this->cells.size());
}

template<typename T, size_t row_num, size_t column_num>
void getCofactor(const Matrix<T, row_num, column_num> &mat,
                 Matrix<T, row_num, column_num> &temp,
                 size_t rowSrc,
                 size_t columnSrc, size_t size) {
    size_t i = 0;
    size_t j = 0;

    for (size_t row = 0; row < size; row++) {
        for (size_t col = 0; col < size; col++) {
            if (row != rowSrc && col != columnSrc) {
                *temp(i, j++) = *mat(row, col);
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

template<typename T, size_t row_num, size_t column_num>
T Matrix<T, row_num, column_num>::getDeterminant(size_t size) {
    static_assert(row_num == column_num);

    if (size == 1) {
        return *(*this)(0, 0);
    } else if (size == 2) {
        return *(*this)(0, 0) * *(*this)(1, 1)
               - *(*this)(0, 1) * *(*this)(1, 0);
    }

    T result = 0;
    Matrix<T, row_num, column_num> sMatrix;

    single_loop_(0,  size, [&](size_t i) {
        getCofactor((*this), sMatrix, 0, i, size);
        result += (T) (std::pow(-1, 2 + i)
                       * *(*this)(0, i)
                       * sMatrix.getDeterminant(size - 1));
    });

    return result;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>
        ::getAdjoint() {
    Matrix<T, row_num, column_num> adj;
    auto size = column_num;

    if (size == 1) {
        *adj(0, 0) = 1;
        return adj;
    }
    Matrix<T, row_num, column_num> subMatrix;

    double_loop_(0, 0, size, size,
                 [&](size_t i, size_t j) {
        getCofactor((*this), subMatrix, i, j, size);
        *adj(j, i) = (T) (std::pow(-1, 2 + (i + j))
                          * (subMatrix.getDeterminant(size - 1))); });

    return adj;
}

template<typename T, size_t row_num, size_t column_num>
Matrix<T, row_num, column_num> Matrix<T, row_num, column_num>::invert() {
    static_assert(row_num == column_num);

    Matrix<T, row_num, column_num> inv;

    auto det = this->getDeterminant(column_num);

    if (det != 0) {
        auto adj = this->getAdjoint();

        double_loop_(0, 0,
                     row_num, column_num,
                     [&](size_t i, size_t j)
                     {*inv(i, j) = *adj(i, j) / det; });
    }
    return inv;
}

#endif  // MATRIXBASE_MATRIX_H_
