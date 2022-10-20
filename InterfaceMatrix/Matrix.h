//
// Created by mora on 17.10.2022.
//

#ifndef MATRIXCALC_MATRIX_H
#define MATRIXCALC_MATRIX_H

#include <iostream>
#include <cstring>
#include "MatrixInterface.h"


template<typename T, size_t rows = defaultSize, size_t columns = defaultSize>
class Matrix : public MatrixInterface<T, rows, columns> {
    using MatrixInterface<T, rows, columns>::cells;
    using MatrixInterface<T, rows, columns>::rowsCount;
    using MatrixInterface<T, rows, columns>::columnsCount;
public:
    using MatrixInterface<T, rows, columns>::MatrixInterface;
    using MatrixInterface<T, rows, columns>::getRowsCount;
    using MatrixInterface<T, rows, columns>::getColumnsCount;

    template<typename K>
    class MatrixInstance : MatrixInterface<T, rows, columns> {
        using MatrixInterface<T, rows, columns>::cells;
        using MatrixInterface<T, rows, columns>::rowsCount;
        using MatrixInterface<T, rows, columns>::columnsCount;
        using MatrixInterface<T, rows, columns>::MatrixInterface;

    public:
        explicit MatrixInstance(uint32_t _columns) {
            rowsCount = defaultSize;
            columnsCount = _columns;
            cells = new T[columnsCount];
            std::fill_n(cells, columnsCount, 0);
        };

        MatrixInstance(T *_cells, uint32_t _columns) {
            rowsCount = defaultSize;
            columnsCount = _columns;
            cells = _cells;
        };

        MatrixInstance(const MatrixInstance &other) {
            rowsCount = defaultSize;
            columnsCount = other.columnsCount;
            cells = new T[other.columnsCount];

            std::copy(other.cells, other.cells + columnsCount, cells);
        };


        MatrixInstance &operator=(const MatrixInstance &other) {
            delete[]cells;

            rowsCount = defaultSize;
            columnsCount = other.columnsCount;
            cells = new T[other.columnsCount];

            std::copy(other.cells, other.cells + columnsCount, cells);
            return *this;
        }

        void fill(uint32_t n, T arr[])  {
            if (rowsCount * columnsCount != n) throw std::runtime_error("wrong fill matrix");
            for (int i = 0; i < n; ++i) {
                cells[i] = arr[i];
            }
        }

        [[nodiscard]] size_t getLen() const { return columnsCount; }

        inline K operator[](uint32_t c) {
            return cells[c];
        }

        Matrix multiply(MatrixInstance<T &> &matrix) {
            Matrix res(getLen(), matrix.getLen());
            for (uint32_t i = 0; i < getLen(); ++i) {
                for (uint32_t j = 0; j < matrix.getLen(); ++j) {
                    res[i][j] += (*this)[i] * matrix[j];
                }
            }
            return res;
        }


        MatrixInterface<T, rows, columns> addition(T num) {
            MatrixInstance<T &> res(getLen());
            for (uint32_t i = 0; i < getLen(); ++i) {
                res[i] += (*this)[i] + num;
            }
            return res;
        }

        MatrixInterface<T, rows, columns> subtraction(T num) {
            MatrixInstance<T &> res(getLen());
            for (uint32_t i = 0; i < getLen(); ++i) {
                res[i] += (*this)[i] - num;
            }
            return res;
        }

        friend std::ostream &operator<<(std::ostream &out, MatrixInstance &matrix) {
            out << "{ ";
            for (int i = 0; i < matrix.columnsCount; ++i) {
                out << matrix[i] << " ";
            }
            out << "}\n";
            return out;
        }
    };

    inline MatrixInstance<T &> operator[](uint32_t i) {
        return MatrixInstance<T &>(this->cells + i * columnsCount, columnsCount);
    }

    inline MatrixInstance<const T &> operator[](uint32_t i) const {
        return MatrixInstance<const T &>(this->cells + i * columnsCount, columnsCount);
    }

    MatrixInstance<T &> getRow(size_t rowNum);

    MatrixInstance<T &> getColumn(size_t columnNum);

    MatrixInstance<T &> getDiagonal();

    Matrix transposed() const;

    void fill(uint32_t i, MatrixInstance<T &> row);

    void fill(uint32_t n, T arr[]);

    MatrixInstance<T &> multiply(MatrixInstance<T &> &other);

    Matrix<T, rows, columns> multiply(T num);

    Matrix<T, rows, columns> addition(MatrixInstance<T &> &other, uint32_t mode);

    Matrix<T, rows, columns> subtraction(MatrixInstance<T &> &other, uint32_t mode);

