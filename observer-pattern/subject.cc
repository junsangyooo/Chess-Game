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

void Subject::drawBoard() {
    for (auto ob: observers) {
        ob->drawBoard();
    }
}

void Subject::notify(std::string value) {
    for(auto ob: observers) {
        ob->notify(value);
    }
}