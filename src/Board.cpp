#include "Board.hpp"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

    // pawns
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Piece(Piece::BLACK, Vect(i, 1), Piece::PAWN);
    }
    for (int i = 0; i < 8; i++) {
        board[i][6] = new Piece(Piece::WHITE, Vect(i, 6), Piece::PAWN);
    }
    // rooks
    board[0][0] = new Piece(Piece::BLACK, Vect(0, 0), Piece::ROOK);
    board[7][0] = new Piece(Piece::BLACK, Vect(7, 0), Piece::ROOK);
    board[0][7] = new Piece(Piece::WHITE, Vect(0, 7), Piece::ROOK);
    board[7][7] = new Piece(Piece::WHITE, Vect(7, 7), Piece::ROOK);
    // knights
    board[1][0] = new Piece(Piece::BLACK, Vect(1, 0), Piece::KNIGHT);
    board[6][0] = new Piece(Piece::BLACK, Vect(6, 0), Piece::KNIGHT);
    board[1][7] = new Piece(Piece::WHITE, Vect(1, 7), Piece::KNIGHT);
    board[6][7] = new Piece(Piece::WHITE, Vect(6, 7), Piece::KNIGHT);
    // bishops
    board[2][0] = new Piece(Piece::BLACK, Vect(2, 0), Piece::BISHOP);
    board[5][0] = new Piece(Piece::BLACK, Vect(5, 0), Piece::BISHOP);
    board[2][7] = new Piece(Piece::WHITE, Vect(2, 7), Piece::BISHOP);
    board[5][7] = new Piece(Piece::WHITE, Vect(5, 7), Piece::BISHOP);
    // kings
    board[3][0] = new Piece(Piece::BLACK, Vect(3, 0), Piece::KING);
    board[3][7] = new Piece(Piece::WHITE, Vect(3, 7), Piece::KING);
    // queens
    board[4][0] = new Piece(Piece::BLACK, Vect(4, 0), Piece::QUEEN);
    board[4][7] = new Piece(Piece::WHITE, Vect(4, 7), Piece::QUEEN);


    for (int i = 0; i < 12; i++) {
        sf::Texture texture;
        if (texture.loadFromFile(files[i])) {
            images[ids[i]] = texture;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]) {
                delete(board[i][j]);
            }
        }
    }
}

void Board::render() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                sf::RectangleShape square(sf::Vector2f(100, 100));
                square.setPosition(sf::Vector2f(i * 100, j * 100));
                if ((i + j) % 2 == 1) {
                    square.setFillColor(sf::Color(149, 110, 87, 255)); // timeless copper #956e57
                } else {
                    square.setFillColor(sf::Color::White);
                }
                window.draw(square);

                if (board[i][j]) {
                    Piece* piece= board[i][j];
                    sf::Sprite sprite(images[piece->getID()]);
                    sprite.setPosition(piece->getLocation().toRender().asVector2f());
                    window.draw(sprite);
                }
            }
        }
        window.display();
    }
}