    MatrixInstance<T &> Slice(size_t start, size_t end);

    T determinant();

    Matrix adjoint();

    Matrix inverted();

    Matrix multiply(Matrix &matrix);

    Matrix addition(T num);

    Matrix subtraction(T num);

    Matrix subMatrix(size_t delRow, size_t delColumn);

    ~Matrix();
};

template<typename T, size_t rows, size_t columns>
 std::ostream &operator<<(std::ostream &out, Matrix<T, rows, columns> &matrix) {
    for (int i = 0; i < matrix.getRowsCount(); ++i) {
        out << "{ ";
        for (int j = 0; j < matrix.getColumnsCount(); ++j) {
            out << matrix[i][j] << " ";
        }
        out << "}\n";
    }
    return out;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns>::~Matrix() {
    delete[] cells;
}

template<typename T, size_t rows, size_t columns>
void Matrix<T, rows, columns>::fill(uint32_t i, MatrixInstance<T &> row) {
    //if (getRowsCount() != row.getLen()) throw std::runtime_error("wrong fill matrix");
    if (i + row.getLen() > getRowsCount() * getColumnsCount()) throw std::runtime_error("wrong fill matrix");
    for (int j = 0; j <= getRowsCount(); ++j) {
        cells[i + j] = row[j];
    }
}

template<typename T, size_t rows, size_t columns>
typename Matrix<T, rows, columns>::template MatrixInstance<T &> Matrix<T, rows, columns>::getRow(size_t rowNum) {
    auto tmp = MatrixInstance<T &>(this->cells + rowNum * columnsCount, columnsCount);//why are you g...???
    return MatrixInstance<T &>(tmp);
    //Хорошо ли вызвать конструктор в конструктуре, чтобы вернуть копию?
}

template<typename T, size_t rows, size_t columns>
typename Matrix<T, rows, columns>::template MatrixInstance<T &> Matrix<T, rows, columns>::getColumn(size_t columnNum) {
    auto transposed = this->transposed();
    auto tmp = MatrixInstance<T &>(transposed.getCells() + columnNum * getRowsCount(), getRowsCount());//why are you g...???
    return MatrixInstance<T &>(tmp);
}

template<typename T, size_t rows, size_t columns>
typename Matrix<T, rows, columns>::template MatrixInstance<T &> Matrix<T, rows, columns>::getDiagonal() {
    uint32_t size = 0;
    getRowsCount() < getColumnsCount() ? size = getRowsCount() : size = getColumnsCount();
    MatrixInstance<T &> diagonal(size);
    for (size_t i = 0; i < size; ++i) {
        diagonal[i] = (*this)[i][i];
    }
    return diagonal;
}

template<typename T, size_t rows, size_t columns>
typename Matrix<T, rows, columns>::template MatrixInstance<T &>
Matrix<T, rows, columns>::multiply(MatrixInstance<T &> &matrix) {
    MatrixInstance<T &> res(matrix.getLen());
    for (unsigned i = 0; i < matrix.getLen(); ++i) {
        for (unsigned q = 0; q < getColumnsCount(); ++q) {
            res[i] += (*this)[i][q] * matrix[q];
        }
    }
    return res;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::multiply(T num) {
    Matrix res(getRowsCount(), getColumnsCount());
    for (unsigned i = 0; i < getRowsCount(); ++i) {
        for (unsigned j = 0; j < getColumnsCount(); ++j) {
            res[i][j] += (*this)[i][j] * num;
        }
    }
    return res;
}


template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::addition(MatrixInstance<T &> &matrix, uint32_t mode) {
    Matrix res(getRowsCount(), getColumnsCount());
    if (mode == ROW) {
        for (unsigned i = 0; i < getRowsCount(); ++i) {
            for (unsigned j = 0; j < getColumnsCount(); ++j) {
                res[i][j] += (*this)[i][j] + matrix[j];
            }
        }
        return res;
    } else {
        for (unsigned i = 0; i < getRowsCount(); ++i) {
            for (unsigned j = 0; j < getColumnsCount(); ++j) {
                res[j][i] += (*this)[j][i] + matrix[j];
            }
        }
        return res;
    }
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::subtraction(MatrixInstance<T &> &matrix, uint32_t mode) {
    Matrix res(getRowsCount(), getColumnsCount());
    if (mode == ROW) {
        for (unsigned i = 0; i < getRowsCount(); ++i) {
            for (unsigned j = 0; j < getColumnsCount(); ++j) {
                res[i][j] += (*this)[i][j] - matrix[j];
            }
        }
        return res;
    } else {
        for (unsigned i = 0; i < getRowsCount(); ++i) {
            for (unsigned j = 0; j < getColumnsCount(); ++j) {
                res[j][i] += (*this)[j][i] - matrix[j];
            }
        }
        return res;
    }
}

template<typename T, size_t rows, size_t columns>
typename Matrix<T, rows, columns>::template MatrixInstance<T &>
Matrix<T, rows, columns>::Slice(size_t start, size_t end) {
    if (start < 0 || end > getRowsCount() * getColumnsCount())
        throw std::runtime_error("Slice out of range");
    return MatrixInstance<T &>(this->cells + start, end - start + 1);
}


template<typename T, size_t rows, size_t columns>
T Matrix<T, rows, columns>::determinant() {
    if (getColumnsCount() != getRowsCount())
        throw std::runtime_error("Trying to calculate det of non-square matrix");
    if (getRowsCount() == 1 && getColumnsCount() == 1)
        return (*this)[0][0];
    if (getRowsCount() == 2 && getColumnsCount() == 2)
        return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
    T result = 0;
    for (size_t i = 0; i < getColumnsCount(); ++i) {
        auto subMatrix = this->subMatrix(i, 0);
        result += std::pow(-1, 2 + i) * (*this)[i][0] * subMatrix.determinant();
    }
    return result;
}


template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::adjoint() {
    Matrix adj(getRowsCount(), getColumnsCount());

    int32_t sign = 1;

    for (size_t i = 0; i < getRowsCount(); i++) {
        for (size_t j = 0; j < getRowsCount(); j++) {
            auto tmp = subMatrix(i, j);
            adj[j][i] = std::pow(-1, 2 + (i + j)) * (tmp.determinant());
        }
    }
    return adj;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::inverted() {
    if (getRowsCount() != getColumnsCount())
        throw std::runtime_error("Trying to inverse a non-square matrix");

    auto det = this->determinant();
    if (det == 0)
        throw std::runtime_error("determinant is zero");

    Matrix inv(getRowsCount(), getColumnsCount());

    auto adj = this->adjoint();

    for (uint32_t i = 0; i < getRowsCount(); ++i) {
        for (uint32_t j = 0; j < getColumnsCount(); j++) {
            inv[i][j] = adj[i][j] / det;
        }
    }
    return inv;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::multiply(Matrix &matrix) {
    Matrix res(getRowsCount(), matrix.getColumnsCount());
    for (unsigned i = 0; i < getRowsCount(); ++i) {
        for (unsigned j = 0; j < matrix.getColumnsCount(); ++j) {
            for (unsigned q = 0; q < getColumnsCount(); ++q) {
                res[i][j] += (*this)[i][q] * matrix[q][j];
            }
        }
    }
    return res;
}


template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::addition(T num) {
    Matrix res(getRowsCount(), getColumnsCount());
    for (unsigned i = 0; i < getRowsCount(); ++i) {
        for (unsigned j = 0; j < getColumnsCount(); ++j) {
            res[i][j] += (*this)[i][j] + num;
        }
    }
    return res;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::subtraction(T num) {
    Matrix res(getRowsCount(), getColumnsCount());
    for (unsigned i = 0; i < getRowsCount(); ++i) {
        for (unsigned j = 0; j < getColumnsCount(); ++j) {
            res[i][j] += (*this)[i][j] - num;
        }
    }
    return res;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::subMatrix(size_t delRow, size_t delColumn) {
    Matrix res(getRowsCount() - 1, getColumnsCount() - 1);
    size_t i = 0, j = 0;
    for (size_t row = 0; row < getRowsCount(); ++row) {
        for (size_t column = 0; column < getColumnsCount(); ++column) {
            if (row != delRow && column != delColumn) {
                res[i][j++] = (*this)[row][column];
                if (j == getRowsCount() - 1) {
                    j = 0;
                    ++i;
                }
            }
        }
    }
    return res;
}

template<typename T, size_t rows, size_t columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::transposed() const {
    Matrix res(columnsCount, rowsCount);

    for (size_t i = 0; i < rowsCount; ++i)
        for (size_t j = 0; j < columnsCount; ++j)
            res[j][i] = (*this)[i][j];

    return res;
}

template<typename T, size_t rows, size_t columns>
void Matrix<T, rows, columns>::fill(uint32_t n, T arr[]) {
    if (getRowsCount() * getColumnsCount() != n) throw std::runtime_error("wrong fill matrix");
    for (int i = 0; i < n; ++i) {
        cells[i] = arr[i];
    }
}

#endif //MATRIXCALC_MATRIX_H
