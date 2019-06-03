#include "matrix.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    matrix<int> mat1(2, 3);
    matrix<int> mat2(2, 3);
    cin >> mat1 >> mat2;
    cout << mat1 << mat2;
    cout << mat1 << endl << mat2 << endl;
    cout << mat1 + mat2 << endl;
    cout << mat1 - mat2 << endl;
    return 0;
}
