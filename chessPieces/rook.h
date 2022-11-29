#ifndef _ROOK_H_
#define _ROOK_H_
#include "pieces.h"

class Rook : public Piece {
    char piece;
    std::string colour;
    bool firstMove = true;
    bool castling = false;
public:
    Rook(char piece, std::string colour);
    ~Rook();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() {return firstMove;}
    void setFirstMove(bool value) override {firstMove = value;}
    bool getIsChecked() const override {return false;}
    void setIsChecked(bool value) override {}
    bool getEnPassant() const override {return false;}
    void setEnPassant(bool value) override {}
    bool getCastling() const override {return castling;}
    void setCastling(bool value) override {castling = value;}
};

#endif