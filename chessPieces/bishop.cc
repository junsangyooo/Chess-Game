#include "bishop.h"

//Bishop::Bishop(char piece, std::string colour): piece{piece}, colour{colour} {}
Bishop::Bishop(char piece): piece{piece} {}

Bishop::~Bishop() {}

char Bishop::getPiece() const {return piece;}
