#ifndef TBP_LITTLE_COORDINATES_H
#define TBP_LITTLE_COORDINATES_H


class Coordinates {
private:
    float x;
    float y;
public:
    Coordinates();

    Coordinates(float x, float y);

    virtual ~Coordinates();

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);
};


#endif //TBP_LITTLE_COORDINATES_H
