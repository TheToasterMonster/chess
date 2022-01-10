#pragma once
#include "Vect.hpp"

class Util {
    public:
        Vect pawnMove = Vect(0, 1);
        std::vector<Vect> pawnCaptures = {
            Vect(-1, 1),
            Vect( 1, 1)
        };

        std::vector<Vect> knightMoves = {
            Vect(-1, -2),
            Vect(-1,  2),
            Vect( 1, -2),
            Vect( 1,  2),
            Vect(-2, -1),
            Vect(-2,  1),
            Vect( 2, -1),
            Vect( 2,  1)
        };


        std::vector<Vect> bishopMoves = {
            Vect(-1, -1),
            Vect(-1,  1),
            Vect( 1, -1),
            Vect( 1,  1),
        };

        std::vector<Vect> rookMoves = {
            Vect(-1,  0),
            Vect( 1,  0),
            Vect( 0, -1),
            Vect( 0,  1)
        };

        std::vector<Vect> kingMoves = {
            Vect(-1, -1),
            Vect(-1,  1),
            Vect( 1, -1),
            Vect( 1,  1),
            Vect(-1,  0),
            Vect( 1,  0),
            Vect( 0, -1),
            Vect( 0,  1)
        };

        std::vector<Vect> queenMoves = {
            Vect(-1, -1),
            Vect(-1,  1),
            Vect( 1, -1),
            Vect( 1,  1),
            Vect(-1,  0),
            Vect( 1,  0),
            Vect( 0, -1),
            Vect( 0,  1)
        };

        Util(const Util&) = delete;

        static Util& Get() {
            static Util instance;
            return instance;
        }
    
    private:
        Util() {}
};