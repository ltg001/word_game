#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

class Shape {
public:
    Shape() {std::cout << "class shape init" << std::endl;}
    ~Shape() {std::cout << "class shape destroyed" << std::endl;}
    double getArea() {
        return 0;
    }
};

class Circle : public Shape {
    int r;
public:
    Circle():Shape() {std::cout << "class circle init" << std::endl;}
    Circle(int _r):Shape() {r = _r;std::cout << "class circle init" << std::endl;}
    ~Circle() {std::cout << "class circle destroyed" << std::endl;}
    double getArea() {
        return M_PI * r * r;
    }
};

class Rectangle: public Shape {
    int length, height;
public:
    Rectangle():Shape() {std::cout << "class rectangle init" << std::endl;}
    Rectangle(int _length, int _height):Shape() {
        length = _length;
        height = _height;
        std::cout << "class rectangle init" << std::endl;
    }
    ~Rectangle() {std::cout << "class rectangle destroyed" << std::endl;}
    double getArea() {
        return height * length;
    }
};

class Square :public Rectangle{
public:
    Square():Rectangle() {std::cout << "class square init" << std::endl;}
    Square(int _length): Rectangle(_length, _length) {
        std::cout << "class square init" << std::endl;
    }
    ~Square() {std::cout << "class square destroyed" << std::endl;}
};

int main(int argc, char *argv[])
{
    Circle circle(1);
    Rectangle rec(1, 2);
    Square square(4);
    std::cout << circle.getArea() << " " << rec.getArea() << " " << square.getArea() << std::endl;
    return 0;
}

