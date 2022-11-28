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
        auto pawn1 = std::make_shared<Pawn>('p',"Black");
        bd[1][i] = pawn1;
        auto pawn2 = std::make_shared<Pawn>('P', "White");
        bd[6][i] = pawn2;
    }
    auto rook_b1 = std::make_shared<Rook>('r', "Black");
    auto rook_b2 = std::make_shared<Rook>('r', "Black");
    auto rook_w1 = std::make_shared<Rook>('R', "White");
    auto rook_w2 = std::make_shared<Rook>('R', "White");
    bd[0][0] = rook_b1;
    bd[0][7] = rook_b2;
    bd[7][0] = rook_w1;
    bd[7][7] = rook_w2;
    
    auto knight_b1 = std::make_shared<Knight>('n', "Black");
    auto knight_b2 = std::make_shared<Knight>('n', "Black");
    auto knight_w1 = std::make_shared<Knight>('N', "White");
    auto knight_w2 = std::make_shared<Knight>('N', "White");
    bd[0][1] = knight_b1;
    bd[0][6] = knight_b2;
    bd[7][1] = knight_w1;
    bd[7][6] = knight_w2;

    auto bishop_b1 = std::make_shared<Bishop>('b', "Black");
    auto bishop_b2 = std::make_shared<Bishop>('b', "Black");
    auto bishop_w1 = std::make_shared<Bishop>('B', "White");
    auto bishop_w2 = std::make_shared<Bishop>('B', "White");
    bd[0][2] = bishop_b1;
    bd[0][5] = bishop_b2;
    bd[7][2] = bishop_w1;
    bd[7][5] = bishop_w2;

    auto king_b = std::make_shared<King>('k', "Black");
    auto queen_b = std::make_shared<Queen>('q', "Black");
    bd[0][4] = king_b;
    bd[0][3] = queen_b;

    auto king_w = std::make_shared<King>('K', "White");
    auto queen_w = std::make_shared<Queen>('Q', "White");
    bd[7][3] = queen_w;
    bd[7][4] = king_w;

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

char Board::charAt(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    char piece = bd[row][col]->getPiece();
    return piece;
}

void Board::move(Position org_posn, Position new_posn) {
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

std::shared_ptr<Piece> Board::pieceAt(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    return bd[row][col];
}

std::string Board::colourAt(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    std::string colour = bd[row][col]->getColour();
    return colour;
}

bool Board::getFirstMove(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    bool firstMove = bd[row][col]->getFirstMove();
    return firstMove;
}