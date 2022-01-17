#include <string>
#include "Vect.hpp"

Vect::Vect() {
    x = -1;
    y = -1;
}

Vect::Vect(int x, int y) {
    this->x = x;
    this->y = y;
}

int Vect::getX() const {
    return x;
}

int Vect::getY() const {
    return y;
}

Vect Vect::operator+(const Vect& shift) const {
    return Vect(x + shift.x, y + shift.y);
}

Vect Vect::operator-(const Vect& shift) const {
    return Vect(x - shift.x, y - shift.y);
}

Vect Vect::operator*(int scale) const {
    return Vect(x * scale, y * scale);
}

Vect Vect::operator/(int scale) const {
    return Vect(x / scale, y / scale);
}

void Vect::operator+=(const Vect& shift) {
    x += shift.x;
    y += shift.y;
}

bool Vect::operator==(const Vect& other) {
    return x == other.x && y == other.y;
}

std::string Vect::asString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

sf::Vector2f Vect::asVector2f() const {
    return sf::Vector2f(x, y);
}

void Vect::print() const {
    std::cout << '(' << x << ',' << ' ' << y << ')' << std::endl;
}

Vect Vect::toRender() const {
    return *this * 100;
}

Vect Vect::toBoard() const {
    return *this / 100;
}