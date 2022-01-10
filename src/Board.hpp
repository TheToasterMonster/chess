#pragma once
#include <string>
#include <map>
#include "Pieces.hpp"
#include "Util.hpp"


class Board {
    public:
        std::string files[12] = {
            "images/bb.png",
            "images/bk.png",
            "images/bn.png",
            "images/bp.png",
            "images/bq.png",
            "images/br.png",
            "images/wb.png",
            "images/wk.png",
            "images/wn.png",
            "images/wp.png",
            "images/wq.png",
            "images/wr.png"
        };

        Piece::ID ids[12] = {
            Piece::BB,
            Piece::BK,
            Piece::BN,
            Piece::BP,
            Piece::BQ,
            Piece::BR,
            Piece::WB,
            Piece::WK,
            Piece::WN,
            Piece::WP,
            Piece::WQ,
            Piece::WR
        };

        enum HighlightType {
            TRANSPARENT = 0,
            GREY,
            GREEN
        };

        std::map<Piece::ID, sf::Texture> images;
        Piece* board[8][8];
        HighlightType highlights[8][8];
        std::vector<Vect> highlighted;
        sf::RenderWindow* window;

        Board();
        ~Board();
        void start();
        void render();
        void updateHighlightOnMouseClick(Vect position);
        std::vector<Vect> calcMoves(Piece* piece);
        bool isValidPosition(Vect position);
};