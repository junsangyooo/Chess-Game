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
#include "subject.h"
#include "board.h"

class Chess : Subject{
    std::vector<std::shared_ptr<Board>> boards;
    std::shared_ptr<Board> board;
    bool isCheck(std::shared_ptr<Board> bd);
    bool isCheckMate(std::shared_ptr<Board> bd);
    bool isStaleMate(std::shared_ptr<Board> bd);
public:
    void movePiece(Position org_posn, Position new_posn);
    char getPiece(Position posn) const override;
    std::shared_ptr<Board> getBoard() {return boards.back();}
};

#endif