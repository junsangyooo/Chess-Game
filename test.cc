#include <iostream>
//#include "window.h"

int main() {
    Xwindow xw{240, 240};
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int posn = row + col;
            if (posn % 2 == 0) {
                xw.fillRectangle(col*30, row*30, 30, 30, Xwindow::Yellow);
            } else {
                xw.fillRectangle(col*30, row*30, 30, 30, Xwindow::Brown);
            }
            int colour;
            if (row == 0) {
                colour = Xwindow::Black;
                if (col == 0 || col == 7) {
                    xw.fillRectangle(col*30+6, row*30+6, 5, 4, colour);
                    xw.fillRectangle(col*30+14, row*30+6, 4, 4, colour);
                    xw.fillRectangle(col*30+21, row*30+6, 5, 4, colour);
                    xw.fillRectangle(col*30+6, row*30+10, 20, 4, colour);
                    xw.fillRectangle(col*30+11, row*30+14, 10, 8, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else if (col == 1 || col == 6) {
                    xw.fillRectangle(col*30+11, row*30+5, 2, 1, colour);
                    xw.fillRectangle(col*30+14, row*30+5, 2, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+6, 6, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+7, 7, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+8, 8, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+9, 2, 1, colour);
                    xw.fillRectangle(col*30+14, row*30+9, 7, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+10, 11, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+11, 12, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+12, 14, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+13, 15, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+14, 7, 1, colour);
                    xw.fillRectangle(col*30+16, row*30+14, 7, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+15, 4, 1, colour);
                    xw.fillRectangle(col*30+15, row*30+15, 8, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+16, 2, 1, colour);
                    xw.fillRectangle(col*30+14, row*30+16, 9, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+17, 10, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+18, 11, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+19, 12, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+20, 13, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+21, 14, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else if (col == 2 || col == 5) {
                    xw.fillRectangle(col*30+15, row*30+4, 2, 2, colour);
                    xw.fillRectangle(col*30+14, row*30+6, 4, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+7, 6, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+8, 6, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+9, 6, 1, colour);
                    xw.fillRectangle(col*30+20, row*30+9, 1, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+10, 6, 1, colour);
                    xw.fillRectangle(col*30+19, row*30+10, 3, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+11, 6, 1, colour);
                    xw.fillRectangle(col*30+18, row*30+11, 5, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+12, 6, 1, colour);
                    xw.fillRectangle(col*30+17, row*30+12, 7, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+13, 6, 1, colour);
                    xw.fillRectangle(col*30+16, row*30+13, 9, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+14, 8, 1, colour);
                    xw.fillRectangle(col*30+15, row*30+14, 12, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+15, 20, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+16, 18, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+17, 16, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+18, 14, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+19, 12, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+20, 10, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else if (col == 3) {
                    xw.fillRectangle(col*30+15, row*30+5, 2, 3, colour);
                    xw.fillRectangle(col*30+14, row*30+8, 4, 2, colour);
                    xw.fillRectangle(col*30+3, row*30+9, 2, 1, colour);
                    xw.fillRectangle(col*30+27, row*30+9, 2, 1, colour);
                    xw.fillRectangle(col*30+4, row*30+10, 2, 1, colour);
                    xw.fillRectangle(col*30+26, row*30+10, 2, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+10, 6, 1, colour);
                    xw.fillRectangle(col*30+4, row*30+11, 3, 1, colour);
                    xw.fillRectangle(col*30+25, row*30+11, 3, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+11, 8, 1, colour);
                    xw.fillRectangle(col*30+5, row*30+12, 5, 1, colour);
                    xw.fillRectangle(col*30+22, row*30+12, 5, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+12, 10, 1, colour);
                    xw.fillRectangle(col*30+5, row*30+13, 22, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+14, 20, 2, colour);
                    xw.fillRectangle(col*30+7, row*30+16, 18, 2, colour);
                    xw.fillRectangle(col*30+8, row*30+18, 16, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+19, 14, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+20, 12, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+21, 16, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else {
                    xw.fillRectangle(col*30+15, row*30+2, 2, 2, colour);
                    xw.fillRectangle(col*30+13, row*30+4, 6, 2, colour);
                    xw.fillRectangle(col*30+15, row*30+6, 2, 3, colour);
                    xw.fillRectangle(col*30+11, row*30+8, 2, 1, colour);
                    xw.fillRectangle(col*30+19, row*30+8, 2, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+9, 14, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+10, 18, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+11, 20, 2, colour);
                    xw.fillRectangle(col*30+5, row*30+13, 22, 3, colour);
                    xw.fillRectangle(col*30+6, row*30+16, 20, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+17, 18, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+18, 14, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+19, 12, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+20, 8, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                }
            } else if (row == 1) {
                colour = Xwindow::Black;
                xw.fillRectangle(col*30+15, row*30+6, 2, 1, colour);
                xw.fillRectangle(col*30+14, row*30+7, 4, 1, colour);
                xw.fillRectangle(col*30+13, row*30+8, 6, 1, colour);
                xw.fillRectangle(col*30+14, row*30+9, 4, 1, colour);
                xw.fillRectangle(col*30+15, row*30+10, 2, 1, colour);
                xw.fillRectangle(col*30+12, row*30+11, 8, 1, colour);
                xw.fillRectangle(col*30+14, row*30+12, 4, 2, colour);
                xw.fillRectangle(col*30+15, row*30+14, 2, 1, colour);
                xw.fillRectangle(col*30+14, row*30+15, 4, 2, colour);
                xw.fillRectangle(col*30+13, row*30+17, 6, 2, colour);
                xw.fillRectangle(col*30+12, row*30+19, 8, 2, colour);
                xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
                xw.fillRectangle(col*30+9, row*30+22, 14, 1, colour);
                xw.fillRectangle(col*30+7, row*30+23, 18, 2, colour);
            } else if (row == 6) {
                colour = Xwindow::White;
                xw.fillRectangle(col*30+15, row*30+6, 2, 1, colour);
                xw.fillRectangle(col*30+14, row*30+7, 4, 1, colour);
                xw.fillRectangle(col*30+13, row*30+8, 6, 1, colour);
                xw.fillRectangle(col*30+14, row*30+9, 4, 1, colour);
                xw.fillRectangle(col*30+15, row*30+10, 2, 1, colour);
                xw.fillRectangle(col*30+12, row*30+11, 8, 1, colour);
                xw.fillRectangle(col*30+14, row*30+12, 4, 2, colour);
                xw.fillRectangle(col*30+15, row*30+14, 2, 1, colour);
                xw.fillRectangle(col*30+14, row*30+15, 4, 2, colour);
                xw.fillRectangle(col*30+13, row*30+17, 6, 2, colour);
                xw.fillRectangle(col*30+12, row*30+19, 8, 2, colour);
                xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
                xw.fillRectangle(col*30+9, row*30+22, 14, 1, colour);
                xw.fillRectangle(col*30+7, row*30+23, 18, 2, colour);
            } else if (row == 7){
                colour = Xwindow::White;
                if (col == 0 || col == 7) {
                    xw.fillRectangle(col*30+6, row*30+6, 5, 4, colour);
                    xw.fillRectangle(col*30+14, row*30+6, 4, 4, colour);
                    xw.fillRectangle(col*30+21, row*30+6, 5, 4, colour);
                    xw.fillRectangle(col*30+6, row*30+10, 20, 4, colour);
                    xw.fillRectangle(col*30+11, row*30+14, 10, 8, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else if (col == 1 || col == 6) {
                    xw.fillRectangle(col*30+11, row*30+5, 2, 1, colour);
                    xw.fillRectangle(col*30+14, row*30+5, 2, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+6, 6, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+7, 7, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+8, 8, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+9, 2, 1, colour);
                    xw.fillRectangle(col*30+14, row*30+9, 7, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+10, 11, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+11, 12, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+12, 14, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+13, 15, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+14, 7, 1, colour);
                    xw.fillRectangle(col*30+16, row*30+14, 7, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+15, 4, 1, colour);
                    xw.fillRectangle(col*30+15, row*30+15, 8, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+16, 2, 1, colour);
                    xw.fillRectangle(col*30+14, row*30+16, 9, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+17, 10, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+18, 11, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+19, 12, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+20, 13, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+21, 14, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else if (col == 2 || col == 5) {
                    xw.fillRectangle(col*30+15, row*30+4, 2, 2, colour);
                    xw.fillRectangle(col*30+14, row*30+6, 4, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+7, 6, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+8, 6, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+9, 6, 1, colour);
                    xw.fillRectangle(col*30+20, row*30+9, 1, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+10, 6, 1, colour);
                    xw.fillRectangle(col*30+19, row*30+10, 3, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+11, 6, 1, colour);
                    xw.fillRectangle(col*30+18, row*30+11, 5, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+12, 6, 1, colour);
                    xw.fillRectangle(col*30+17, row*30+12, 7, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+13, 6, 1, colour);
                    xw.fillRectangle(col*30+16, row*30+13, 9, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+14, 8, 1, colour);
                    xw.fillRectangle(col*30+15, row*30+14, 12, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+15, 20, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+16, 18, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+17, 16, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+18, 14, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+19, 12, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+20, 10, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else if (col == 3) {
                    xw.fillRectangle(col*30+15, row*30+2, 2, 2, colour);
                    xw.fillRectangle(col*30+13, row*30+4, 6, 2, colour);
                    xw.fillRectangle(col*30+15, row*30+6, 2, 3, colour);
                    xw.fillRectangle(col*30+11, row*30+8, 2, 1, colour);
                    xw.fillRectangle(col*30+19, row*30+8, 2, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+9, 14, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+10, 18, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+11, 20, 2, colour);
                    xw.fillRectangle(col*30+5, row*30+13, 22, 3, colour);
                    xw.fillRectangle(col*30+6, row*30+16, 20, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+17, 18, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+18, 14, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+19, 12, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+20, 8, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+21, 12, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                } else {
                    xw.fillRectangle(col*30+15, row*30+5, 2, 3, colour);
                    xw.fillRectangle(col*30+14, row*30+8, 4, 2, colour);
                    xw.fillRectangle(col*30+3, row*30+9, 2, 1, colour);
                    xw.fillRectangle(col*30+27, row*30+9, 2, 1, colour);
                    xw.fillRectangle(col*30+4, row*30+10, 2, 1, colour);
                    xw.fillRectangle(col*30+26, row*30+10, 2, 1, colour);
                    xw.fillRectangle(col*30+13, row*30+10, 6, 1, colour);
                    xw.fillRectangle(col*30+4, row*30+11, 3, 1, colour);
                    xw.fillRectangle(col*30+25, row*30+11, 3, 1, colour);
                    xw.fillRectangle(col*30+12, row*30+11, 8, 1, colour);
                    xw.fillRectangle(col*30+5, row*30+12, 5, 1, colour);
                    xw.fillRectangle(col*30+22, row*30+12, 5, 1, colour);
                    xw.fillRectangle(col*30+11, row*30+12, 10, 1, colour);
                    xw.fillRectangle(col*30+5, row*30+13, 22, 1, colour);
                    xw.fillRectangle(col*30+6, row*30+14, 20, 2, colour);
                    xw.fillRectangle(col*30+7, row*30+16, 18, 2, colour);
                    xw.fillRectangle(col*30+8, row*30+18, 16, 1, colour);
                    xw.fillRectangle(col*30+9, row*30+19, 14, 1, colour);
                    xw.fillRectangle(col*30+10, row*30+20, 12, 1, colour);
                    xw.fillRectangle(col*30+8, row*30+21, 16, 1, colour);
                    xw.fillRectangle(col*30+7, row*30+22, 18, 3, colour);
                }
            }
        }
    }
    int c;
    std::cin >> c;
}