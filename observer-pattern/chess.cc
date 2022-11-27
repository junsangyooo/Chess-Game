#include "chess.h"

Chess::Chess(std::shared_ptr<Board> bd): board{bd} {
    boards.emplace_back(bd);
}

void Chess::movePiece(Position org_posn, Position new_posn) {
    char piece = getPiece(org_posn);
    bool valid_move = false;
    if (piece == 'p') {
        auto tmp = std::make_shared<Pawn>("black");
        valid_move = tmp->validMove(org_posn, new_posn);
    } else if(piece == 'P') {
        auto tmp = std::make_shared<Pawn>("white");
        valid_move = tmp->validMove(org_posn, new_posn);
    } else if (piece == 'k' || piece == 'K') {
        auto tmp = std::make_shared<King>();
        valid_move = tmp->validMove(org_posn, new_posn);
    } else if (piece == 'q' || piece == 'Q') {
        auto tmp = std::make_shared<Queen>();
        valid_move = tmp->validMove(org_posn, new_posn);
    } else if (piece == 'n' || piece == 'N') {
        auto tmp = std::make_shared<Knight>();
        valid_move = tmp->validMove(org_posn, new_posn);
    } else if (piece == 'r' || piece == 'R') {
        auto tmp = std::make_shared<Rook>();
        valid_move = tmp->validMove(org_posn, new_posn);
    } else if (piece == 'b' || piece == 'B') {
        auto tmp = std::make_shared<Bishop>();
        valid_move = tmp->validMove(org_posn, new_posn);
    }
    if (!valid_move && (piece == 'p' || piece == 'P')) {
        valid_move = ex
    }
}