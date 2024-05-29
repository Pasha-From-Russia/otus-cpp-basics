#include "Ball.hpp"
#include <cmath>

Ball::Ball(
        const Point& center,
        double radius,
        const Velocity& velocity,
        bool collidable,
        const Color& color) {
    center_ = center;
    // 4/3 * Pi * r ^ 3
    mass_ = 4.0 / 3.0 * M_PI * std::pow(radius, 3.0);
    radius_ = radius;
    isCollidable_ = collidable;
    color_ = color;
    velocity_ = velocity;
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    velocity_.setVector(velocity.vector());
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return velocity_;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter &painter) const {
    painter.draw(center_, radius_, color_);
    /*
    // debug
    if (isCollidable_) {
        RGB color {1, 0, 0};
        painter.draw(center_, 10.0, color);
    }*/
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    center_ = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return center_;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return radius_;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return mass_;
}

bool Ball::isCollidable() const {
    return isCollidable_;
}
