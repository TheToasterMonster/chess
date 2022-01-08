#pragma once
#include <string>
#include <map>
#include "Pawn.hpp"

class Board {
    public:
        Piece* board[8][8];

        Board();
        ~Board();
        void render();

    private:
        std::map<Piece::ID, std::string> imageFiles;
};