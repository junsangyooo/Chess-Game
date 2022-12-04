#ifndef _GUI_H_
#define _GUI_H_
#include "observer.h"
#include "chess.h"
#include "window.h"
#include "position.h"

enum Position;

class Gui: public Observer {
    std::shared_ptr<Chess> chess;
    Xwindow xw;
    void drawKing(int col, int row, char piece);
    void drawQueen(int col, int row, char piece);
    void drawRook(int col, int row, char piece);
    void drawBishop(int col, int row, char piece);
    void drawKnight(int col, int row, char piece);
    void drawPawn(int col, int row, char piece);
public:
    Gui(std::shared_ptr<Chess> chess);
    void drawBoard(Position posn1 = Position(-1), char c1 = NULL, Position posn2 = Position(-1), char c2 = NULL, Position posn3 = Position(-1), char c3 = NULL, Position posn4 = Position(-1), char c4 = NULL) override;
    void notify(std::string value) override;
    ~Gui();
};

#endif