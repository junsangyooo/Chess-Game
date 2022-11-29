#ifndef _KING_H_
#define _KING_H_
#include "pieces.h"

class King : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
    bool isChecked = false;
    bool castling = false;
public:
    King(char piece, std::string colour);
    ~King();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() const override {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getIsChecked() const override {return isChecked;}
    void setIsChecked(bool value) override {isChecked = value;}
    bool getEnPassant() const override {return false;}
    void setEnPassant(bool value) override {}
    bool getCastling() const override {return castling;}
    void setCastling(bool value) override {castling = value;}
};

#endif