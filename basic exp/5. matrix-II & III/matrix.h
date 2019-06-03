#pragma once
#include <cstdio>
#include <algorithm>
#include <iostream>

template <class T>
class Matrix {
    T* data;
    int row;
    int col;
public:
    Matrix();
    Matrix(int _row, int _col);
    Matrix(Matrix<T> &mat);
    ~Matrix();

    T& operator() (int _row, int _col);
    Matrix<T>& operator = (const Matrix& mat);
    template <class elementType>
    friend std::ostream& operator << (std::ostream& os, const Matrix<elementType>& mat) {
        os << '[' << '\n';
        for(int i = 0; i < mat.row; i++) {
            os << '[';
            for(int j = 0; j < mat.col; j++) {
                os << mat.data[i * mat.col + j];
                if(j != mat.col - 1)
                    os << ',';
            }
            os << "]," << '\n';
        }
        os << ']' << '\n';
        return os;
    }
    template <class elementType>
    friend std::istream& operator >> (std::istream& is, const Matrix<elementType>& mat){
        for(int i = 0; i < mat.row; i++)
            for(int j = 0; j < mat.col; j++)
                is >> mat.data[i * mat.col + j];
    }

    template <class elementType>
    friend Matrix<elementType> operator+ (Matrix<elementType>& matl, Matrix<elementType>& matr) {
        if(matl.col == matr.col && matl.row == matr.row) {
            Matrix<elementType> ans(matl);
            for(int i = 0; i < ans.row * ans.col; i++)
                ans.data[i] += matr.data[i];
            return ans;
        }
        else {
            std::cerr << "error dimension [operator +]" << '\n';
        }
    }

    template <class elementType>
    friend Matrix<elementType> operator- (Matrix<elementType>& matl, Matrix<elementType>matr) {
        if(matl.col == matr.col && matl.row == matr.row) {
            Matrix<elementType> ans(matl);
            for(int i = 0; i < ans.row * ans.col; i++)
                ans.data[i] -= matr.data[i];
            return ans;
        }
        else {
            std::cerr << "error dimension [operator +]" << '\n';
        }
    }

    template <class elementType>
    friend Matrix<elementType> operator* (Matrix<elementType>& mat, const elementType tar) {
        Matrix<elementType> ans(mat);
        for(int i = 0; i < mat.row * mat.col; i++)
            ans.data[i] *= tar;
        return ans;
    }

};
