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
//#include "gui.h"
#include "cli.h"
#include "controller.h"

enum Position;


int main() {
    std::shared_ptr<ScoreBoard> sb{0, 0};
    std::string command;
    bool boardExist = false;
    bool whiteTurn = true;
    std::shared_ptr<Board> board;
    //Chess chess;
    //Controller control;
    //std::shared_ptr<Gui> graphicBoard;
    std::shared_ptr<Cli> textBoard;
    while (std::cin >> command) {
        if (!boardExist) {
            board = std::make_shared<Board>();
            Chess chess{board, sb};
            Controller control{chess};
            graphicBoard = std::make_shared<Gui>(chess);
            textBoard = std::make_shared<Cli>(chess);
            chess.attach(graphicBoard);
            chess.attach(textBoard);
            whiteTurn = true;
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
            while(!gameEnd) {
                if (cmd == "resign") {
                    control->resign();
                    if (whiteTurn) {sb->addToBlack(1);}
                    else {sb->addToWhite(1);}
                    boardExist = false;
                    break;
                } else if (cmd == "move") {
                    if (whitTurn && player1IsComputer) {
                        gameEnd = control->computerMove(whiteTurn);
                        continue;
                    } else if (!whiteTurn && player2IsComputer) {
                        gameEnd = control->computerMove(whiteTurn);
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
                    if ((piece == 'p' && 70 <= secondPosn && secondPosn <= 77) || (piece == 'P' && 0 <= secondPosn && secondPosn <= 7)) {
                        std::cin >> promoted;
                        if (promoted == '') {
                            std::cerr << "Please provide which piece pawn to be promoted to." << std::endl;
                        }
                        try {gameEnd = control->pawnPromote(firstPosn, secondPosn, piece);}
                        catch (std::out_of_range &e) {
                            std::cerr << e.what() << std::endl;
                            continue;
                        }
                        continue;
                    }
                    gameEnd = control->move(firstPosn, secondPosn, whiteTurn);
                    whiteturn = !whiteTurn;
                    continue;
                } else if (cmd == "undo") {
                    try{control->undo();}
                    catch (std::out_of_range &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                    whtieturn = !whiteTurn;
                }
            }
            board = nullptr;
            
            boardExist = false;
        } else if (command == "setup") {
            std::string cmd;
            while (std::cin >> cmd) {
                if (cmd == "done") {
                    int whiteKing = 0;
                    int blackKing = 0;
                    bool whiteCheck = control->whiteCheck();
                    bool blackCheck = control->blackCheck();
                    if (whiteCheck || blackCheck) {
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
                } else if (cmd == "-") {
                    std::string position;
                    std::cin >> position;
                    Position posn;
                    try {posn = strToPosn(position);}
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