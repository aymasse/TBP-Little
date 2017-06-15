#include "Coordinates.h"

Coordinates::Coordinates() {}

Coordinates::Coordinates(double x, double y) : x(x), y(y) {}

Coordinates::~Coordinates() {}

double Coordinates::getX() const {
    return x;
}

void Coordinates::setX(double x) {
    Coordinates::x = x;
}

double Coordinates::getY() const {
    return y;
}

void Coordinates::setY(double y) {
    Coordinates::y = y;
}

double Coordinates::computeDistanceWith(Coordinates other) {
    return sqrt(pow(other.getX() - getX(), 2) + pow(other.getY() - getY(), 2));
}
