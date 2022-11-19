// Copyright 2022 mora

#ifndef MATRIXCALC_MATRIXSLICE_H
#define MATRIXCALC_MATRIXSLICE_H

#include <iostream>

template<typename T>
class MatrixSlice;

template<typename T>
std::ostream &operator<<(std::ostream &, MatrixSlice<T> &);

template<typename T>
class MatrixSlice {
public:
    MatrixSlice();
    MatrixSlice(T *elem, size_t start, size_t end, size_t size);
    uint32_t getLen() { return _len; }
    ~MatrixSlice();
    T operator()(const size_t &i);

private:
    size_t _cap;
    size_t _len;
    T *_ptrArr;
};

template<typename T>
MatrixSlice<T>::MatrixSlice() : _cap(0), _len(0), _ptrArr(nullptr)
{
}

template<typename T>
MatrixSlice<T>::MatrixSlice(T *elem, size_t start, size_t end, size_t size)
    : _cap(size), _len(end - start), _ptrArr(elem)
{
}

template<typename T>
MatrixSlice<T>::~MatrixSlice() {
    _cap = 0;
    _len = 0;

    _ptrArr = nullptr;
}

template<typename T>
T MatrixSlice<T>::operator()(const size_t &i) {
    if (i >= _len){
        throw std::runtime_error("Out of slice");
    }
    return _ptrArr[i];
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const MatrixSlice<T> &slice) {
    out << "{ ";
    for (size_t i = 0; i < slice.getLen(); ++i) {
        out << slice(i) << " ";
    }
    out << "}\n";
    return out;
}

#endif//MATRIXCALC_MATRIXSLICE_H
