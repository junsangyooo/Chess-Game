#include "subject.h"

void Subject::attach(Observer* ob) {
    observers.emplace_back(ob);
}

void Subject::detach(Observer* ob) {
    for (auto o = observers.begin(); o != observers.end(); ++o) {
        if (*o == ob) {
            observers.erase(o);
            delete ob;
            break;
        }
    }
}
void Subject::notify(std::string value) {
    for(auto ob: observers) {
        ob->notify(value);
    }
}