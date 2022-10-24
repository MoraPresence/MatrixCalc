//
// Created by mora on 17.10.2022.
//

#ifndef MATRIXCALC_MATRIXINTERFACE_H
#define MATRIXCALC_MATRIXINTERFACE_H
#pragma once
#define defaultSize 1

#define ROW 100
#define COLUMN 200

#include <iostream>
#include <cmath>

/* Интерфейс матрицы */

template<typename T, size_t rows = defaultSize, size_t columns = defaultSize>
class MatrixInterface {
protected:
    uint32_t rowsCount = rows;
    uint32_t columnsCount = columns;
    T *cells;

public:

    MatrixInterface() {
        cells = new T[rows * columns];
    };

    MatrixInterface(uint32_t _rows, uint32_t _columns) {
        rowsCount = _rows;
        columnsCount = _columns;
        cells = new T[_rows * _columns];

        std::fill_n(cells, _rows * _columns, 0);
    };

    MatrixInterface(const MatrixInterface &other);

    MatrixInterface(MatrixInterface &&other) noexcept;

/**********************************************************************************************************************/

    MatrixInterface &operator=(const MatrixInterface &other);

    MatrixInterface &operator=(MatrixInterface &&other) noexcept;

    MatrixInterface &operator+(const MatrixInterface &other);

    MatrixInterface &operator+=(const MatrixInterface &other);

    MatrixInterface &operator-(const MatrixInterface &other);

    MatrixInterface &operator-=(const MatrixInterface &other);

    MatrixInterface &operator*(const MatrixInterface &other);

    MatrixInterface &operator*=(const MatrixInterface &other);

    inline T* operator[](uint32_t i) {
        return (cells + i*rowsCount);
    }


/**********************************************************************************************************************/

    [[nodiscard]] size_t getRowsCount() const { return rowsCount; }

    [[nodiscard]] size_t getColumnsCount() const { return columnsCount; }

    T *getCells() const { return cells; }

};

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns>::MatrixInterface(const MatrixInterface &other) {
    cells = new T[other.columnsCount * other.rowsCount];
    rowsCount = other.rowsCount;
    columnsCount = other.columnsCount;

    std::copy(other.cells, other.cells + (columnsCount * rowsCount), cells);
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns>::MatrixInterface(MatrixInterface &&other) noexcept {

    cells = other.cells;
    rowsCount = other.rowsCount;
    columnsCount = other.columnsCount;

    other.cells = nullptr;
    other.rowsCount = other.columnsCount = 0;
}

/**********************************************************************************************************************/
template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator=(const MatrixInterface &other) {
    delete[] cells;
    cells = new T[other.columnsCount * other.rowsCount];

    columnsCount = other.columnsCount;
    rowsCount = other.rowsCount;
    std::copy(other.cells, other.cells + columnsCount, cells);
    std::copy(other.cells, other.cells + (columnsCount * rowsCount), cells);
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator=(MatrixInterface &&other) noexcept {
    delete[] cells;
    cells = other.cells;

    columnsCount = other.columnsCount;
    rowsCount = other.rowsCount;

    other.cells = nullptr;
    other.rowsCount = other.columnsCount = 0;
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator+(const MatrixInterface &other) {
    if (rowsCount != other.getRowsCount() || columnsCount != other.getColumnsCount())
        throw std::runtime_error("Trying to add matrices of different size");
    for (unsigned i = 0; i < rowsCount * columnsCount; ++i) {
        cells[i] += other.cells[i];
    }
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator+=(const MatrixInterface &other) {
    return *this = *this + other;
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator-(const MatrixInterface &other) {
    if (rowsCount != other.getRowsCount() || columnsCount != other.getColumnsCount())
        throw std::runtime_error("Trying to add matrices of different size");
    for (unsigned i = 0; i < rowsCount * columnsCount; ++i) {
        cells[i] -= other.cells[i];
    }
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator-=(const MatrixInterface &other) {
    return *this = *this - other;
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator*(const MatrixInterface &other) {
    if (rowsCount != other.getRowsCount() || columnsCount != other.getColumnsCount())
        throw std::runtime_error("Trying to add matrices of different size");
    for (unsigned i = 0; i < rowsCount * columnsCount; ++i) {
        cells[i] *= other.cells[i];
    }
    return *this;
}

template<typename T, size_t rows, size_t columns>
MatrixInterface<T, rows, columns> &MatrixInterface<T, rows, columns>::operator*=(const MatrixInterface &other) {
    return *this = *this * other;
}

template<typename T, size_t rows, size_t columns>
std::ostream &operator<<(std::ostream &out, MatrixInterface<T, rows, columns> &matrix) {
    for (int i = 0; i < matrix.getRowsCount(); ++i) {
        out << "{ ";
        for (int j = 0; j < matrix.getColumnsCount(); ++j) {
            out << *(matrix.getCells() + i * matrix.getRowsCount() + j) << " ";
        }
        out << "}\n";
    }
    return out;
}
/**********************************************************************************************************************/
#endif //MATRIXCALC_MATRIXINTERFACE_H
