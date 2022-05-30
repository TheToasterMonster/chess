#include "Board.hpp"
#include "BoardSize.hpp"

Board::Board() {
    window = nullptr;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

    // pawns
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Piece(Piece::Side::BLACK, Vect(i, 1), Piece::Type::PAWN);
    }
    for (int i = 0; i < 8; i++) {
        board[i][6] = new Piece(Piece::Side::WHITE, Vect(i, 6), Piece::Type::PAWN);
    }
    // rooks
    board[0][0] = new Piece(Piece::Side::BLACK, Vect(0, 0), Piece::Type::ROOK);
    board[7][0] = new Piece(Piece::Side::BLACK, Vect(7, 0), Piece::Type::ROOK);
    board[0][7] = new Piece(Piece::Side::WHITE, Vect(0, 7), Piece::Type::ROOK);
    board[7][7] = new Piece(Piece::Side::WHITE, Vect(7, 7), Piece::Type::ROOK);
    // knights
    board[1][0] = new Piece(Piece::Side::BLACK, Vect(1, 0), Piece::Type::KNIGHT);
    board[6][0] = new Piece(Piece::Side::BLACK, Vect(6, 0), Piece::Type::KNIGHT);
    board[1][7] = new Piece(Piece::Side::WHITE, Vect(1, 7), Piece::Type::KNIGHT);
    board[6][7] = new Piece(Piece::Side::WHITE, Vect(6, 7), Piece::Type::KNIGHT);
    // bishops
    board[2][0] = new Piece(Piece::Side::BLACK, Vect(2, 0), Piece::Type::BISHOP);
    board[5][0] = new Piece(Piece::Side::BLACK, Vect(5, 0), Piece::Type::BISHOP);
    board[2][7] = new Piece(Piece::Side::WHITE, Vect(2, 7), Piece::Type::BISHOP);
    board[5][7] = new Piece(Piece::Side::WHITE, Vect(5, 7), Piece::Type::BISHOP);
    // queens
    board[3][0] = new Piece(Piece::Side::BLACK, Vect(3, 0), Piece::Type::QUEEN);
    board[3][7] = new Piece(Piece::Side::WHITE, Vect(3, 7), Piece::Type::QUEEN);
    // kings
    board[4][0] = new Piece(Piece::Side::BLACK, Vect(4, 0), Piece::Type::KING);
    blackKing = board[4][0];
    board[4][7] = new Piece(Piece::Side::WHITE, Vect(4, 7), Piece::Type::KING);
    whiteKing = board[4][7];

    for (int i = 0; i < 12; i++) {
        sf::Texture texture;
        if (texture.loadFromFile(Board::files[i])) {
            images[Board::ids[i]] = texture;
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            highlights[i][j] = HighlightType::TRANSPARENT;
        }
    }

    whiteKingChecked = false;
    blackKingChecked = false;
    gameOver = false;
    turn = Piece::Side::WHITE;
}

Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]) {
                delete board[i][j];
            }
        }
    }
}

bool Board::isValidMousePosition(const Vect& position) {
    return position.x < 8 && position.x >= 0 && position.y < 8 && position.y >= 0;
}

bool Board::isValidPiecePosition(const Vect& position, Piece::Side side) {
    if (!(position.x < 8 && position.x >= 0 && position.y < 8 && position.y >= 0)) {
        return false;
    }

    // a piece cannot take over the square of another piece of the same color
    if (board[position.x][position.y] && board[position.x][position.y]->getSide() == side) {
        return false;
    }

    return true;
}

