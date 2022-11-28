#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include "position.h"

class Board {
    std::shared_ptr<Piece> bd[8][8];
public:
    Board();
    ~Board();
    Board(const std::shared_ptr<Board> other);
    char charAt(Position posn);
    void move(Position org_posn, Position new_posn);
    std::shared_ptr<Piece> pieceAt(Position posn);
    std::string colourAt(Position posn);
    bool getFirstMove(Position posn);
    void setFirstMove(Position posn, bool value);
    void enPassant(Position org_posn, Position new_posn);
    void castling(Position org_posn, Position new_posn);
    std::shared_ptr<Piece> getPiece(Position posn);
};

#endif