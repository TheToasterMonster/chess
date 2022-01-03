#include "Pieces.hpp"

Piece::Piece(Side side, Vect location, Type type) {
    m_side = side;
    m_location = location;
    m_id = determineID(type, side);
}

Piece::Side Piece::getSide() {
    return m_side;
}

Vect Piece::getLocation() {
    return m_location;
}

Piece::ID Piece::determineID(Type type, Side side) {
    switch (type) {
        case BISHOP:
            return (side == BLACK) ? BB : WB;
            break;
        case KING:
            return (side == BLACK) ? BK : WK;
            break;
        case KNIGHT:
            return (side == BLACK) ? BN : WN;
            break;
        case PAWN:
            return (side == BLACK) ? BP : WP;
            break;
        case QUEEN:
            return (side == BLACK) ? BQ : WQ;
            break;
        case ROOK:
            return (side == BLACK) ? BR : WR;
            break;
    }
}