void Board::updateHighlightOnMouseClick(const Vect& position) {
    if (gameOver) {
        return;
    }

    if (highlights[position.x][position.y] == HighlightType::TRANSPARENT || highlights[position.x][position.y] == HighlightType::RED) {
        // selected a new square, calculate moves for that square if theres a piece
        clearHighlights();

        if (turn == Piece::Side::WHITE && whiteKingChecked) {
            highlights[whiteKing->getLocation().x][whiteKing->getLocation().y] = HighlightType::RED;
        } else if (turn == Piece::Side::BLACK && blackKingChecked) {
            highlights[blackKing->getLocation().x][blackKing->getLocation().y] = HighlightType::RED;
        }

        highlights[position.x][position.y] = HighlightType::GREY;
        selectedSquare = position;
        highlighted.push_back(position);

        // check if there's a piece and make sure it's that side's turn
        if (board[position.x][position.y] && board[position.x][position.y]->getSide() == turn) {
            for (const Vect& move : calcMoves(board[position.x][position.y])) {
                highlights[move.x][move.y] = HighlightType::GREEN;
                highlighted.push_back(move);
            }
        }
    } else if (highlights[position.x][position.y] == HighlightType::GREEN) {
        // if square is green, this must be a move
        clearHighlights();
        move(selectedSquare, position);
    } else if (highlights[position.x][position.y] == HighlightType::GREY) {
        // unselect the square
        clearHighlights();

        if (turn == Piece::Side::WHITE && whiteKingChecked) {
            highlights[whiteKing->getLocation().x][whiteKing->getLocation().y] = HighlightType::RED;
        } else if (turn == Piece::Side::BLACK && blackKingChecked) {
            highlights[blackKing->getLocation().x][blackKing->getLocation().y] = HighlightType::RED;
        }
    }
}

void Board::clearHighlights() {
    while (!highlighted.empty()) {
        Vect back = highlighted.back();
        highlights[back.x][back.y] = HighlightType::TRANSPARENT;
        highlighted.pop_back();
    }
}

void Board::move(const Vect& start, const Vect& end) {
    if (turn == Piece::Side::WHITE) {
        highlights[whiteKing->getLocation().x][whiteKing->getLocation().y] = HighlightType::TRANSPARENT;
    } else {
        highlights[blackKing->getLocation().x][blackKing->getLocation().y] = HighlightType::TRANSPARENT;
    }

    // remove existing piece if there is one
    if (board[end.x][end.y]) {
        delete board[end.x][end.y];
        board[end.x][end.y] = nullptr;
    } else if (board[start.x][start.y]->getType() == Piece::Type::PAWN && abs(end.y - start.y) == 1 && abs(end.x - start.x) == 1) {
        // this must be an en passant
        Vect pieceLocation;
        if (end.y - start.y == 1) {
            // must be black
            pieceLocation = end - Vect(0, 1);
        } else {
            // must be white
            pieceLocation = end + Vect(0, 1);
        }
        
        // ensure there is indeed a piece here
        if (board[pieceLocation.x][pieceLocation.y]) {
            delete board[pieceLocation.x][pieceLocation.y];
            board[pieceLocation.x][pieceLocation.y] = nullptr;
        }
    }

    // check for a double pawn move
    if (board[start.x][start.y]->getType() == Piece::Type::PAWN && abs(end.y - start.y) == 2) {
        if (end.y - start.y == 2) {
            // must be black pawn
            enPassantSquare = start + Vect(0, 1);
        } else {
            // must be white pawn
            enPassantSquare = start - Vect(0, 1);
        }
    } else {
        enPassantSquare = Vect(-1, -1);
    }

    // check for castling
    if (board[start.x][start.y]->getType() == Piece::Type::KING && abs(end.x - start.x) == 2) {
        if (end.x - start.x == 2) {
            // kingside - white rook at (7, 7), black rook at (7, 0)
            Piece* rook = (turn == Piece::Side::WHITE) ? board[7][7] : board[7][0];
            board[end.x - 1][end.y] = rook;
            rook->setLocation(end - Vect(1, 0));
            rook->setHasMoved();
            board[7][end.y] = nullptr;
        } else {
            // queenside - white rook at (0, 7), black rook at (0, 0)
            Piece* rook = (turn == Piece::Side::WHITE) ? board[0][7] : board[0][0];
            board[end.x + 1][end.y] = rook;
            rook->setLocation(end + Vect(1, 0));
            rook->setHasMoved();
            board[0][end.y] = nullptr;
        }
    }

    board[end.x][end.y] = board[start.x][start.y];
    board[end.x][end.y]->setLocation(end);
    board[end.x][end.y]->setHasMoved();
    board[start.x][start.y] = nullptr;

    // promotion
    if (board[end.x][end.y]->getType() == Piece::Type::PAWN && (end.y == 0 || end.y == 7)) {
        // board[end.x][end.y]->setType(Piece::Type::QUEEN);
        promote(board[end.x][end.y]);
    }

    if (turn == Piece::Side::WHITE) {
        // if this move was legal, the king can't be in check
        if (whiteKingChecked) {
            whiteKingChecked = false;
        }
        turn = Piece::Side::BLACK;
    } else {
        if (blackKingChecked) {
            blackKingChecked = false;
        }
        turn = Piece::Side::WHITE;
    }

    // check for checks
    if (turn == Piece::Side::WHITE) {
        whiteKingChecked = isSquareInCheck(whiteKing->getLocation(), Piece::Side::WHITE);
        if (whiteKingChecked) {
            highlights[whiteKing->getLocation().x][whiteKing->getLocation().y] = HighlightType::RED;
        }
    } else {
        blackKingChecked = isSquareInCheck(blackKing->getLocation(), Piece::Side::BLACK);
        if (blackKingChecked) {
            highlights[blackKing->getLocation().x][blackKing->getLocation().y] = HighlightType::RED;
        }
    }

    GameState gameState = getGameState();
    if (gameState == GameState::CHECKMATE) {
        if (turn == Piece::Side::WHITE) {
            highlights[whiteKing->getLocation().x][whiteKing->getLocation().y] = HighlightType::ORANGE;
        } else {
            highlights[blackKing->getLocation().x][blackKing->getLocation().y] = HighlightType::ORANGE;
        }
        gameOver = true;
        return;
    } else if (gameState == GameState::STALEMATE) {
        if (turn == Piece::Side::WHITE) {
            highlights[whiteKing->getLocation().x][whiteKing->getLocation().y] = HighlightType::WHITE;
        } else {
            highlights[blackKing->getLocation().x][blackKing->getLocation().y] = HighlightType::WHITE;
        }
        gameOver = true;
        return;
    }
}

