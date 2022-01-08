#include <SFML/Graphics.hpp>
#include "Board.hpp"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = new Piece(Piece::WHITE, Vect(i, j), Piece::PAWN);
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
                    square.setFillColor(sf::Color::Black);
                } else {
                    square.setFillColor(sf::Color::White);
                }
                window.draw(square);
            }
        }
        window.display();
    }
}