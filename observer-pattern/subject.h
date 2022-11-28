#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <memory>
#include <string>
#include "position.h"
#include "observer.h"

enum Position;
class Observer;

class Subject {
    std::vector<Observer*> observers;

public:
    void attach(Observer* ob);
    void detach(Observer* ob);
    void notify(std::string value);
    virtual char getPiece(Position posn) const = 0;
    virtual ~Subject() = default;
};


#endif