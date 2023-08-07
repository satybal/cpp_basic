#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
public:
    Ball(
        Point x_y, Point vx_vy, 
        double radius, 
        Color r_g_b,
        bool isCollidable
    ) : x_y{x_y}, vx_vy{vx_vy}, radius{radius}, r_g_b{r_g_b}, isCollidable{isCollidable} {};

    Point x_y, vx_vy;
    double radius;
    Color r_g_b;
    bool isCollidable;

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
};
