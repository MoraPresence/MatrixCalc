// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIX_H
#define MATRIXCALC_MATRIX_H

#include <iostream>
#include "MatrixBase.h"
#include "MatrixColumn.h"
#include "MatrixRow.h"
#include "MatrixSlice.h"

template<typename T, size_t rowsCount, size_t columnsCount>
class Matrix : public MatrixBase<T, rowsCount, columnsCount> {
    using MatrixBase<T, rowsCount, columnsCount>::MatrixBase;
public:
    using MatrixBase<T, rowsCount, columnsCount>::operator+=;

    using MatrixBase<T, rowsCount, columnsCount>::operator+;

    using MatrixBase<T, rowsCount, columnsCount>::operator-=;

    using MatrixBase<T, rowsCount, columnsCount>::operator-;

    using MatrixBase<T, rowsCount, columnsCount>::operator*=;

    using MatrixBase<T, rowsCount, columnsCount>::operator*;

    using MatrixBase<T, rowsCount, columnsCount>::operator=;

    using MatrixBase<T, rowsCount, columnsCount>::Begin;

    using MatrixBase<T, rowsCount, columnsCount>::End;

/************************************************constructors**********************************************************/
    Matrix() : MatrixBase<T, rowsCount, columnsCount>() {};

    Matrix(const Matrix &other) : MatrixBase<T, rowsCount, columnsCount>(other) {};

    Matrix(const MatrixBase<T, rowsCount, columnsCount> &other) : MatrixBase<T, rowsCount, columnsCount>(
            other) {};

    Matrix(std::initializer_list<MatrixRow<T, columnsCount>> list, size_t rows);

    ~Matrix();

/**********************************************************************************************************************/


/************************************************operators*************************************************************/
    friend std::ostream &operator
    <<<T, rowsCount, columnsCount>
    (std::ostream &, MatrixBase<T, rowsCount, columnsCount> &);

    MatrixColumn<T, rowsCount> operator*=(MatrixColumn<T, rowsCount> &other);

    MatrixColumn<T, rowsCount> operator*(MatrixColumn<T, rowsCount> &other);

    Matrix operator+=(MatrixRow<T, columnsCount> &other);

    Matrix operator+(MatrixRow<T, columnsCount> &other);

    Matrix operator-=(MatrixRow<T, columnsCount> &other);

    Matrix operator-(MatrixRow<T, columnsCount> &other);

    Matrix operator+=(MatrixColumn<T, rowsCount> &other);

    Matrix operator+(MatrixColumn<T, rowsCount> &other);

    Matrix operator-=(MatrixColumn<T, rowsCount> &other);

    Matrix operator-(MatrixColumn<T, rowsCount> &other);

/**********************************************************************************************************************/


/************************************************getters***************************************************************/
    MatrixRow<T, columnsCount> getRow(size_t rowNum);

    MatrixColumn<T, rowsCount> getColumn(size_t columnNum);

    MatrixRow<T, columnsCount> getDiagonal();
/**********************************************************************************************************************/


/************************************************functions*************************************************************/
    Matrix<T, rowsCount, columnsCount> transpose();

    MatrixColumn<T, rowsCount> multiply(MatrixColumn<T, rowsCount> &other);

    MatrixRow<T, columnsCount> multiply(MatrixRow<T, columnsCount> &other);

    Matrix<T, rowsCount, columnsCount> add(MatrixRow<T, columnsCount> &matrix);

    Matrix<T, rowsCount, columnsCount> add(MatrixColumn<T, columnsCount> &matrix);

    Matrix<T, rowsCount, columnsCount> subtract(MatrixRow<T, columnsCount> &matrix);

    Matrix<T, rowsCount, columnsCount> subtract(MatrixColumn<T, columnsCount> &matrix);

    MatrixSlice<T> Slice(size_t start, size_t end);

    T getDeterminant(size_t size);

    Matrix getAdjoint();

    Matrix invert();

    Matrix multiply(Matrix &matrix);
/**********************************************************************************************************************/
};


/************************************************constructors**********************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount>::Matrix(std::initializer_list<MatrixRow<T, columnsCount>> list, const size_t rows) {
    size_t i = 0;
    for (MatrixRow<T, columnsCount> row: list) {
        std::copy(row.Begin(), row.End(), this->Begin() + rowsCount * i);
        ++i;
    }
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns>::~Matrix() = default;

/**********************************************************************************************************************/


/************************************************operators*************************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
MatrixColumn<T, rowsCount> Matrix<T, rowsCount, columnsCount>::operator*=(MatrixColumn<T, rowsCount> &other) {
    return Matrix<T, columnsCount, columnsCount>(*this).multiply(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixColumn<T, rowsCount> Matrix<T, rowsCount, columnsCount>::operator*(MatrixColumn<T, rowsCount> &other) {
    return operator*=(other);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator*=(MatrixBase<T, columnsCount, columnsCount> &other) {
    return Matrix<T, columnsCount, columnsCount>(other).multiply(*this);
}

template<typename T, size_t columnsCount>
MatrixRow<T, columnsCount> MatrixRow<T, columnsCount>::operator*(MatrixBase<T, columnsCount, columnsCount> &other) {
    return operator*=(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+=(MatrixRow<T, columnsCount> &other) {
    return this->add(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+(MatrixRow<T, columnsCount> &other) {
    return this->operator+=(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-=(MatrixRow<T, columnsCount> &other) {
    return this->subtract(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-(MatrixRow<T, columnsCount> &other) {
    return this->operator-=(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+=(MatrixColumn<T, rowsCount> &other) {
    return this->add(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator+(MatrixColumn<T, rowsCount> &other) {
    return this->operator+=(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-=(MatrixColumn<T, rowsCount> &other) {
    return this->subtract(other);
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::operator-(MatrixColumn<T, rowsCount> &other) {
    return this->operator-=(other);
}
/**********************************************************************************************************************/


