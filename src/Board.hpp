#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Pawn.hpp"

class Board {
    public:
        Board();
        ~Board();

    private:
        std::map<Piece::ID, std::string> imageFiles;
        int board[8][8];
};