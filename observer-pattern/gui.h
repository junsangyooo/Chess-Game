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
public:
    void drawKing(int col, int row, char piece);
    void drawQueen(int col, int row, char piece);
    void drawRook(int col, int row, char piece);
    void drawBishop(int col, int row, char piece);
    void drawKnight(int col, int row, char piece);
    void drawPawn(int col, int row, char piece);
    Gui(std::shared_ptr<Chess> chess);
    void notify(std::string value) override;
    ~Gui();
};

#endif