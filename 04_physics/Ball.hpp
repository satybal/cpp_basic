#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
public:
    //Ball() = default;
    Ball(
        double x, double y, double vx, double vy, double radius,
        double red, double green, double blue, bool isCollidable
    ) : x{x}, y{y}, vx{vx}, vy{vy}, radius{radius}, red{red}, green{green}, blue{blue}, isCollidable{isCollidable} {};

    double x, y, vx, vy, radius, red, green, blue;
    bool isCollidable;

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
};
