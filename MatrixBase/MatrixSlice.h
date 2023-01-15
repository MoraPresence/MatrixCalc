// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXSLICE_H
#define MATRIXCALC_MATRIXSLICE_H

#include <iostream>

template<size_t start, size_t end, typename T, size_t orig>
class MatrixSlice;

template<size_t start, size_t end, typename T, size_t orig>
std::ostream &operator<<(std::ostream &, MatrixSlice<start, end, T, orig> &);

template<size_t start, size_t end, typename T, size_t orig>
class MatrixSlice {
public:
    MatrixSlice() = delete;
    explicit MatrixSlice(std::array<T, orig> &arr);
    ~MatrixSlice() = default;

    typename std::array<T, end - start>
            ::const_iterator operator()(const size_t &i) const;
    typename std::array<T, end - start>
            ::iterator operator()(const size_t &i);
private:
    std::array<T, end - start> _arr;
};

template<size_t start, size_t end, typename T, size_t orig>
MatrixSlice<start, end, T, orig>::MatrixSlice(std::array<T, orig> &arr) {
    static_assert(end <= orig && start < orig,
                  "slice(array): array index out of bounds");

    _arr = *reinterpret_cast<std::array<T, end - start> *>(&arr[start]);
}

template<size_t start, size_t end, typename T, size_t orig>
typename std::array<T, end - start>
        ::const_iterator MatrixSlice<start, end, T, orig>
        ::operator()(const size_t &i) const {
    return _arr.begin() + i;
}

template<size_t start, size_t end, typename T, size_t orig>
typename std::array<T, end - start>::iterator MatrixSlice<start, end, T, orig>
        ::operator()(const size_t &i) {
    return _arr.begin() + i;
}

template<size_t start, size_t end, typename T, size_t orig>
std::ostream &operator<<(std::ostream &out,
                         const MatrixSlice<start, end, T, orig> &slice) {
    out << "{ ";
    for (size_t i = 0; i < slice.getLen(); ++i) {
        out << slice(i) << " ";
    }
    out << "}\n";
    return out;
}

#endif//MATRIXCALC_MATRIXSLICE_H
