#include "matrix.h"

template <class T>
Matrix<T>::Matrix() {
    row = 0;
    col = 0;
    data = nullptr;
}

template <class T>
Matrix<T>::Matrix(int _row, int _col) {
    this -> row = _row;
    this -> col = _col;
    data = new T [row * col];
}

template <class T>
Matrix<T>::~Matrix() {
    this -> row = 0;
    this -> col = 0;
    delete []data;
}

template <class T>
Matrix<T>::Matrix(Matrix& mat) {
    this -> col = mat.col;
    this -> row = mat.row;
    this -> data = new T[col * row];
    for(int i = 0; i < row * col; i++)
        data[i] = mat.data[i];
}

template <class T>
T& Matrix<T>::operator() (int _row, int _col) {
    return data[_row * col + _col];
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix& mat) {
    if(*this == mat)
        return *this;
    col = mat.col;
    row = mat.row;
    delete []data;
    data = new T[col * row];
    for(int i = 0; i < col * row; i++)
        data[i] = mat.data[i];
    return *this;
}
