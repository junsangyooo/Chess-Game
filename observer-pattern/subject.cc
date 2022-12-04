#include "subject.h"

void Subject::attach(std::shared_ptr<Observer> ob) {
    observers.emplace_back(ob);
}

void Subject::detach(std::string type) {
    if (type == "Cli") {
        observers.erase(observers.begin());
    } else {
        observers.erase(observers.end());
    }
}

void Subject::drawBoard(std::string value = "", int posn1 = -1, int posn2 = -1, int posn3 = -1, int posn4 = -1) {
    for (auto ob: observers) {
        ob->drawBoard(value, posn1, posn2, posn3, posn4);
    }
}