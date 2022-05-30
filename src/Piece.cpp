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
        case Type::BISHOP:
            return (side == Side::BLACK) ? ID::BB : ID::WB;
            break;
        case Type::KING:
            return (side == Side::BLACK) ? ID::BK : ID::WK;
            break;
        case Type::KNIGHT:
            return (side == Side::BLACK) ? ID::BN : ID::WN;
            break;
        case Type::PAWN:
            return (side == Side::BLACK) ? ID::BP : ID::WP;
            break;
        case Type::QUEEN:
            return (side == Side::BLACK) ? ID::BQ : ID::WQ;
            break;
        default:
            return (side == Side::BLACK) ? ID::BR : ID::WR;
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
        case Type::PAWN:
            type = "Pawn";
            break;
        case Type::BISHOP:
            type = "Bishop";
            break;
        case Type::KNIGHT:
            type = "Knight";
            break;
        case Type::ROOK:
            type = "Rook";
            break;
        case Type::QUEEN:
            type = "Queen";
            break;
        case Type::KING:
            type = "King";
            break;
    }
    std::cout << (m_side == Side::BLACK ? "Black" : "White") << ' ' << type << std::endl;
    std::cout << "Position: " << m_location.asString() << std::endl;
    std::cout << std::endl;
}