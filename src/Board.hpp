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
            Piece::ID::BB,
            Piece::ID::BK,
            Piece::ID::BN,
            Piece::ID::BP,
            Piece::ID::BQ,
            Piece::ID::BR,
            Piece::ID::WB,
            Piece::ID::WK,
            Piece::ID::WN,
            Piece::ID::WP,
            Piece::ID::WQ,
            Piece::ID::WR
        };

        enum class HighlightType : uint8_t {
            TRANSPARENT = 0,
            GREY,
            GREEN,
            ORANGE,
            RED,
            WHITE
        };

        enum class GameState: uint8_t{
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

        void updateHighlightOnMouseClick(const Vect& position);
        void clearHighlights();
        void move(const Vect& start, const Vect& end);

        std::vector<Vect> calcMoves(Piece* piece);
        void promote(Piece* piece);
        bool isValidMousePosition(const Vect& position);
        bool isValidPiecePosition(const Vect& position, Piece::Side side);
        bool isSquareInCheck(const Vect& square, Piece::Side side);
        // returns true if the move is invalid
        bool simulatePieceMove(Piece* piece, const Vect& shift);

        GameState getGameState();
};