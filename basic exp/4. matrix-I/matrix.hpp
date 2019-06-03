/*
    Date: 2018/2/24
    Author: Sheldon Zhang
    School: Beijing University of Posts and Telecommunications(BUPT)
    Description: A simple support for matrix
*/
#include <vector>
#include <iostream>
#include "cmath"
#include "complex.h"
using namespace std;

#define ROW_MAX 1000
#define COL_MAX 1000

template <typename T>
class matrix;

template <typename T>
istream & operator >> (istream &is, matrix<T> & obj);

template <typename T>
ostream & operator << (ostream &os, matrix<T> const & obj);

/*
Class Description: a class provides fundamental matrix storage and calculation
                   supported by vector in STL
*/
template <typename T>
class matrix
{
private:
    friend istream & operator >> <>(istream &is, matrix<T> & obj);
    friend ostream & operator << <>(ostream &os, matrix<T> const & obj);
private:
    int row, col;
    vector<vector<T>> data;
private:
    void zero();
public:
    matrix();
    matrix(int inputRow, int inputCol);
    matrix(const matrix<T> &obj);
    matrix(const matrix<T> *obj);
    ~matrix();

    matrix<T> operator + (const matrix<T> &rhs);
    matrix<T> operator - (const matrix<T> &rhs);
    matrix<T> operator * (const matrix<T> &rhs);
    matrix<T> & operator = (const matrix<T> &rhs);
    void operator *= (const matrix<T> &rhs);
    void operator += (const matrix<T> &rhs);
    void operator -= (const matrix<T> &rhs);
    void resize(int row, int col);
};
/*----------------------------------------------------*/
//IMPLEMENT
/*----------------------------------------------------*/
template <typename T>
/*
function name: istream & operator >>
description: overload operator >> (stream input)
arguments:
    istream &is: input stream object from which characters are extracted
    matrix<T> &obj: a referance of an object of class matrix
return value: the istream object(is)
*/
istream & operator >> (istream &is, matrix<T> &obj)
{
    for(int i = 0; i < obj.row; i++)
        for(int j = 0; j < obj.col; j++)
            is >> obj.data[i][j];
    return is;
}
template <typename T>
/*
function name: ostream & operator <<
description: overload operator <<
arguments:
    ostream &os: output stream object where characters are inserted
    matrix<T> const &obj: a referance of an object of class matrix
return value: the ostream object(os)
output format:
[
[ , ... , ]
[ , ... , ]
]
*/
ostream & operator << (ostream &os, matrix<T> const &obj)
{
    os << "[" << endl;
    for(int i = 0; i < obj.row; i++)
    {
        os << "[ ";
        for(int j = 0; j < obj.col; j++)
            os << obj.data[i][j] << " ";
    os << " ]" <<endl;
    }
    os << "]";
    return os;
}
template <typename T>
/*
function name: matrix
description: a constructor of class matrix
  1.set varible row and col to 0
  2.resize data to a 0 by 0 matrix
arguments: None
return value: None
*/
matrix<T>::matrix()
{
    row = 4; col = 5;
    data.resize(4, vector<T>(5));
}
template <typename T>
/*
function name: matrix
description: a constructor of class matrix
  1. check if the arguments are legal
  2. record the values of arguments
  3. allocate space for the matrix of the wanted dimention
  4. set all elements to 0
arguments:
  inputRow: the wanted row of the matrix
  inputCol: the wanted column of the matrix
return value: None
*/
matrix<T>::matrix(int inputRow, int inputCol)
{
    if(inputRow <= 0 || inputCol <= 0)
        std::cerr << "Invalid Parameter" << '\n';
    if(inputRow > ROW_MAX || inputCol > COL_MAX)
        std::cerr << "matrix is too large" << '\n';
    row = inputRow;
    col = inputCol;
    data.resize(row, vector<T>(col));
    zero();
}
template <typename T>
/*
function name: matrix
description: a copy constructor of class matrix
arguments: a referance of an object of class matrix
return value: None
*/
matrix<T>::matrix(const matrix<T> &obj)
{
    col = obj.col;
    row = obj.row;
    data.resize(row, vector<T>(col));
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            data[i][j] = obj.data[i][j];
}
template <typename T>
/*
function name: matrix
description: to create a copy of the matrix which the pointer points at
arguments: a pointer of class matrix
return value: None
*/
matrix<T>::matrix(const matrix<T> *obj)
{
    col = obj->col;
    row = obj->row;
    data.resize(row, vector<T>(col));
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            data[i][j] = obj->data[i][j];
}
template <typename T>
/*
function name: ~matrix
description: a destructor of class matrix
    1. set varible row and col to 0
    2. delete all elements in data
arguments: None
return value: None
*/
matrix<T>::~matrix()
{
    row = 0;
    col = 0;
    data.clear();
}
template <typename T>
/*
function name: zero
description: set all elements in data to 0
arguments: None
return value: None
*/
void matrix<T>::zero()
{
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col ;j++)
            data[i][j] = 0;
}
template <typename T>
/*
function name: matrix<T>::operator +
description: overload operator +
    1. check if the dimension of two matrices matches
    2. add the elements in the same localtion
      (add this->data[i][j] and rhs.data[i][j])
arguments: matrix<T> &rhs: a referance of an object of class matrix
return value: an object of class matrix
*/
matrix<T> matrix<T>::operator + (const matrix<T> &rhs)
{
    if(row != rhs.row || col != rhs.col)
          std::cerr << "the dimension is not the same" << '\n';
    matrix<T> matrixTemp(rhs.data.size(), rhs.data[0].size());
    for(int i = 0; i < rhs.data.size(); i++)
        for(int j = 0; j < rhs.data[0].size(); j++)
            matrixTemp.data[i][j] = this->data[i][j] + rhs.data[i][j];
    return matrixTemp;
}
template <typename T>
/*
function name: matrix<T>::operator -
description: overload operator -
    1. check if the dimension of two matrices matches
    2. subtruct this->data[i][j] by rhs.data[i][j]
arguments: matrix<T> &rhs: a referance of an object of class matrix
return value: an object of class matrix
*/
matrix<T> matrix<T>::operator - (const matrix<T> &rhs)
{
    if(row != rhs.row || col != rhs.col)
        std::cerr << "the dimension is not the same" << '\n';

    matrix<T> matrixTemp(rhs);
    for(int i = 0; i < rhs.data.size(); i++)
        for(int j = 0; j < rhs.data[0].size(); j++)
            matrixTemp.data[i][j] = this->data[i][j] - rhs.data[i][j];
    return matrixTemp;
}
template <typename T>
/*
function name: matrix<T>::operator *
description: overload operator *
    1. check if the dimension of two matrices matches
    2. do the multiple operation
arguments: matrix<T> &rhs: a referance of an object of class matrix
return value: an object of class matrix
*/
matrix<T> matrix<T>::operator * (const matrix<T> &rhs)
{
    if(this->data[0].size() != rhs.data.size())
        std::cerr << "matrix A can not be multiplied by matrix B" << '\n';
    matrix<T> matrixTemp(this->row, rhs.col);
    for(int i = 0; i < this->row; i++)
        for(int j = 0; j < this->col; j++)
            for(int k = 0; k < rhs.col; k++)
                matrixTemp.data[i][k] += this->data[i][j] * rhs.data[j][k];
    return matrixTemp;
}
template <typename T>
/*
function name: matrix<T>::operator =
description: overload operator =
    change all elements of current object to those in rhs
arguments: matrix<T> &rhs: a referance of an object of class matrix
return value: an object which pointer this points at of class matrix
*/
matrix<T>& matrix<T>::operator = (const matrix<T> &rhs)
{
    this->row = rhs.row;
    this->col = rhs.col;
    this->data.resize(row, vector<T>(col));
    this->data = rhs.data;
    return *this;
}
template <typename T>
/*
function name: matrix<T>::operator +=
description: overload operator +=
    1. check if the dimension of two matrices matches
    2. change this->data[i][j] to this->data[i][j] + rhs.data[i][j]
arguments: matrix<T> &rhs: a referance of an object of class matrix
return value: None
*/
void matrix<T>::operator += (const matrix<T> &rhs)
{
    if(row != rhs.row || col != rhs.col)
        std::cerr << "the dimension is not the same" << '\n';

    for(int i = 0; i < this->row; i++)
        for(int j = 0; j < this->col; j++)
            this->data[i][j] = this->data[i][j] + rhs.data[i][j];
}
template <typename T>
/*
function name: matrix<T>::operator -=
description: overload operator -=
    1. check if the dimension of two matrices matches
    2. change this->data[i][j] to this->data[i][j] - rhs.data[i][j]
arguments: matrix<T> &rhs: a referance of an object of class matrix
return value: None
*/
void matrix<T>::operator -= (const matrix<T> &rhs)
{
    if(row != rhs.row || col != rhs.col)
        std::cerr << "the dimension is not the same" << '\n';

    for(int i = 0; i < this->row; i++)
        for(int j = 0; j < this->col; j++)
            this->data[i][j] = this->data[i][j] - rhs.data[i][j];
}
template <typename T>
/*
function name: matrix<T>::operator *=
description: overload operator *=
    1. check if the dimension of two matrices matches
    2. create a temporary object the same as the current one
    3. change the dimension of current object to the answer's demention and set
      all elements in data to 0
    4. do the multiple operation
arguments: matrix<T> &rhs: a referance of an object of class matrix
return value: None
*/
void matrix<T>::operator *= (const matrix<T> &rhs)
{
    if(this->data[0].size() != rhs.data.size())
        std::cerr << "matrix A can not be multiplied by matrix B" << '\n';

    matrix<T> matrixTemp(this);
    this->resize(this->row, rhs.col);
    for(int i = 0; i < matrixTemp.row; i++)
        for(int j = 0; j < matrixTemp.col; j++)
            for(int k = 0; k < rhs.col; k++)
                this->data[i][k] += matrixTemp.data[i][j] * rhs.data[j][k];
}
template <typename T>
/*
function name: matrix<T>::resize
description:
    1. change the dimension of current object
    2. set all elements in data to 0
arguments:
    inputRow: the wanted row of the matrix
    inputCol: the wanted column of the matrix
return value: None
*/
void matrix<T>::resize(int inputRow, int inputCol)
{
    row = inputRow; col = inputCol;
    data.resize(row, vector<T>(col));
    zero();
}
