#include "Dust.h"

void Dust::draw(Painter& painter) const {
    // TODO: место для доработки
    painter.draw(getCenter(), 8, {1, 0, 0});
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Dust::setCenter(const Point& center) {
    // TODO: место для доработки
    x_y.x = center.x;
    x_y.y = center.y;
}

/**
 * @return центр объекта
 */
Point Dust::getCenter() const {
    // TODO: место для доработки
    return x_y;
}

void Dust::incrementDust() {
    spentTimes++;
}

int Dust::getTotalTimes() const {
    return totalTimes;
}

int Dust::getSpentTimes() {
    return spentTimes;
}

