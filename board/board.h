#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include "position.h"

class Board {
    std::shared_ptr<Piece> bd[8][8];
    Position whiteKing;
    Position blackKing;
    void enPassant(Position org_posn, Position new_posn);
    void castling(Position org_posn, Position new_posn);
public:
    Board();
    ~Board();
    Board(const std::shared_ptr<Board> other);
    char charAt(Position posn);
    std::string colourAt(Position posn); 
    std::shared_ptr<Piece> getPiece(Position posn);
    void setPiece(Position posn, std::shared_ptr<Piece> piece);
    bool getFirstMove(Position posn);
    void setFirstMove(Position posn, bool value);
    bool getIsChecked(Position posn) const;
    void setIsChecked(Position posn, bool value);
    Position getWhiteKing() const {return whiteKing;}
    Position getBlackKing() const {return blackKing;}
    void setWhiteKing(Position value) {whiteKing = value;}
    void setBlackKing(Position value) {blackKing = value;}
    bool getEnPassant(Position posn);
    void setEnPassant(Position posn, bool value);
    bool getCastling(Position posn);
    void setCastling(Position posn, bool value);
    void replace(char c, Position posn);
    void remove(Position posn);
    void move(Position org_posn, Position new_posn);
};

#endif