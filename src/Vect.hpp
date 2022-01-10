#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Vect {
    public:
        int x, y;

        // default constructor
        Vect();
        // constructor
        Vect(int x, int y);

        // getter method for x-coordinate
        int getX();
        // getter method for y-coordinate
        int getY();

        // overload on + operator for vectors
        Vect operator+(Vect shift);
        // overload on + operator for vectors
        Vect operator-(Vect shift);
        // overload on * operator for vectors
        Vect operator*(int scale);
        // overload on / operator for vectors
        Vect operator/(int scale);
        // overload on += operator for vectors
        void operator+=(Vect shift);

        // returns vector as a string
        std::string asString();
        // returns vector as a Vector2f
        sf::Vector2f asVector2f();
        // prints vector
        void print();

        // converts from board to rendering coordinates
        Vect toRender();
        // converts from rendering to board coordinates
        Vect toBoard();

        // check if position is within bounds of board
        bool isValidPosition();
};