#pragma once
#include <iostream>

class Vect {
    public:
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
        // overload on += operator for vectors
        void operator+=(Vect shift);

        // returns vector as a string
        std::string asString();
        // prints vector
        void print();

    private:
        int m_x, m_y;
};