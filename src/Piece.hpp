#pragma once
#include "Vect.hpp"

class Piece {
    public:
        enum Type : uint8_t {
            BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK
        };
        enum ID : uint8_t {
            BB, BK, BN, BP, BQ, BR,
            WB, WK, WN, WP, WQ, WR
        };
        enum Side : uint8_t {
            WHITE = 0, BLACK = 1
        };

        Piece(Side side, Vect location, Type type);

        Side getSide();
        Vect getLocation();
        ID getID();
        Type getType();
        void setType(Type type);
        void setLocation(Vect location);
        void setLocation(int x, int y);
        ID determineID(Type type, Side side);

        bool hasMoved();
        void setHasMoved();
        
        void print();

    private:
        Side m_side;
        Vect m_location;
        ID m_id;
        Type m_type;
        bool m_hasMoved;
};
