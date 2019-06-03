#include <cstdio>
#include <iostream>

class Point
{
    int x, y;
public:
    Point() {}
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
    ~Point() {}

    Point operator++ () {
        this -> x ++;
        this -> y ++;
        return *this;
    }

    Point operator ++(int) {
        Point point(*this);
        this -> x ++;
        this -> y ++;
        // this -> z ++;
        return point;
    }

    Point operator -- () {
        this -> x --;
        this -> y --;
        return *this;
    }

    Point operator -- (int) {
        Point point(*this);
        //std::cout << "__4__" << std::endl;
        this -> x --;
        this -> y --;
        return point;
    }

    friend std::ostream& operator << (std::ostream& os, const Point point) {
        os << point.x << " " << point.y << std::endl;
        return os;
    }
};


int main(int argc, char *argv[])
{
    Point point(1 , 2);
    int x = 1;
    std::cout << point;
    std::cout << point++;
    std::cout << point--;
    return 0;
}
