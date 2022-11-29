#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include "position.h"

class Board {
    std::shared_ptr<Piece> bd[8][8];
    Position whiteKing;
    Position blackKing;
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
    bool getIsChecked(Position posn) const;
    void setIsChecked(Position posn, bool value);
    Position getWhiteKing() const {return whiteKing;}
    Position getBlickKing() const {return blackKing;}
    void setWhiteKing(Position value) {whiteKing = value;}
    void setBlackKing(Position value) {blackKing = value;}
    void setPiece(Position posn, std::shared_ptr<Piece> piece);
};

#endif