#include "board.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                bd[i][j] = ' ';
            } else {
                bd[i][j] = '-';
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        bd[1][i] = 'p';
        bd[6][i] = 'P';
    }
    bd[0][0] = 'r';
    bd[0][1] = 'n';
    bd[0][2] = 'b';
    bd[0][3] = 'q';
    bd[0][4] = 'k';
    bd[0][5] = 'b';
    bd[0][6] = 'n';
    bd[0][7] = 'r';
    bd[7][0] = 'R';
    bd[7][1] = 'N';
    bd[7][2] = 'B';
    bd[7][3] = 'Q';
    bd[7][4] = 'K';
    bd[7][5] = 'B';
    bd[7][6] = 'N';
    bd[7][7] = 'R';
}

char Board::charAt(Position posn) {
    int col = posn % 10;
    int row = posn / 10;
    char piece = bd[row][col];
    return piece;
}