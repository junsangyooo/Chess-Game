#include <iostream>
#include <string>
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
#include "computer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

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


bool newGame() {
    std::string response;
    std::cin >> response;
    if (response == "yes") {return true;}
    else if (response == "no") { return false;}
    else {
        std::cout << "Please provide valid response." << std::endl;
        return newGame();
    }
}


bool validPiece(char piece) {
    if (piece == 'p' || piece == 'P' || piece == 'k' || piece == 'K' || piece == 'q' || piece == 'Q' || piece == 'r' || piece == 'R' ||piece == 'b' || piece == 'B' || piece == 'n' || piece == 'N') {
        return true;
    }
    return false;
}

int main() {
    std::shared_ptr<ScoreBoard> sb = std::make_shared<ScoreBoard>(0, 0);
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
            chess = std::make_shared<Chess>(board, sb);
            control = std::make_shared<Controller>(chess);
            textBoard = std::make_shared<Cli>(chess);
            graphicBoard = std::make_shared<Gui>(chess);
            chess->attach(textBoard);
            chess->attach(graphicBoard);
            whiteTurn = true;
            boardExist = true;
        }
        if (command == "exit") {
            break;
        } else if (command == "game"){
            std::string player1;
            std::string player2;
            std::cin >> player1 >> player2;
            control->setPlayer1(player1);
            control->setPlayer2(player2);
            bool player1IsComputer = false;
            bool player2IsComputer = false;
            std::shared_ptr<Computer> computer;
            if (player1 == "computer1") {
                player1IsComputer = true;
                computer = std::make_shared<LevelOne>(chess, board);
                control->setComputerWhite(computer);
            } else if (player1 == "computer2") {
                player1IsComputer = true;
                computer = std::make_shared<LevelTwo>(chess, board);
                control->setComputerWhite(computer);
            } else if (player1 == "computer3") {
                player1IsComputer = true;
                computer = std::make_shared<LevelThree>(chess, board);
                control->setComputerWhite(computer);
            } else if (player1 == "computer4") {
                player1IsComputer = true;
                computer = std::make_shared<LevelFour>(chess, board);
                control->setComputerWhite(computer);
            } else if (player2 == "computer1") {
                player2IsComputer = true;
                computer = std::make_shared<LevelOne>(chess, board);
                control->setComputerBlack(computer);
            } else if (player2 == "computer2") {
                player2IsComputer = true;
                computer = std::make_shared<LevelTwo>(chess, board);
                control->setComputerBlack(computer);
            } else if (player2 == "computer3") {
                player2IsComputer = true;
                computer = std::make_shared<LevelThree>(chess, board);
                control->setComputerBlack(computer);
            } else if (player2 == "computer4") {
                player2IsComputer = true;
                computer = std::make_shared<LevelFour>(chess, board);
                control->setComputerBlack(computer);
            }
            std::string cmd;
            bool gameEnd = false;
            while(std::cin >> cmd) {
                if (gameEnd) {break;}
                if (cmd == "resign") {
                    control->resign(whiteTurn);
                    if (whiteTurn) {sb->addToBlack(1);}
                    else {sb->addToWhite(1);}
                    break;
                } else if (cmd == "move") {
                    if (whiteTurn && player1IsComputer) {
                        gameEnd = control->computerMove(whiteTurn);
                        whiteTurn = !whiteTurn;
                        continue;
                    } else if (!whiteTurn && player2IsComputer) {
                        gameEnd = control->computerMove(whiteTurn);
                        whiteTurn = !whiteTurn;
                        continue;
                    }
                    std::string posn1;
                    std::string posn2;
                    Position firstPosn;
                    Position secondPosn;
                    std::cin >> posn1 >> posn2;
                    try {firstPosn = strToPosn(posn1);}
                    catch(std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    try {secondPosn = strToPosn(posn2);}
                    catch(std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    char piece = board->charAt(firstPosn);
                    char promoted;
                    if ((piece == 'p' && 60 <= secondPosn && secondPosn <= 67) || (piece == 'P' && 10 <= secondPosn && secondPosn <= 17)) {
                        std::cin >> promoted;
                        if (promoted != 'r' && promoted != 'R' && promoted != 'n' && promoted != 'N' && promoted != 'b' && promoted != 'B' && promoted != 'q' && promoted != 'Q') {
                            std::cerr << "Please provide a valid piece." << std::endl;
                            continue;
                        }
                        if (piece == 'p' && 'A' <= promoted && promoted <= 'Z') {
                            std::cerr << "You cannont promote to the opponent's piece." << std::endl;
                            continue;
                        } else if (piece == 'P' && 'a' <= promoted && promoted <= 'z') {
                            std::cerr << "You cannont promote to the opponent's piece." << std::endl;
                            continue;
                        }
                        try {gameEnd = control->pawnPromote(firstPosn, secondPosn, whiteTurn, piece);}
                        catch (std::out_of_range &e) {
                            std::cerr << e.what() << std::endl;
                            continue;
                        }
                        continue;
                    }
                    try {gameEnd = control->move(firstPosn, secondPosn, whiteTurn);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    whiteTurn = !whiteTurn;
                    continue;
                } else if (cmd == "undo") {
                    try{control->undo();}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    whiteTurn = !whiteTurn;
                }
            }
            std::cout << "Game ended. Do you want to play again? (yes/no)" << std::endl;
            bool restart = newGame();
            if (!restart) {
                break;
            } else {
                boardExist = false;
                continue;
            }
        } else if (command == "setup") {
            std::string cmd;
            int changedPosn;
            while (std::cin >> cmd) {
                if (cmd == "done") {
                    int whiteKing = 0;
                    int blackKing = 0;
                    bool check = control->check();
                    if (check) {
                        std::cerr << "King should be not in check!!!" << std::endl;
                        continue;
                    }
                    for(int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            char piece = board->charAt(Position(10*i +j));
                            if (i == 0 || i == 7) {
                                if (piece == 'p' || piece == 'P') {
                                    std::cerr << "Pawn cannot start on the first or last row!!!" << std::endl;
                                    continue;
                                }
                            }
                            if (piece == 'k') {blackKing++;}
                            else if (piece == 'K') {whiteKing++;}
                        }
                    }
                    if (whiteKing != 1 || blackKing != 1) {
                        std::cerr << "Each side can has only one King!!!" << std::endl;
                        continue;
                    }
                    break;
                } else if (cmd == "+") {
                    char piece;
                    std::string position;
                    std::cin >> piece >> position;
                    Position posn;
                    try {posn = strToPosn(position);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    try {board->replace(piece, posn);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    changedPosn = ((posn / 10) * 10) + (posn % 10);
                } else if (cmd == "-") {
                    std::string position;
                    std::cin >> position;
                    Position posn;
                    try {posn = strToPosn(position);}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    char c = board->charAt(posn);
                    if (c == ' ' || c == '-') {
                        continue;
                    }
                    board->remove(posn);
                    changedPosn = ((posn / 10) * 10) + (posn % 10);
                } else if (cmd == "=") {
                    std::string colour;
                    std::cin >> colour;
                    if (colour == "White") {whiteTurn = true;}
                    else if (colour == "Black") {whiteTurn = false;}
                    else {
                        std::cerr << "Invalid colour!" << std::endl;
                        continue;
                    }
                    continue;
                } else {
                    std::cerr << "Please provide a valid command." << std::endl;
                    continue;
                }
                control->display(changedPosn);
            }
        } else {
            std::cerr << "Please provide a valid command." << std::endl;
            continue;
        }
    }
    std::cout << sb;
}