#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
private:
    Color    color_;
    Velocity velocity_;
    Point    center_;
    double   mass_;
    double   radius_;
    bool     isCollidable_;
public:
    Ball(
        const Point& center,
        double radius,
        const Velocity& velocity,
        bool collidable,
        const Color& color);
    void draw(Painter &painter) const;

    Point    getCenter()    const;
    double   getRadius()    const;
    double   getMass()      const;
    Velocity getVelocity()  const;
    bool     isCollidable() const;

    void setCenter(const Point& center);
    void setVelocity(const Velocity& velocity);
};