void Board::promote(Piece* piece) {
    Piece::ID arr[4];
    arr[0] = (turn == Piece::Side::WHITE) ? Piece::ID::WQ : Piece::ID::BQ;
    arr[1] = (turn == Piece::Side::WHITE) ? Piece::ID::WB : Piece::ID::BB;
    arr[2] = (turn == Piece::Side::WHITE) ? Piece::ID::WN : Piece::ID::BN;
    arr[3] = (turn == Piece::Side::WHITE) ? Piece::ID::WR : Piece::ID::BR;

    for (int i = 0; i < 4; i++) {
        sf::RectangleShape square(sf::Vector2f(Chess::squareSize, Chess::squareSize));
        square.setPosition(sf::Vector2f((i + 4) * Chess::squareSize, 0));
        if (i % 2 == 0) {
            square.setFillColor(sf::Color(149, 110, 87, 255));
        } else {
            square.setFillColor(sf::Color::White);
        }
        window->draw(square);

        sf::RectangleShape highlight(sf::Vector2f(Chess::squareSize, Chess::squareSize));
        highlight.setPosition(sf::Vector2f((i + 4) * Chess::squareSize, 0));
        highlight.setFillColor(sf::Color(255, 255, 0, 150));
        window->draw(highlight);

        sf::Sprite sprite(images[arr[i]]);
        sprite.setPosition(Vect((i + 4) * Chess::squareSize, 0).asVector2f());
        window->draw(sprite);
    }
    window->display();

    sf::Event event;
    while (window->waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mouseLocation = sf::Mouse::getPosition() - window->getPosition();
            #ifdef MAC
            mouseLocation.y -= 1800;
            #endif
            #ifdef WINDOWS
            mouseLocation.x -= 8;
            mouseLocation.y -= 30;
            #endif
            Vect location = Vect(mouseLocation.x, mouseLocation.y).toBoard();
            if (!isValidMousePosition(location) || location.y != 0 || location.x < 4) {
                continue;
            }

            switch (location.x - 4) {
                case 0: {
                    piece->setType(Piece::Type::QUEEN);
                    break;
                }
                case 1: {
                    piece->setType(Piece::Type::BISHOP);
                    break;
                }
                case 2: {
                    piece->setType(Piece::Type::KNIGHT);
                    break;
                }
                case 3: {
                    piece->setType(Piece::Type::ROOK);
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
    }
}

bool Board::isSquareInCheck(const Vect& square, Piece::Side side) {
    for (Vect move : Util::Get().pawnCaptures) {
        if (side == Piece::Side::BLACK) {
            move = Vect(0, 0) - move;
        }

        if (isValidPiecePosition(square - move, side) && board[square.x - move.x][square.y - move.y]) {
            Piece::Type enemyPiece = board[square.x - move.x][square.y - move.y]->getType();
            if (enemyPiece == Piece::Type::PAWN || enemyPiece == Piece::Type::BISHOP || enemyPiece == Piece::Type::QUEEN) {
                return true;
            }
        }
    }
    for (const Vect& move : Util::Get().knightMoves) {
        if (isValidPiecePosition(square - move, side) && board[square.x - move.x][square.y - move.y]) {
            if (board[square.x - move.x][square.y - move.y]->getType() == Piece::Type::KNIGHT) {
                return true;
            }
        }
    }
    for (const Vect& baseMove : Util::Get().rookMoves) {
        // check until a piece is hit
        for (int i = 1; i < 8; i++) {
            Vect move = baseMove * i;
            if (!isValidPiecePosition(square - move, side)) {
                break;
            }
            if (!board[square.x - move.x][square.y-move.y]) {
                continue;
            }

            Piece::Type enemyPiece = board[square.x - move.x][square.y - move.y]->getType();
            if (enemyPiece == Piece::Type::ROOK || enemyPiece == Piece::Type::QUEEN) {
                return true;
            }
            if (i == 1 && enemyPiece == Piece::Type::KING) {
                return true;
            }

            if (board[square.x - move.x][square.y - move.y]) {
                break;
            }
        }
    }
    for (const Vect& baseMove : Util::Get().bishopMoves) {
        // check until a piece is hit
        for (int i = 1; i < 8; i++) {
            Vect move = baseMove * i;
            if (!isValidPiecePosition(square - move, side)) {
                break;
            }
            if (!board[square.x - move.x][square.y - move.y]) {
                continue;
            }

            Piece::Type enemyPiece = board[square.x - move.x][square.y - move.y]->getType();
            if (enemyPiece == Piece::Type::BISHOP || enemyPiece == Piece::Type::QUEEN) {
                return true;
            }
            if (i == 1 && enemyPiece == Piece::Type::KING) {
                return true;
            }

            if (board[square.x - move.x][square.y - move.y]) {
                break;
            }
        }
    }
    return false;
}

bool Board::simulatePieceMove(Piece* piece, const Vect& shift) {
    Vect newPos = piece->getLocation() - shift;
    Piece* tmp = nullptr;
    if (board[newPos.x][newPos.y]) {
        tmp = board[newPos.x][newPos.y];
        board[newPos.x][newPos.y] = nullptr;
    }

    board[newPos.x][newPos.y] = piece;
    board[piece->getLocation().x][piece->getLocation().y] = nullptr;
    piece->setLocation(newPos);
    bool isInCheck = (piece->getSide() == Piece::Side::WHITE) ? isSquareInCheck(whiteKing->getLocation(), Piece::Side::WHITE) : isSquareInCheck(blackKing->getLocation(), Piece::Side::BLACK);

    board[newPos.x + shift.x][newPos.y + shift.y] = piece;
    piece->setLocation(newPos + shift);
    board[newPos.x][newPos.y] = tmp;
    return isInCheck;
}

std::vector<Vect> Board::calcMoves(Piece* piece) {
    std::vector<Vect> possibleMoves;
    std::vector<Vect> moves;

    switch (piece->getType()) {
        case Piece::Type::PAWN: {
            Vect move;
            std::vector<Vect> captures;

            // if square is black, move vectors have to be inverted
            if (piece->getSide() == Piece::Side::BLACK) {
                move = Vect(0, 0) - Util::Get().pawnMove;
                for (const Vect& capture : Util::Get().pawnCaptures) {
                    captures.push_back(Vect(0, 0) - capture);
                } 
            } else {
                move = Util::Get().pawnMove;
                captures = Util::Get().pawnCaptures;
            }

            // basic move
            if (!board[piece->getLocation().x - move.x][piece->getLocation().y - move.y]) {
                moves.push_back(move);
                // double move on first move
                if (!piece->hasMoved() && !board[piece->getLocation().x - move.x * 2][piece->getLocation().y - move.y * 2]) {
                    moves.push_back(move * 2);
                }
            }
            // diagonal capture moves
            for (const Vect& capture : captures) {
                if (isValidPiecePosition(piece->getLocation() - capture, piece->getSide())) {
                    Piece* square = board[piece->getLocation().x - capture.x][piece->getLocation().y - capture.y];
                    if (square && square->getSide() != piece->getSide()) {
                        moves.push_back(capture);
                    }
                    // check for en passant
                    if (piece->getLocation() - capture == enPassantSquare) {
                        moves.push_back(capture);
                    }
                }
            }
            break;
        }
        case Piece::Type::KNIGHT: {
            moves = Util::Get().knightMoves;
            break;
        }
        case Piece::Type::KING: {
            moves = Util::Get().kingMoves;
            // check for castling
            if (turn == Piece::Side::WHITE) {
                if (!whiteKing->hasMoved()) {
                    if (!whiteKingChecked && !board[5][7] && !board[6][7] && board[7][7] && board[7][7]->getID() == Piece::ID::WR && !board[7][7]->hasMoved() && !isSquareInCheck(Vect(5, 7), Piece::Side::WHITE)) {
                        moves.push_back(Vect(-2, 0));
                    }
                    if (!whiteKingChecked && !board[3][7] && !board[2][7] && !board[1][7] && board[0][7] && board[0][7]->getID() == Piece::ID::WR && !board[0][7]->hasMoved() && !isSquareInCheck(Vect(3, 7), Piece::Side::WHITE)) {
                        moves.push_back(Vect(2, 0));
                    }
                }
            } else {
                if (!blackKing->hasMoved()) {
                    if (!blackKingChecked && !board[5][0] && !board[6][0] && board[7][0] && board[7][0]->getID() == Piece::ID::BR && !board[7][0]->hasMoved() && !isSquareInCheck(Vect(5, 0), Piece::Side::BLACK)) {
                        moves.push_back(Vect(-2, 0));
                    }
                    if (!blackKingChecked && !board[3][0] && !board[2][0] && !board[1][0] && board[0][0] && board[0][0]->getID() == Piece::ID::BR && !board[0][0]->hasMoved() && !isSquareInCheck(Vect(3, 0), Piece::Side::BLACK)) {
                        moves.push_back(Vect(2, 0));
                    }
                }
            }
            break;
        }
        case Piece::Type::BISHOP: {
            for (const Vect& baseMove : Util::Get().bishopMoves) {
                // check until a piece is hit
                for (int i = 1; i < 8; i++) {
                    Vect move = baseMove * i;
                    if (!isValidPiecePosition(piece->getLocation() - move, piece->getSide())) {
                        break;
                    }
                    moves.push_back(move);
                    if (board[piece->getLocation().x - move.x][piece->getLocation().y - move.y]) {
                        break;
                    }
                }
            }
            break;
        }
        case Piece::Type::ROOK: {
            for (const Vect& baseMove : Util::Get().rookMoves) {
                // check until a piece is hit
                for (int i = 1; i < 8; i++) {
                    Vect move = baseMove * i;
                    if (!isValidPiecePosition(piece->getLocation() - move, piece->getSide())) {
                        break;
                    }
                    moves.push_back(move);
                    if (board[piece->getLocation().x - move.x][piece->getLocation().y - move.y]) {
                        break;
                    }
                }
            }
            break;
        }
        case Piece::Type::QUEEN: {
            for (const Vect& baseMove : Util::Get().queenMoves) {
                // check until a piece is hit
                for (int i = 1; i < 8; i++) {
                    Vect move = baseMove * i;
                    if (!isValidPiecePosition(piece->getLocation() - move, piece->getSide())) {
                        break;
                    }
                    moves.push_back(move);
                    if (board[piece->getLocation().x - move.x][piece->getLocation().y - move.y]) {
                        break;
                    }
                }
            }
            break;
        }
    }

    for (const Vect& move : moves) {
        Vect newPosition = piece->getLocation() - move;
        if (isValidPiecePosition(newPosition, piece->getSide())) {
            if (simulatePieceMove(piece, move)) {
                continue;
            }
            possibleMoves.push_back(newPosition);
        }
    }
    return possibleMoves;
}

Board::GameState Board::getGameState() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] && board[i][j]->getSide() == turn) {
                if (calcMoves(board[i][j]).size() > 0) {
                    return GameState::ONGOING;
                }
            }
        }
    }

    if (turn == Piece::Side::WHITE) {
        return (whiteKingChecked) ? GameState::CHECKMATE : GameState::STALEMATE;
    } else {
        return (blackKingChecked) ? GameState::CHECKMATE : GameState::STALEMATE;
    }
}

