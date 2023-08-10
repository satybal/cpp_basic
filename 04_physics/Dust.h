#pragma once
#include "Painter.h"
#include "Point.h"


class Dust {
public:
    Dust() = default;

    Dust(Point x_y, Point vx_vy) : x_y{x_y}, vx_vy{vx_vy} {};

    Point x_y, vx_vy;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;

    void incrementDust();
    int getTotalTimes() const;
    int getSpentTimes();

private:
    int totalTimes = 300;
    int spentTimes = 0;
};