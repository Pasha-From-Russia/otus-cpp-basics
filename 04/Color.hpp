#pragma once

typedef struct {
    double r, g, b;
} RGB;

class Color {
public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

private:
    double r{};
    double g{};
    double b{};
};
