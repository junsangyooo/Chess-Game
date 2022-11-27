#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <memory>
#include <string>
#include "position.h"

class Observer;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
protected:
    enum Position;
public:
    void attach(std::shared_ptr<Observer> ob);
    void detach(std::shared_ptr<Observer> ob);
    void notify(std::string value);
    virtual char getPiece(Position posn) const = 0;
    virtual ~Subject() = default;
};


#endif