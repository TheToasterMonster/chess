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

int Vect::getX() {
    return x;
}

int Vect::getY() {
    return y;
}

Vect Vect::operator+(Vect shift) {
    return Vect(x + shift.x, y + shift.y);
}

Vect Vect::operator-(Vect shift) {
    return Vect(x - shift.x, y - shift.y);
}

Vect Vect::operator*(int scale) {
    return Vect(x * scale, y * scale);
}

Vect Vect::operator/(int scale) {
    return Vect(x / scale, y / scale);
}

void Vect::operator+=(Vect shift) {
    x += shift.x;
    y += shift.y;
}

std::string Vect::asString() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

sf::Vector2f Vect::asVector2f() {
    return sf::Vector2f(x, y);
}

void Vect::print() {
    std::cout << '(' << x << ',' << ' ' << y << ')' << std::endl;
}

Vect Vect::toRender() {
    return *this * 100;
}

Vect Vect::toBoard() {
    return *this / 100;
}

bool Vect::isValidPosition() {
    return x < 8 && x >= 0 && y < 8 && y >= 0;
}