#pragma once
#include "Vect.hpp"

class Piece {
    public:
        enum Type {
            BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK
        };
        enum ID {
            BB, BK, BN, BP, BQ, BR,
            WB, WK, WN, WP, WQ, WR
        };
        enum Side {
            WHITE = 0, BLACK = 1
        };

        Piece(Side side, Vect location, Type type);
        Side getSide();
        Vect getLocation();
        ID determineID(Type type, Side side);

    private:
        Side m_side;
        Vect m_location;
        ID m_id;
};