#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Vect {
    public:
        int x, y;

        Vect();
        Vect(int x, int y);

        int getX() const;
        int getY() const;

        Vect operator+(const Vect& shift) const;
        Vect operator-(const Vect& shift) const;
        Vect operator*(int scale) const;
        Vect operator/(int scale) const;
        void operator+=(const Vect& shift);
        bool operator==(const Vect& other) const;

        std::string asString() const;
        sf::Vector2f asVector2f() const;
        void print() const;

        // converts from board to rendering coordinates
        Vect toRender() const;
        // converts from rendering to board coordinates
        Vect toBoard() const;
};