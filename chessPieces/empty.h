#ifndef _EMPTY_H_
#define _EMPTY_H_
#include "pieces.h"

class Empty : public Piece {
    char piece;
public:
    Empty(char piece);
    ~Empty();
public:
    char getPiece() const override {return piece;}
    std::string getColour() const override{return "";}
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