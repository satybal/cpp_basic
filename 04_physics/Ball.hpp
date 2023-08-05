#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
public:
    Ball(
        Point x_y, Point vx_vy, 
        double radius, 
        double red, double green, double blue,
        bool isCollidable
    ) : x_y{x_y}, vx_vy{vx_vy}, radius{radius}, red{red}, green{green}, blue{blue}, isCollidable{isCollidable} {};

    Point x_y, vx_vy;
    double radius;
    double red, green, blue;
    bool isCollidable;

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
};
