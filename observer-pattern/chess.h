#ifndef _CHESS_H_
#define _CHESS_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "move.h"
#include "subject.h"
#include "board.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h"
#include "scoreboard.h"

class Chess : public Subject{
    std::shared_ptr<ScoreBoard> score;
    std::vector<std::shared_ptr<Move>> moves;
    std::shared_ptr<Board> board;
    std::string whiteInCheck();
    std::string blackInCheck();
    std::string isStaleMate();
    void enPassant(std::shared_ptr<Move> movement);
    void castling(std::shared_ptr<Move> movement);
    bool validPawn(std::shared_ptr<Move> movement);
    bool validKing(std::shared_ptr<Move> movement);
    bool validQueen(std::shared_ptr<Move> movement);
    bool validRook(std::shared_ptr<Move> movement);
    bool validBishop(std::shared_ptr<Move> movement);
    bool validKnight(std::shared_ptr<Move> movement);
    bool whiteTurn = true;
public:
    void undo(bool notify);
    bool movePiece(std::shared_ptr<Move> movement);
    char getPiece(Position posn) const override;
    std::shared_ptr<Board> getBoard() {return board;}
public:
    Chess(std::shared_ptr<Board> bd, std::shared_ptr<ScoreBoard> scoreboard);
};

#endif