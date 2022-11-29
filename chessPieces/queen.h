#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "pieces.h"

class Queen : public Piece {
    char piece;
    std::string colour;
public:
    Queen(char piece, std::string colour);
    ~Queen();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return colour;}
    bool getFirstMove() const override {return false;}
    void setFirstMove(bool value) override {}
    bool getIsChecked() const override {return false;}
    void setIsChecked(bool value) override {}
    bool getEnPassant() const override {return false;}
    void setEnPassant(bool value) override {}
    bool getCastling() const override {return false;}
    void setCastling(bool value) override {}
};

#endif