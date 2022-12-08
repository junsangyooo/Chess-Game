#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <memory>
#include "position.h"
#include "observer.h"

enum Position;
class Observer;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer> ob);
    void detach(std::string type);
    void drawBoard(std::string value = "", int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1);
    virtual char charAt(Position posn) const = 0;
    virtual ~Subject() = default;
};


#endif
