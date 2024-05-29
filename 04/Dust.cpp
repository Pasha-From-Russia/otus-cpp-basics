#include "Dust.hpp"
#include <iostream>

static constexpr double particleRadius   = 4.0;
static constexpr double particleVelocity = 400.0;
static constexpr int    particleTTL      = 200;

Dust::Dust(const Point& center) {
    timeToLive_ = particleTTL;
    for (double angle = 0.0; angle < 360.0; angle += 30.0) {
        double radian = angle * M_PI / 180.0;
        Point p {cos(radian) * particleVelocity, sin(radian) * particleVelocity};
        Ball particle(
			center,
			particleRadius,
			Velocity(p),
			false,
			Color(1, 0, 0));
        particles_.push_back(particle);
    }
}

void Dust::draw(Painter &painter) const {
    for (const Ball& particle : particles_) {
        particle.draw(painter);
    }
}

std::vector<Ball>& Dust::getDust() {
	return particles_;
}

void Dust::dropTTL() {
	--timeToLive_;
}

int Dust::getTTL() const {
	return timeToLive_;
}
