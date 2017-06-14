#include "Coordinates.h"

Coordinates::Coordinates() {}

Coordinates::Coordinates(float x, float y) : x(x), y(y) {}

Coordinates::~Coordinates() {}

float Coordinates::getX() const {
    return x;
}

void Coordinates::setX(float x) {
    Coordinates::x = x;
}

float Coordinates::getY() const {
    return y;
}

void Coordinates::setY(float y) {
    Coordinates::y = y;
}