/************************************************getters***************************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
MatrixRow<T, columnsCount> Matrix<T, rowsCount, columnsCount>::getRow(size_t rowNum) {
    if (rowsCount <= rowNum) {
        throw std::runtime_error("No such row exists");
    }
    MatrixRow<T, columnsCount> tmp;
    std::copy(this->cells.begin() + (rowNum * rowsCount), this->cells.begin() + (rowNum * rowsCount + columnsCount),
              tmp.Begin());
    return tmp;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixColumn<T, rowsCount> Matrix<T, rowsCount, columnsCount>::getColumn(size_t columnNum) {
    if (columnsCount <= columnNum) {
        throw std::runtime_error("No such row exists");
    }
    auto transposed = this->transpose();
    MatrixColumn<T, columnsCount> tmp;
    std::copy(transposed.Begin() + (columnNum * transposed.getRowsCount()),
              transposed.Begin() + (columnNum * transposed.getRowsCount() + transposed.getColumnsCount()),
              tmp.Begin());
    return tmp;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixRow<T, columnsCount> Matrix<T, rowsCount, columnsCount>::getDiagonal() {
    static_assert(rowsCount == columnsCount);

    MatrixRow<T, columnsCount> diagonal;

    std::copy_if(this->Begin(), this->End(), diagonal.Begin(), [](T &i) { return i % (rowsCount + 1) == 0; });

    return diagonal;
}
/**********************************************************************************************************************/


/************************************************functions*************************************************************/
template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::transpose() {
    Matrix<T, columnsCount, rowsCount> transponse(*this);
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = i + 1; j < columnsCount; ++j) {
            std::swap(*(transponse(j, i)), *(transponse(i, j)));
        }
    }
    return transponse;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::multiply(Matrix &matrix) {
    Matrix<T, rows, columns> res;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < matrix.getColumnsCount(); ++j) {
            for (size_t q = 0; q < columns; ++q) {
                *res(i, j) += *(*this)(i, q) * *matrix(q, j);
            }
        }
    }
    return res;
}

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
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::add(MatrixRow<T, columnsCount> &matrix) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(i, j) += *(*this)(i, j) + *matrix(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::add(MatrixColumn<T, columnsCount> &matrix) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(j, i) += *(*this)(j, i) + *matrix(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::subtract(MatrixRow<T, columnsCount> &matrix) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(i, j) += *(*this)(i, j) - *matrix(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount>
Matrix<T, rowsCount, columnsCount>::subtract(MatrixColumn<T, columnsCount> &matrix) {
    Matrix<T, rowsCount, columnsCount> res;
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; ++j) {
            *res(j, i) += *(*this)(j, i) - *matrix(j);
        }
    }
    return res;
}

template<typename T, size_t rowsCount, size_t columnsCount>
MatrixSlice<T> Matrix<T, rowsCount, columnsCount>::Slice(size_t start, size_t end) {
    if (end > rowsCount * columnsCount)
        throw std::runtime_error("Slice out of range");

    return MatrixSlice<T>(this->Begin() + start, start, end, this->cells.size());
}

template<typename T, size_t rowsCount, size_t columnsCount>
void getCofactor(Matrix<T, rowsCount, columnsCount> mat, Matrix<T, rowsCount, columnsCount> &temp, size_t rowSrc,
                 size_t columnSrc, size_t size) {
    size_t i = 0, j = 0;

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
    if (rowsCount != columnsCount)
        throw std::runtime_error("Trying to calculate det of non-square matrix");
    if (size == 1)
        return *(*this)(0, 0);
    if (size == 2)
        return *(*this)(0, 0) * *(*this)(1, 1) - *(*this)(0, 1) * *(*this)(1, 0);
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
    size_t size = columnsCount;

    if (size == 1) {
        *adj(0, 0) = 1;
        return adj;
    }
    Matrix<T, rowsCount, columnsCount> sMatrix;

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            getCofactor((*this), sMatrix, i, j, size);
            *adj(j, i) = (T) (std::pow(-1, 2 + (i + j)) * (sMatrix.getDeterminant(size - 1)));
        }
    }
    return adj;
}

template<typename T, size_t rowsCount, size_t columnsCount>
Matrix<T, rowsCount, columnsCount> Matrix<T, rowsCount, columnsCount>::invert() {
    if (rowsCount != columnsCount)
        throw std::runtime_error("Trying to inverse a non-square matrix");

    auto det = this->getDeterminant(columnsCount);
    if (det == 0)
        throw std::runtime_error("getDeterminant is zero");

    Matrix<T, rowsCount, columnsCount> inv;

    auto adj = this->getAdjoint();

    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < columnsCount; j++) {
            *inv(i, j) = *adj(i, j) / det;
        }
    }
    return inv;
}
/**********************************************************************************************************************/
#endif //MATRIXCALC_MATRIX_H
