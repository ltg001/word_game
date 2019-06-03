#include "matrix.h"
#include "matrix.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Matrix<int> mat1(3, 4);
    Matrix<int> mat2(3, 4);
    cin >> mat1;
    cin >> mat2;
    cout << "load" << endl;
    cout << mat1 << mat2 << endl;
    cout << mat1 + mat2 << endl;
    cout << mat1 - mat2 << endl;
    cout << mat1 * 2 << endl;
    return 0;
}
