#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "pieces.h"

class Bishop : public Piece {
    char piece;
    std::string colour;
public:
    Bishop(char piece, std::string colour);
    ~Bishop();
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