#ifndef TBP_LITTLE_COORDINATES_H
#define TBP_LITTLE_COORDINATES_H

#include <cmath>

class Coordinates {
private:
    double x;
    double y;
public:
    Coordinates();

    Coordinates(double x, double y);

    virtual ~Coordinates();

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double computeDistanceWith(Coordinates other);
};


#endif //TBP_LITTLE_COORDINATES_H
