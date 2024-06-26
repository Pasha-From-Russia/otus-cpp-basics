#pragma once
#include "Ball.hpp"
#include "Physics.hpp"
#include "Dust.hpp"
#include <string>
#include <vector>

class Painter;

class World {
public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);

private:
    // Границы мира заданы углами прямоугольника
    Point topLeft_;
    Point bottomRight_;
    // Объект физического движка
    Physics physics_;
    // Контейнер с шарами
    std::vector<Ball> balls_;
    std::vector<Dust> dust_;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime_ = 0.;
};
