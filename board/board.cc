#include "board.h"
#include "pieces.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "empty.h"

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
    blackKing = Position(4);
    bd[0][3] = queen_b;

    auto king_w = std::make_shared<King>('K');
    auto queen_w = std::make_shared<Queen>('Q');
    bd[7][3] = queen_w;
    bd[7][4] = king_w;
    whiteKing = Position(74);

    for (int i = 2; i < 5; i++) {
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

bool Board::getIsChecked(Position posn) const {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col]->getIsChecked(); 
}

void Board::setIsChecked(Position posn, bool value) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col]->setIsChecked(value);
}


void Board::enPassant(Position org_posn, Position new_posn) {
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    bd[new_row][new_col] = bd[org_row][org_col];
    int blank = org_col + org_row;
    if (blank % 2 == 0) {
        auto empty = std::make_shared<Empty>(' ');
        bd[org_row][org_col] = empty;
    } else {
        auto empty = std::make_shared<Empty>('-');
        bd[org_row][org_col] = empty;
    }
    if ((org_row + new_col) % 2 == 0) {
        auto empty = std::make_shared<Empty>(' ');
        bd[org_row][new_col] = empty;
    } else {
        auto empty = std::make_shared<Empty>('-');
        bd[org_row][new_col] = empty;
    }
}

void Board::castling(Position org_posn, Position new_posn) {
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int org_blank = org_col + org_row;
    bd[org_row][new_col] = bd[org_row][org_col];
    if (org_blank % 2 == 0) {
        auto empty = std::make_shared<Empty>(' ');
        bd[org_row][org_col] = empty;
    } else {
        auto empty = std::make_shared<Empty>('-');
        bd[org_row][org_col] = empty;
    }
    if (new_posn > org_posn) {
        bd[org_row][new_col - 1] = bd[org_row][new_col + 1];
        int new_blank = org_row + new_col + 1;
        if (new_blank % 2 == 0) {
            auto empty = std::make_shared<Empty>(' ');
            bd[org_row][new_col + 1] = empty;
        } else {
            auto empty = std::make_shared<Empty>('-');
            bd[org_row][new_col + 1] = empty;
        }
    } else {
        bd[org_row][new_col + 1] = bd[org_row][new_col - 2];
        int new_blank = org_row + new_col - 2;
        if (new_blank % 2 == 0) {
            auto empty = std::make_shared<Empty>(' ');
            bd[org_row][new_col - 2] = empty;
        } else {
            auto empty = std::make_shared<Empty>('-');
            bd[org_row][new_col - 2] = empty;
        }
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
void Board::setCastling(Position posn, bool value) {
    int col = posn % 10;
    int row = posn / 10;
    bd[row][col]->setCastling(value);
}
bool Board::getCastling(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col]->getCastling();
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
        newPiece = std::make_shared<Pawn>(c, "Black");
    } else if (c == 'P') {
        newPiece = std::make_shared<Pawn>(c, "White");
    } else if (c == 'r') {
        newPiece = std::make_shared<Rook>(c, "Black");
    } else if (c == 'R') {
        newPiece = std::make_shared<Rook>(c, "White");
    } else if (c == 'b') {
        newPiece = std::make_shared<Bishop>(c, "Black");
    } else if (c == 'B') {
        newPiece = std::make_shared<Bishop>(c, "White");
    } else if (c == 'n') {
        newPiece = std::make_shared<Knight>(c, "Black");
    } else if (c == 'N') {
        newPiece = std::make_shared<Knight>(c, "White");
    } else if (c == 'k') {
        newPiece = std::make_shared<King>(c, "Black");
    } else if (c == 'K') {
        newPiece = std::make_shared<King>(c, "White");
    } else if (c == 'q') {
        newPiece = std::make_shared<Queen>(c, "Black");
    } else if (c == 'Q') {
        newPiece = std::make_shared<Queen>(c, "White");
    } else {throw std::out_of_range {"Invalid Piece!"};}
    remove(posn);
    setPiece(posn, newPiece);
}


void Board::move(Position org_posn, Position new_posn) {
    char movingPiece = charAt(org_posn);
    char captured = charAt(new_posn);
    if (movingPiece == 'p' || movingPiece == 'P') {
        if (org_posn - 11 == new_posn || new_posn == org_posn - 9 || org_posn + 9 == new_posn || new_posn == org_posn + 11) {
            if (captured == '-' || captured == ' '){
                enPassant(org_posn, new_posn);
                return;
            }
        }
    } else if (movingPiece == 'k' || movingPiece == 'K') {
        if (new_posn + 2 == org_posn || new_posn - 2 == org_posn) {
            castling(org_posn, new_posn);
            return;
        }
    }
    int org_col = org_posn % 10;
    int org_row = org_posn / 10;
    int new_col = new_posn % 10;
    int new_row = new_posn / 10;
    int blank = org_col + org_row;
    bd[new_row][new_col] = bd[org_row][org_col];
    if (blank % 2 == 0) {
        auto empty = std::make_shared<Empty>(' ');
        bd[org_row][org_col] = empty;
    } else {
        auto empty = std::make_shared<Empty>('-');
        bd[org_row][org_col] = empty;
    }
}

Board::Board(const std::shared_ptr<Board> other) {
    for(int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            auto piece = std::make_shared<Piece>(other->getPiece(Position(i*10 + j)));
            bd[i][j] = piece;
        }
    }
}

