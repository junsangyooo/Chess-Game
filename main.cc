#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "scoreboard.h"
#include "pieces.h"
#include "board.h"
#include "subject.h"
#include "chess.h"
#include "observer.h"
#include "gui.h"
#include "cli.h"
#include "controller.h"

enum Position;

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


int main() {
    ScoreBoard sb{0, 0};
    std::string command;
    bool boardExist = false;
    bool whiteTurn = true;
    std::shared_ptr<Board> board;
    std::shared_ptr<Chess> chess;
    std::shared_ptr<Controller> control;
    std::shared_ptr<Gui> graphicBoard;
    std::shared_ptr<Cli> textBoard;
    while (std::cin >> command) {
        if (!boardExist) {
            board = std::make_shared<Board>();
            chess = std::make_shared<Chess>(board,sb);
            control = std::make_shared<Controller>(chess);
            graphicBoard = std::make_shared<Gui>(chess);
            textBoard = std::make_shared<Cli>(chess);
            chess.attach(graphicBoard);
            chess.attach(textBoard);
            boardExist = true;
        }
        if (command == "exit") {
            std::cout << sb;
            break;
        } else if (command == "game"){
            std::string player1;
            std::string player2;
            std::cin >> player1 >> player2;
            control->setPlayer1(player1);
            control->setPlayer2(player2);
            bool player1IsComputer = false;
            bool player2IsCoimputer = false;
            std::shared_ptr<Computer> computer;
            if (player1 == "computer1") {
                player1IsComputer = true;
                computer = std::make_shared<LevelOne>(chess);
            } else if (player1 == "computer2") {
                player1IsComputer = true;
                computer = std::make_shared<LevelTwo>(chess);
            } else if (player1 == "computer3") {
                player1IsComputer = true;
                computer = std::make_shared<LevelThree>(chess);
            } else if (player1 == "computer4") {
                player1IsComputer = true;
                computer = std::make_shared<LevelFour>(chess);
            } else if (player2 == "computer1") {
                player2IsComputer = true;
                computer = std::make_shared<LevelOne>(chess);
            } else if (player2 == "computer2") {
                player2IsComputer = true;
                computer = std::make_shared<LevelTwo>(chess);
            } else if (player2 == "computer3") {
                player2IsComputer = true;
                computer = std::make_shared<LevelThree>(chess);
            } else if (player2 == "computer4") {
                player2IsComputer = true;
                computer = std::make_shared<LevelFour>(chess);
            }
            std::string cmd;
            while(std::cin >> cmd) {
                if (cmd == "resign") {
                    control->resign();
                    if (whiteTurn) {sb->addToBlack(1);}
                    else {sb->addToWhite(1);}
                    boardExist = false;
                    break;
                } else if (cmd == "move") {
                    std::
                }
            }
            boardExist = false;
        } else if (command == "setup") {
            std::string cmd;
            while (std::cin >> cmd) {
                if (cmd == "done") {
                    bool whitePawn = true;
                    bool blackPawn = true;
                    int whiteKing = 0;
                    int blackKing = 0;
                    bool whiteCheck = control->whiteCheck();
                    bool blackCheck = control->blackCheck();
                    for(int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            char piece = board->charAt(Position(10*i +j));
                            if (i == 0 || i == 7) {
                                if (piece == 'p') {blackPawn = false;}
                                else if (piece == 'P') {whitePawn = false;}
                            }
                            if (piece == 'k') {blackKing++;}
                            else if (piece == 'K') {whiteKing++;}
                        }
                    }
                    if (whiteKing != 1 || blackKing != 1) {
                        std::cerr << "Each side can has only one King!!!" << std::endl;
                        continue;
                    } else if (!whitePawn || !blackPawn) {
                        std::cerr << "Pawn cannot start on the first or last row!!!" << std::endl;
                        continue;
                    } else if (whiteCheck || blackCheck) {
                        std::cerr << "King should be not in check!!!" << std::endl;
                        continue;
                    } else {break;}
                } else if (cmd == "+") {
                    char piece;
                    std::string position;
                    std::cin >> piece >> position;
                    try {Position posn = strToPosn(position);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    try {board->replace(piece, posn);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                } else if (cmd == "-") {
                    std::string position;
                    std::cin >> position;
                    try {Position posn = strToPosn(position);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    std::string colour = board->colourAt(posn);
                    if (colour == "") {
                        continue;
                    }
                    board->remove(posn);
                } else if (cmd == "=") {
                    std::string colour;
                    std::cin >> colour;
                    if (colour == "White") {whiteTurn = true;}
                    else if (colour == "Black") {whiteTurn = false;}
                    else {
                        std::cerr << "Invalid colour!" << std::endl;
                        continue;
                    }
                } else {
                    std::cerr << "Please provide a valid command." << std::endl;
                    continue;
                }
                control->display();
            }
        } else {
            std::cerr << "Please provide a valid command." << std::endl;
            continue;
        }
    }
    std::cout << sb;
}