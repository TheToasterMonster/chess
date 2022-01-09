#include <string>
#include "Vect.hpp"

Vect::Vect() {
    m_x = -1;
    m_y = -1;
}

Vect::Vect(int x, int y) {
    m_x = x;
    m_y = y;
}

int Vect::getX() {
    return m_x;
}

int Vect::getY() {
    return m_y;
}

Vect Vect::operator+(Vect shift) {
    return Vect(m_x + shift.m_x, m_y + shift.m_y);
}

Vect Vect::operator*(int scale) {
    return Vect(m_x * scale, m_y * scale);
}

Vect Vect::operator/(int scale) {
    return Vect(m_x / scale, m_y / scale);
}

void Vect::operator+=(Vect shift) {
    m_x += shift.m_x;
    m_y += shift.m_y;
}

std::string Vect::asString() {
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}

sf::Vector2f Vect::asVector2f() {
    return sf::Vector2f(m_x, m_y);
}

void Vect::print() {
    std::cout << '(' << m_x << ',' << ' ' << m_y << ')' << std::endl;
}

Vect Vect::toRender() {
    return *this * 100;
}

Vect Vect::toBoard() {
    return *this / 100;
}
