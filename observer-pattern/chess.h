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

class Chess : public Subject{
    std::vector<std::shared_ptr<Move>> moves;
    std::shared_ptr<Board> board;
    bool isCheck(std::shared_ptr<Board> bd);
    bool isCheckMate(std::shared_ptr<Board> bd);
    bool isStaleMate(std::shared_ptr<Board> bd);
    bool whiteTurn = true;
public:
    void movePiece(Position org_posn, Position new_posn);
    char getPiece(Position posn) const override;
    std::shared_ptr<Board> getBoard() {return board;}
public:
    Chess(std::shared_ptr<Board> bd);
};

#endif