#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Vect {
    public:
        int x, y;

        Vect();
        Vect(int x, int y);

        int getX();
        int getY();

        Vect operator+(Vect shift);
        Vect operator-(Vect shift);
        Vect operator*(int scale);
        Vect operator/(int scale);
        void operator+=(Vect shift);

        std::string asString();
        sf::Vector2f asVector2f();
        void print();

        // converts from board to rendering coordinates
        Vect toRender();
        // converts from rendering to board coordinates
        Vect toBoard();
};