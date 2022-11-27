#include "subject.h"

class Subject {
    enum Position;
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer> ob);
    void detach(std::shared_ptr<Observer> ob);
    void notify();
    virtual char getPiece(Position posn) const;
};

void Subject::attach(std::shared_ptr<Observer> ob) {
    observers.emplace_back(ob);
}

void Subject::detach(std::shared_ptr<Observer> ob) {
    for (auto o = observers.begin(); o != observers.end(); ++o) {
        if (*o == ob) {
            observers.erase(o);
            break;
        }
    }
}
void Subject::notify(std::string value) {
    for(auto ob: observers) {
        ob->notify(value);
    }
}