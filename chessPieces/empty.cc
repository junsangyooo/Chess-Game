#include "empty.h"

Empty::Empty(char piece): piece{piece}{}

bool Empty::validMove(Position org_posn, Position new_posn) const {return true;}

Empty::~Empty() {}