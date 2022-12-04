#include "board.h"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        auto pawn1 = std::make_shared<Pawn>('p');
        bd[1][i] = pawn1;
        auto pawn2 = std::make_shared<Pawn>('P');
        bd[6][i] = pawn2;
    }
    auto rook_b1 = std::make_shared<Rook>('r');
    auto rook_b2 = std::make_shared<Rook>('r');
    auto rook_w1 = std::make_shared<Rook>('R');
    auto rook_w2 = std::make_shared<Rook>('R');
    bd[0][0] = rook_b1;
    bd[0][7] = rook_b2;
    bd[7][0] = rook_w1;
    bd[7][7] = rook_w2;
    
    auto knight_b1 = std::make_shared<Knight>('n');
    auto knight_b2 = std::make_shared<Knight>('n');
    auto knight_w1 = std::make_shared<Knight>('N');
    auto knight_w2 = std::make_shared<Knight>('N');
    bd[0][1] = knight_b1;
    bd[0][6] = knight_b2;
    bd[7][1] = knight_w1;
    bd[7][6] = knight_w2;

    auto bishop_b1 = std::make_shared<Bishop>('b');
    auto bishop_b2 = std::make_shared<Bishop>('b');
    auto bishop_w1 = std::make_shared<Bishop>('B');
    auto bishop_w2 = std::make_shared<Bishop>('B');
    bd[0][2] = bishop_b1;
    bd[0][5] = bishop_b2;
    bd[7][2] = bishop_w1;
    bd[7][5] = bishop_w2;

    auto king_b = std::make_shared<King>('k');
    auto queen_b = std::make_shared<Queen>('q');
    bd[0][4] = king_b;
    bd[0][3] = queen_b;

    auto king_w = std::make_shared<King>('K');
    auto queen_w = std::make_shared<Queen>('Q');
    bd[7][3] = queen_w;
    bd[7][4] = king_w;

    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                auto white = std::make_shared<Empty>(' ');
                bd[i][j] = white;
            } else {
                auto black = std::make_shared<Empty>('-');
                bd[i][j] = black;
            }
        }
    }
}

Board::~Board() {}

std::shared_ptr<Piece> Board::getPiece(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col];
}

void Board::setPiece(Position posn, std::shared_ptr<Piece> piece) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col] = piece;
}

void Board::remove(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    char piece;
    if ((col + row) % 2 == 0) {
        piece = ' ';
    } else {piece = '-';}
    auto empty = std::make_shared<Empty>(piece);
    bd[row][col] = empty;
}

void Board::replace(char c, Position posn) {
    std::shared_ptr<Piece> newPiece;
    if (c == 'p') {
        newPiece = std::make_shared<Pawn>(c);
    } else if (c == 'P') {
        newPiece = std::make_shared<Pawn>(c);
    } else if (c == 'r') {
        newPiece = std::make_shared<Rook>(c);
    } else if (c == 'R') {
        newPiece = std::make_shared<Rook>(c);
    } else if (c == 'b') {
        newPiece = std::make_shared<Bishop>(c);
    } else if (c == 'B') {
        newPiece = std::make_shared<Bishop>(c);
    } else if (c == 'n') {
        newPiece = std::make_shared<Knight>(c);
    } else if (c == 'N') {
        newPiece = std::make_shared<Knight>(c);
    } else if (c == 'k') {
        newPiece = std::make_shared<King>(c);
    } else if (c == 'K') {
        newPiece = std::make_shared<King>(c);
    } else if (c == 'q') {
        newPiece = std::make_shared<Queen>(c);
    } else if (c == 'Q') {
        newPiece = std::make_shared<Queen>(c);
    } else {throw std::out_of_range {"Invalid Piece!"};}
    remove(posn);
    setPiece(posn, newPiece);
}

char Board::charAt(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    char piece = bd[row][col]->getPiece();
    return piece;
}

bool Board::getFirstMove(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col]->getFirstMove();
}

void Board::setFirstMove(Position posn, bool value) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col]->setFirstMove(value);
}


void Board::enPassant(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    bd[new_row][new_col] = bd[org_row][org_col];
    remove(org_posn);
    remove(Position(10*org_row + new_col));
}

void Board::castling(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    bd[org_row][new_col] = bd[org_row][org_col];
    remove(org_posn);
    if (new_posn + 2 == org_posn) {
        bd[org_row][new_col + 1] = bd[org_row][new_col - 2];
        remove(Position(new_posn - 2));
    } else {
        bd[org_row][new_col - 1] = bd[org_row][new_col + 1];
        remove(Position(new_posn + 1));
    }
}

void Board::setEnPassant(Position posn, bool value) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col]->setEnPassant(value);
}
bool Board::getEnPassant(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col]->getEnPassant();
}


void Board::move(std::shared_ptr<Move> movement, char piece) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    bd[new_row][new_col] = bd[org_row][org_col];
    remove(org_posn);
    if (piece != '.') {
        replace(piece, new_posn);
    }
}

bool Board::getPromoted(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col]->getPromoted();
}
void Board::setPromoted(Position posn, bool value) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col]->setPromoted(value);
}

void Board::setWhenPromoted(Position posn, int value) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col]->setWhenPromoted(value);
}
int Board::getWhenPromoted(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col]->getWhenPromoted();
}


void Board::setWhenFirstMove(Position posn, int value) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col]->setWhenFirstMove(value);
}
int Board::getWhenFirstMove(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col]->getWhenFirstMove();
}


void Board::undo(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    auto newMove = std::make_shared<Move>(new_posn, org_posn);
    move(newMove);
    auto captured = movement->getCaptured();
    if (captured != nullptr) {
        bd[new_row][new_col] = captured;
    }
}

void Board::undoPromoted(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    bd[org_row][org_col] = movement->getPromoted();
    auto captured = movement->getCaptured();
    if (captured == nullptr) {
        remove(new_posn);
    } else {
        bd[new_row][new_col] = captured;
    }
}

void Board::undoEnPassant(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    bd[org_row][org_col] = bd[new_row][new_col];
    remove(new_posn);
    bd[org_row][new_col] = movement->getCaptured();
}

void Board::undoCastling(std::shared_ptr<Move> movement) {
    Position org_posn = movement->getOrg();
    Position new_posn = movement->getNew();
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    bd[org_row][org_col] = bd[new_row][new_col];
    if (new_posn  + 2 == org_posn) {
        bd[org_row][new_col - 1]= bd[org_row][new_col + 1];
        remove(Position(new_posn + 1));
    } else {
        bd[org_row][new_col + 1]= bd[org_row][new_col - 1];
        remove(Position(new_posn - 1));
    }
}