// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIX_H
#define MATRIXCALC_MATRIX_H

#include "MatrixBase.h"
#include "MatrixColumn.h"
#include "MatrixRow.h"
#include "MatrixSlice.h"

#include <iostream>

template<typename T, size_t rowsCount, size_t columnsCount>
class Matrix : public MatrixBase<T, rowsCount, columnsCount> {
private:
    using MatrixBase<T, rowsCount, columnsCount>::MatrixBase;

public:
    using MatrixBase<T, rowsCount, columnsCount>::operator+=;

    using MatrixBase<T, rowsCount, columnsCount>::operator+;

    using MatrixBase<T, rowsCount, columnsCount>::operator-=;

    using MatrixBase<T, rowsCount, columnsCount>::operator-;

    using MatrixBase<T, rowsCount, columnsCount>::operator*=;

    using MatrixBase<T, rowsCount, columnsCount>::operator*;

    using MatrixBase<T, rowsCount, columnsCount>::operator=;

    using MatrixBase<T, rowsCount, columnsCount>::operator==;

    using MatrixBase<T, rowsCount, columnsCount>::begin;

    using MatrixBase<T, rowsCount, columnsCount>::end;

/************************************************constructors**********************************************************/
    Matrix() : MatrixBase<T, rowsCount, columnsCount>() {};

    Matrix(const Matrix &other) : MatrixBase<T, rowsCount, columnsCount>(other) {};

    Matrix(const MatrixBase<T, rowsCount, columnsCount> &other) : MatrixBase<T, rowsCount, columnsCount>(
            other) {};

    Matrix(const MatrixBase<T, rowsCount, columnsCount> &&other) : MatrixBase<T, rowsCount, columnsCount>(
            other) {};

    Matrix(std::initializer_list<MatrixRow<T, columnsCount>> list);

    ~Matrix();

/**********************************************************************************************************************/


/************************************************operators*************************************************************/
    friend std::ostream &operator<<<T, rowsCount, columnsCount>
            (std::ostream &, MatrixBase<T, rowsCount, columnsCount> &);

    constexpr MatrixColumn<T, rowsCount> operator*=(MatrixColumn<T, rowsCount> &other);

    constexpr MatrixColumn<T, rowsCount> operator*(MatrixColumn<T, rowsCount> &other);

    constexpr Matrix operator+=(MatrixRow<T, columnsCount> &other);

    constexpr Matrix operator+(MatrixRow<T, columnsCount> &other);

    constexpr Matrix operator-=(MatrixRow<T, columnsCount> &other);

    constexpr Matrix operator-(MatrixRow<T, columnsCount> &other);

    constexpr Matrix operator+=(MatrixColumn<T, rowsCount> &other);

    constexpr Matrix operator+(MatrixColumn<T, rowsCount> &other);

    constexpr Matrix operator-=(MatrixColumn<T, rowsCount> &other);

    constexpr Matrix operator-(MatrixColumn<T, rowsCount> &other);

    constexpr Matrix &operator=(std::initializer_list<MatrixRow<T, columnsCount>> list);

/**********************************************************************************************************************/


/************************************************getters***************************************************************/
    MatrixRow<T, columnsCount> getRow(size_t rowNum);

    MatrixColumn<T, rowsCount> getColumn(size_t columnNum);

    MatrixRow<T, columnsCount> getDiagonal();

/**********************************************************************************************************************/


    Matrix<T, rowsCount, columnsCount> transpose();

    MatrixColumn<T, rowsCount> multiply(MatrixColumn<T, rowsCount> &other);

    MatrixRow<T, columnsCount> multiply(MatrixRow<T, columnsCount> &other);

    Matrix<T, rowsCount, columnsCount> add(MatrixRow<T, columnsCount> &other);

    Matrix<T, rowsCount, columnsCount> add(MatrixColumn<T, columnsCount> &other);

    Matrix<T, rowsCount, columnsCount> subtract(MatrixRow<T, columnsCount> &other);

    Matrix<T, rowsCount, columnsCount> subtract(MatrixColumn<T, columnsCount> &other);

