#ifndef POSITION_H_
#define POSITION_H_
#include <string>
#include <stdexcept>

enum Position{
    a8 = 0, b8, c8, d8, e8, f8, g8, h8,
    a7 = 10, b7, c7, d7, e7, f7, g7, h7,
    a6 = 20, b6, c6, d6, e6, f6, g6, h6,
    a5 = 30, b5, c5, d5, e5, f5, g5, h5,
    a4 = 40, b4, c4, d4, e4, f4, g4, h4,
    a3 = 50, b3, c3, d3, e3, f3, g3, h3,
    a2 = 60, b2, c2, d2, e2, f2, g2, h2,
    a1 = 70, b1, c1, d1, e1, f1, g1, h1};

Position strToPosn(std::string str) {
    if (str == "a8") {return Position(a8);}
    else if (str == "b8") {return Position(b8);}
    else if (str == "c8") {return Position(c8);}
    else if (str == "d8") {return Position(d8);}
    else if (str == "e8") {return Position(e8);}
    else if (str == "f8") {return Position(f8);}
    else if (str == "g8") {return Position(g8);}
    else if (str == "h8") {return Position(h8);}
    else if (str == "a7") {return Position(a7);}
    else if (str == "b7") {return Position(b7);}
    else if (str == "c7") {return Position(c7);}
    else if (str == "d7") {return Position(d7);}
    else if (str == "e7") {return Position(e7);}
    else if (str == "f7") {return Position(f7);}
    else if (str == "g7") {return Position(g7);}
    else if (str == "h7") {return Position(h7);}
    else if (str == "a6") {return Position(a6);}
    else if (str == "b6") {return Position(b6);}
    else if (str == "c6") {return Position(c6);}
    else if (str == "d6") {return Position(d6);}
    else if (str == "e6") {return Position(e6);}
    else if (str == "f6") {return Position(f6);}
    else if (str == "g6") {return Position(g6);}
    else if (str == "h6") {return Position(h6);}
    else if (str == "a5") {return Position(a5);}
    else if (str == "b5") {return Position(b5);}
    else if (str == "c5") {return Position(c5);}
    else if (str == "d5") {return Position(d5);}
    else if (str == "e5") {return Position(e5);}
    else if (str == "f5") {return Position(f5);}
    else if (str == "g5") {return Position(g5);}
    else if (str == "h5") {return Position(h5);}
    else if (str == "a4") {return Position(a4);}
    else if (str == "b4") {return Position(b4);}
    else if (str == "c4") {return Position(c4);}
    else if (str == "d4") {return Position(d4);}
    else if (str == "e4") {return Position(e4);}
    else if (str == "f4") {return Position(f4);}
    else if (str == "g4") {return Position(g4);}
    else if (str == "h4") {return Position(h4);}
    else if (str == "a3") {return Position(a3);}
    else if (str == "b3") {return Position(b3);}
    else if (str == "c3") {return Position(c3);}
    else if (str == "d3") {return Position(d3);}
    else if (str == "e3") {return Position(e3);}
    else if (str == "f3") {return Position(f3);}
    else if (str == "g3") {return Position(g3);}
    else if (str == "h3") {return Position(h3);}
    else if (str == "a2") {return Position(a2);}
    else if (str == "b2") {return Position(b2);}
    else if (str == "c2") {return Position(c2);}
    else if (str == "d2") {return Position(d2);}
    else if (str == "e2") {return Position(e2);}
    else if (str == "f2") {return Position(f2);}
    else if (str == "g2") {return Position(g2);}
    else if (str == "h2") {return Position(h2);}
    else if (str == "a1") {return Position(a1);}
    else if (str == "b1") {return Position(b1);}
    else if (str == "c1") {return Position(c1);}
    else if (str == "d1") {return Position(d1);}
    else if (str == "e1") {return Position(e1);}
    else if (str == "f1") {return Position(f1);}
    else if (str == "g1") {return Position(g1);}
    else if (str == "h1") {return Position(h1);}
    else {throw std::out_of_range {"Invalid position!"};}
}

#endif