#include "src/Board.hpp"

int main() {
    Vect final = Vect(1, 1) + Vect(2, 2);
    final.print();
    final += Vect(3, 3);
    final.print();
    Pawn* wp1 = (Pawn *)(new Piece(Piece::WHITE, final, Piece::PAWN));
    wp1->print();
    Board game;
    game.render();

    delete(wp1);
}
