#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include <vector>
#include "subject.h"
#include "position.h"
class Subject;

class Observer {
public:
    virtual void drawBoard(Position posn1 = Position(-1), char c1 = NULL, Position posn2 = Position(-1), char c2 = NULL, Position posn3 = Position(-1), char c3 = NULL, Position posn4 = Position(-1), char c4 = NULL) = 0;
    virtual void notify(std::string value) = 0;
    virtual ~Observer() = default;
};

#endif