    MatrixSlice<T> slice(size_t start, size_t stop);

    T getDeterminant(size_t size);

    Matrix getAdjoint();

    Matrix invert();

    Matrix multiply(Matrix &other);
};


/************************************************constructors**********************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount>::Matrix(std::initializer_list<MatrixRow<T, columnsCount>> list) {
    *this = list;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns>::~Matrix() = default;

/**********************************************************************************************************************/


/************************************************operators*************************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixColumn<T, rowsCount> Matrix<T, rowsCount, columnsCount>::operator*=(MatrixColumn<T, rowsCount> &other) {
    return multiply(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr MatrixColumn<T, rowsCount> Matrix<T, rowsCount, columnsCount>::operator*(MatrixColumn<T, rowsCount> &other) {
    return *this *= other;
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator*=(MatrixBase<T, columnsCount, columnsCount> &other) {
    return Matrix<T, columnsCount, columnsCount>(other).multiply(*this);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator*(MatrixBase<T, columnsCount, columnsCount> &other) {
    return *this *= other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+=(MatrixRow<T, columnsCount> &other) {
    return add(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+(MatrixRow<T, columnsCount> &other) {
    return *this += other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-=(MatrixRow<T, columnsCount> &other) {
    return subtract(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-(MatrixRow<T, columnsCount> &other) {
    return *this -= other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+=(MatrixColumn<T, rowsCount> &other) {
    return add(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+(MatrixColumn<T, rowsCount> &other) {
    return *this += other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-=(MatrixColumn<T, rowsCount> &other) {
    return subtract(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-(MatrixColumn<T, rowsCount> &other) {
    return *this -= other;
}

template<typename T, size_t rowsCount, size_t columnsCount>
constexpr Matrix<T, rowsCount, columnsCount> &
Matrix<T, rowsCount, columnsCount>::operator=(std::initializer_list<MatrixRow<T, columnsCount>> list) {
    size_t i = 0;
    for (MatrixRow<T, columnsCount> row: list) {
        std::copy(row.begin(), row.end(), this->begin() + rowsCount * i);
        ++i;
    }
    return *this;
}
/**********************************************************************************************************************/


/************************************************getters***************************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
MatrixRow<T, columnsCount> Matrix<T, rowsCount, columnsCount>::getRow(const size_t rowNum) {
    MatrixRow<T, columnsCount> tmp;

    if (rowsCount > rowNum) {
        std::copy(this->begin() + (rowNum * rowsCount), this->begin() + (rowNum * rowsCount + columnsCount),
                  tmp.begin());
    }

    return tmp;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixColumn<T, rowsCount> Matrix<T, rowsCount, columnsCount>::getColumn(const size_t columnNum) {
    MatrixColumn<T, columnsCount> tmp;

    if (columnsCount > columnNum) {
        auto transposed = this->transpose();

        std::copy(transposed.begin() + (columnNum * transposed.getRowsCount()),
                  transposed.begin() + (columnNum * transposed.getRowsCount() + transposed.getColumnsCount()),
                  tmp.begin());
    }

    return tmp;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixRow<T, columnsCount> Matrix<T, rowsCount, columnsCount>::getDiagonal() {
    static_assert(rowsCount == columnsCount);

    MatrixRow<T, columnsCount> diagonal;

    for (size_t i = 0; i < rowsCount; ++i) {
        *diagonal(i) = *(*this)(i, i);
    }

    return diagonal;
}

/**********************************************************************************************************************/


template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::transpose() {
    Matrix<T, columnsCount, rowsCount> transposed(*this);
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = i + 1; j < columnsCount; ++j) {
            std::swap(*(transposed(j, i)), *(transposed(i, j)));
        }
    }
    return transposed;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::multiply(Matrix &other) {
    Matrix<T, rowsCount, columnsCount> res;

    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < other.getColumnsCount(); ++j) {
            for (size_t k = 0; k < columnsCount; ++k) {
                *res(i, j) += *(*this)(i, k) * *other(k, j);
            }
        }
    }
    return res;
}


