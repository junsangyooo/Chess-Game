#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "empty.h"
#include "move.h"

class Board {
    std::shared_ptr<Piece> bd[8][8];
public:
    Board();
    ~Board();
    char charAt(Position posn);
    std::shared_ptr<Piece> getPiece(Position posn);
    void setPiece(Position posn, std::shared_ptr<Piece> piece);
    bool getFirstMove(Position posn);
    void setFirstMove(Position posn, bool value);
    void enPassant(std::shared_ptr<Move> movement);
    void castling(std::shared_ptr<Move> movement);
    bool getEnPassant(Position posn);
    void setEnPassant(Position posn, bool value);
    void replace(char c, Position posn);
    void remove(Position posn);
    void move(std::shared_ptr<Move> movement, char piece = '.');
    bool getPromoted(Position posn);
    void setPromoted(Position posn, bool value);
    void setWhenPromoted(Position posn, int value);
    int getWhenPromoted(Position posn);
    void setWhenFirstMove(Position posn, int value);
    int getWhenFirstMove(Position posn);
    void undo(std::shared_ptr<Move> movement);
    void undoPromoted(std::shared_ptr<Move> movement);
    void undoEnPassant(std::shared_ptr<Move> movement);
    void undoCastling(std::shared_ptr<Move> movement);
};

#endif
