#include <string>
#include "Piece.hpp"

Piece::Piece(Side side, Vect location, Type type) {
    m_side = side;
    m_location = location;
    m_id = determineID(type, side);
    m_type = type;
    m_hasMoved = false;
}

Piece::Side Piece::getSide() const {
    return m_side;
}

const Vect& Piece::getLocation() const {
    return m_location;
}

Piece::ID Piece::getID() const {
    return m_id;
}

Piece::Type Piece::getType() const {
    return m_type;
}

void Piece::setType(Type type) {
    m_type = type;
    m_id = determineID(m_type, m_side);
}

void Piece::setLocation(Vect location) {
    m_location = location;
}

void Piece::setLocation(int x, int y) {
    m_location.x = x;
    m_location.y = y;
}

Piece::ID Piece::determineID(Type type, Side side) const {
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
        default:
            return (side == BLACK) ? BR : WR;
    }
}

bool Piece::hasMoved() const {
    return m_hasMoved;
}

void Piece::setHasMoved() {
    m_hasMoved = true; 
}

void Piece::print() const {
    std::string type;
    switch (m_type) {
        case PAWN:
            type = "Pawn";
            break;
        case BISHOP:
            type = "Bishop";
            break;
        case KNIGHT:
            type = "Knight";
            break;
        case ROOK:
            type = "Rook";
            break;
        case QUEEN:
            type = "Queen";
            break;
        case KING:
            type = "King";
            break;
    }
    std::cout << (m_side == BLACK ? "Black" : "White") << ' ' << type << std::endl;
    std::cout << "Position: " << m_location.asString() << std::endl;
    std::cout << std::endl;
}