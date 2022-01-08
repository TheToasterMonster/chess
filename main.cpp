#include "src/Board.hpp"

int main() {
    Vect final = Vect(1, 1) + Vect(2, 2);
    final.print();
    final += Vect(3, 3);
    final.print();
    Piece* wp1 = new Pawn(Piece::WHITE, final);
    // Pawn* wp = dynamic_cast<Pawn*>(wp1);
    //send help idk how to do this
    //wp1.print();
    delete(wp1);
}
