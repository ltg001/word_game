#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

class Boat;
class Car;
double addWeights(Boat& boat, Car& car);

class Boat {
    double weight;
public:
    friend double addWeights(Boat &boat, Car &car);
    Boat(double _weight);
    Boat() {}
};

Boat::Boat(double _weight) {
    this -> weight = _weight;
}

class Car {
    double weight;
public:
    friend double addWeights(Boat &boat, Car &car);
    Car(double _weight);
    Car() {}
};

Car::Car(double _weight) {
    this -> weight = _weight;
}

double addWeights(Boat& boat, Car& car) {
    return boat.weight + car.weight;
}

int main(int argc, char *argv[])
{
    double x, y;
    cin >> x >> y;
    Boat boat(x);
    Car car(y);
    cout << addWeights(boat, car) << endl;
    return 0;
}