//template<typename T, size_t rowsCount, size_t columnsCount>
//void Matrix<T, rowsCount, columnsCount>::__mult__(MatrixBase<T, rowsCount, columnsCount> &res,
//                                                  const MatrixBase<T, rowsCount, columnsCount> &other,
//                                                  const bool MODE) {
//    for (size_t i = 0; i < rowsCount; ++i) {
//        for (size_t j = 0; j < columnsCount; ++j) {
//            if (MODE == IS_ROW) {
//                *res(i) += *(*this)(j, i) * *other(j);
//            } else {
//                *res(i) += *(*this)(i, j) * *other(j);
//            }
//        }
//    }
//}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixColumn<T, rowsCount> Matrix<T, rowsCount, columnsCount>::multiply(MatrixColumn<T, rowsCount> &other) {
    MatrixColumn<T, rowsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(i) += *(*this)(i, j) * *other(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixRow<T, columnsCount> Matrix<T, rowsCount, columnsCount>::multiply(MatrixRow<T, columnsCount> &other) {
    MatrixRow<T, columnsCount> res;
    for (size_t i = 0; i < columnsCount; ++i) {
        for (size_t j = 0; j < rowsCount; ++j) {
            *res(i) += *(*this)(j, i) * *other(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::add(MatrixRow<T, columnsCount> &other) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(i, j) += *(*this)(i, j) + *other(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::add(MatrixColumn<T, columnsCount> &other) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(j, i) += *(*this)(j, i) + *other(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::subtract(MatrixRow<T, columnsCount> &other) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(i, j) += *(*this)(i, j) - *other(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount>
Matrix<T, rowsCount, columnsCount>::subtract(MatrixColumn<T, columnsCount> &other) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(j, i) += *(*this)(j, i) - *other(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixSlice<T> Matrix<T, rowsCount, columnsCount>::slice(size_t start, size_t stop) {
    if (stop > rowsCount * columnsCount) {
        throw std::runtime_error("slice out of range");
    }

    return MatrixSlice<T>(this->begin() + start, start, stop, this->cells.size());
}

template<typename T, size_t rowsCount, size_t columnsCount>
void getCofactor(Matrix<T, rowsCount, columnsCount> mat, Matrix<T, rowsCount, columnsCount> &temp, size_t rowSrc,
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

template<typename T, size_t rowsCount, size_t columnsCount>
T Matrix<T, rowsCount, columnsCount>::getDeterminant(size_t size) {
    static_assert(rowsCount == columnsCount);

    if (size == 1) {
        return *(*this)(0, 0);
    } else if (size == 2) {
        return *(*this)(0, 0) * *(*this)(1, 1) - *(*this)(0, 1) * *(*this)(1, 0);
    }

    T result = 0;
    Matrix<T, rowsCount, columnsCount> sMatrix;

    for (size_t i = 0; i < size; ++i) {
        getCofactor((*this), sMatrix, 0, i, size);
        result += (T) (std::pow(-1, 2 + i) * *(*this)(0, i)
                       * sMatrix.getDeterminant(size - 1));
    }

    return result;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::getAdjoint() {
    Matrix<T, rowsCount, columnsCount> adj;
    auto size = columnsCount;

    if (size == 1) {
        *adj(0, 0) = 1;
        return adj;
    }
    Matrix<T, rowsCount, columnsCount> subMatrix;

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            getCofactor((*this), subMatrix, i, j, size);
            *adj(j, i) = (T) (std::pow(-1, 2 + (i + j)) * (subMatrix.getDeterminant(size - 1)));
        }
    }
    return adj;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::invert() {
    static_assert(rowsCount == columnsCount);

    Matrix<T, rowsCount, columnsCount> inv;

    auto det = this->getDeterminant(columnsCount);

    if (det != 0) {
        auto adj = this->getAdjoint();

        for (size_t i = 0; i < rowsCount; ++i) {
            for (size_t j = 0; j < columnsCount; j++) {
                *inv(i, j) = *adj(i, j) / det;
            }
        }
    }
    return inv;
}

#endif //MATRIXCALC_MATRIX_H
