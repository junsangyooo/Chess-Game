#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include <vector>
#include "subject.h"
//#include "position.h"
class Subject;

class Observer {
public:
    virtual void drawBoard(std::string value = "", int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1) = 0;
    virtual void notify() = 0;
    virtual ~Observer() = default;
};

#endif
