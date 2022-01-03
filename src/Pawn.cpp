#include "Pawn.hpp"

Pawn::Pawn(Side side, Vect location) : Piece(side, location, PAWN) {}

void Pawn::print() {
    std::cout << (this->getSide() == BLACK ? "Black" : "White") << ' ' << "Pawn" << std::endl;
    std::cout << "Position: " << this->getLocation().asString() << std::endl;
}