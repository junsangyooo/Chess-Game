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
    std::shared_ptr<Board> board;
    std::shared_ptr<ScoreBoard> score;
    std::vector<std::shared_ptr<Move>> moves;
    bool enPassant(std::shared_ptr<Move> movement, bool whiteTurn);
    bool castling(std::shared_ptr<Move> movement, bool whiteTurn);
    bool validKing(std::shared_ptr<Move> movement, bool whiteTurn);
    bool validQueen(std::shared_ptr<Move> movement, bool whiteTurn);
    bool validRook(std::shared_ptr<Move> movement, bool whiteTurn);
    bool validKnight(std::shared_ptr<Move> movement, bool whiteTurn);
    bool validBishop(std::shared_ptr<Move> movement, bool whiteTurn);
    bool validPawn(std::shared_ptr<Move> movement, bool whiteTurn, char promote = '.');
public:
    std::string whiteInCheck();
    std::string blackInCheck();
    bool validMove(std::shared_ptr<Move> movement, bool whiteTurn, char promote = '.');
    bool movePiece(std::shared_ptr<Move> movement, bool whiteTurn, char promote = '.');
    bool pawnPromote(std::shared_ptr<Move> movement, char piece);
    char charAt(Position posn) const override;
    void undo(bool display);
    std::string checkTest();
    std::string checkmateTest(bool whiteTurn);
    std::string stalemateTest(bool whiteTurn);
public:
    Chess(std::shared_ptr<Board> bd, std::shared_ptr<ScoreBoard> scoreboard);
    ~Chess();
};

#endif