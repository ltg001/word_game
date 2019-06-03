#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

class Shape {
public:
    Shape() {std::cout << "class shape init" << std::endl;}
    ~Shape() {std::cout << "class shape destroyed" << std::endl;}
    virtual double getArea() = 0;
};

class Rectangle: public Shape {
private:
    int x, y;
public:
    Rectangle(int _x, int _y): Shape() {
        x = _x;
        y = _y;
        std::cout << "class rectangle init" << std::endl;
    }
    ~Rectangle() {std::cout << "class rectangle destroyed" << std::endl;}
    double getArea() {
        return x * y;
    }
};

class Circle: public Shape {
private:
    int r;
public:
    Circle(int _r) {
        r = _r;
        std::cout << "class circle init" << std::endl;
    }
    ~Circle() {std::cout << "class circle destroyed" << std::endl;}
    double getArea() {
        return M_PI * r * r;
    }
};

int main() {
    Circle* circle = new Circle(1);
    Rectangle *rec = new Rectangle(2, 3);
    std::cout << circle->getArea() << " " << rec->getArea() << std::endl;
    return 0;
}