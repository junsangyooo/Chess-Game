#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include "subject.h"
class Subject;

class Observer {
public:
    virtual void drawBoard() = 0;
    virtual void notify(std::string value) = 0;
    virtual ~Observer() = default;
};

#endif