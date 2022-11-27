#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include "position.h"
class Subject;

class Observer {
protected:
    enum Position;
public:
    virtual void notify(std::string value) = 0;
    virtual ~Observer() = default;
};

#endif