#pragma once
#include "Vect.hpp"

class Util {
    public:
        Vect pawnMoves[2] = {
            Vect(0, 1),
            Vect(0, 2)
        };

        Util(const Util&) = delete;

        static Util& Get() {
            static Util instance;
            return instance;
        }
    
    private:
        Util() {}
};