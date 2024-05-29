#include "World.hpp"
#include "Painter.hpp"
#include <fstream>
#include <iostream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

std::istream &operator>>(std::istream &is, RGB &data) {
    is >> data.r >> data.g >> data.b;
    return is;
}

std::istream &operator>>(std::istream &is, Point &data) {
    is >> data.x >> data.y;
    return is;
}

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);

    stream >> topLeft_ >> bottomRight_;
    physics_.setWorldBox(topLeft_, bottomRight_);

    Point center;
    Point velVector;
    double radius;
    RGB objColor;
    bool isCollidable;

    int line = 0;

    while (stream.peek(), stream.good()) {
        ++line;
        try {
            stream >> center >> velVector;
            stream >> objColor;
            stream >> radius;
            stream >> std::boolalpha >> isCollidable;
        } catch (...) {
            std::cerr << "Line " << line << " is incorrect";
            continue;
        }

        Ball ball(
            center,
            radius,
            Velocity(velVector),
            isCollidable,
            Color(objColor.r, objColor.g, objColor.b));
        balls_.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft_, bottomRight_, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls_) {
        ball.draw(painter);
    }

    for (const Dust& dust : dust_) {
        dust.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime_;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime_ = time - double(ticks) * timePerTick;

    physics_.update(balls_, dust_, ticks);
}