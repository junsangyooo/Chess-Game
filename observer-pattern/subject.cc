#include "subject.h"

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