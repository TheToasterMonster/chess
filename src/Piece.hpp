#pragma once
#include "Vect.hpp"

class Piece {
    public:
        enum class Type : uint8_t {
            BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK
        };
        enum class ID : uint8_t {
            BB, BK, BN, BP, BQ, BR,
            WB, WK, WN, WP, WQ, WR
        };
        enum class Side : uint8_t {
            WHITE = 0, BLACK = 1
        };

        Piece(Side side, Vect location, Type type);

        Side getSide() const;
        const Vect& getLocation() const;
        ID getID() const;
        Type getType() const;
        void setType(Type type);
        void setLocation(Vect location);
        void setLocation(int x, int y);
        ID determineID(Type type, Side side) const;

        bool hasMoved() const;
        void setHasMoved();
        
        void print() const;

    private:
        Side m_side;
        Vect m_location;
        ID m_id;
        Type m_type;
        bool m_hasMoved;
};