void Board::run() {
    window = new sf::RenderWindow(sf::VideoMode(800, 800), "Chess");
    render();
    while (window->isOpen()) {
        sf::Event event;
        if (window->waitEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button != sf::Mouse::Left) {
                    continue;
                }

                sf::Vector2i mouseLocation = sf::Mouse::getPosition() - window->getPosition();
                // weird cursor stuff
                #ifdef MAC
                mouseLocation.y -= 1800;
                #endif
                #ifdef WINDOWS
                mouseLocation.x -= 8;
                mouseLocation.y -= 30;
                #endif
                Vect location = Vect(mouseLocation.x, mouseLocation.y).toBoard();
                if (!isValidMousePosition(location)) {
                    continue;
                }
                updateHighlightOnMouseClick(location);
            }
        }

        render();
    }
    delete window;
}

void Board::render() {
    window->clear();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape square(sf::Vector2f(Chess::squareSize, Chess::squareSize));
            square.setPosition(sf::Vector2f(i * Chess::squareSize, j * Chess::squareSize));
            if ((i + j) % 2 == 1) {
                square.setFillColor(sf::Color(149, 110, 87, 255)); // timeless copper #956e57
            } else {
                square.setFillColor(sf::Color::White);
            }
            window->draw(square);

            if (board[i][j]) {
                Piece* piece = board[i][j];
                sf::Sprite sprite(images[piece->getID()]);
                sprite.setPosition(piece->getLocation().toRender().asVector2f());
                window->draw(sprite);
            }

            if (highlights[i][j] != HighlightType::TRANSPARENT) {
                sf::RectangleShape highlight(sf::Vector2f(Chess::squareSize, Chess::squareSize));
                highlight.setPosition(sf::Vector2f(i * Chess::squareSize, j * Chess::squareSize));
                if (highlights[i][j] == HighlightType::GREY) {
                    highlight.setFillColor(sf::Color(50, 50, 50, 150));
                } else if (highlights[i][j] == HighlightType::GREEN) {
                    highlight.setFillColor(sf::Color(50, 205, 50, 150));
                } else if (highlights[i][j] == HighlightType::ORANGE) {
                    highlight.setFillColor(sf::Color(255, 165, 0, 150));
                } else if (highlights[i][j] == HighlightType::RED) {
                    highlight.setFillColor(sf::Color(255, 0, 0, 150));
                } else if (highlights[i][j] == HighlightType::WHITE) {
                    highlight.setFillColor(sf::Color(255, 250, 250, 150));
                }
                window->draw(highlight);
            }
        }
    }
    window->display();
}