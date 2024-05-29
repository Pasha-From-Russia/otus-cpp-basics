#pragma once
#include "Point.hpp"
#include "Ball.hpp"
#include <vector>

class Dust {
public:
    Dust(const Point &point);
    void draw(Painter &painter) const;
    std::vector<Ball>& getDust();
    void dropTTL();
    int getTTL() const;
private:
    int timeToLive_;
    std::vector<Ball> particles_;
};