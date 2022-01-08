#pragma once
#include "Pieces.hpp"

class Pawn : public Piece {
    public:
        Pawn(Side side, Vect location);
        void print();
};