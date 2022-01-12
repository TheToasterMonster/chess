#pragma once
#include <string>
#include <map>
#include "Piece.hpp"
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
            GREEN,
            ORANGE,
            RED,
            WHITE
        };

        enum GameState {
            ONGOING = 0,
            CHECKMATE,
            STALEMATE
        };

        sf::RenderWindow* window;
        std::map<Piece::ID, sf::Texture> images;
        Piece* board[8][8];

        Piece::Side turn;

        HighlightType highlights[8][8];
        std::vector<Vect> highlighted;
        Vect selectedSquare;
        Vect enPassantSquare;

        Piece* whiteKing;
        Piece* blackKing;
        bool whiteKingChecked;
        bool blackKingChecked;
        bool gameOver;

        Board();
        ~Board();

        void run();
        void render();

        void updateHighlightOnMouseClick(Vect position);
        void clearHighlights();
        void move(Vect start, Vect end);

        std::vector<Vect> calcMoves(Piece* piece);
        bool isValidMousePosition(Vect position);
        bool isValidPiecePosition(Vect position, Piece::Side side);
        bool isSquareInCheck(Vect square, Piece::Side side);
        // returns true if the move is invalid
        bool simulatePieceMove(Piece* piece, Vect shift);

        GameState getGameState();
};