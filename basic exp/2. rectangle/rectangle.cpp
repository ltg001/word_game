#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

class point {
private:
    double x;
    double y;
public:
    friend class rectangle;
    point() {}
    point(double _x, double _y);
    ~point() {}
    double getDis(point rhs);
};

point::point(double _x, double _y) {
    x = _x;
    y = _y;
}

double point::getDis(point rhs) {
    return sqrt(x - rhs.x * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
}

class rectangle {
private:
    point topLeft;
    point bottomRight;
public:
    rectangle() {}
    rectangle(double topLeft_x, double topLeft_y, double bottomRight_x, double bottomRight_y);
    ~rectangle() {}
    double getArea();
};

rectangle::rectangle(double topLeft_x, double topLeft_y, double bottomRight_x, double bottomRight_y) {
    topLeft.x = topLeft_x;
    topLeft.y = topLeft_y;
    bottomRight.x = bottomRight_x;
    bottomRight.y = bottomRight_y;
}

double rectangle::getArea() {
    return abs(topLeft.y - bottomRight.y) * abs(topLeft.x - bottomRight.x);
}

int main(int argc, char *argv[])
{
    double x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    rectangle rect(x1, y1, x2, y2);
    cout << rect.getArea() << endl;
    return 0;
}
