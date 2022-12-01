#include "level1.h"

LevelOne::LevelOne(std::shared_ptr<Chess> chess, std::shared_ptr<Computer> computer, std::string whitePlayer, std::string blackPlayer): chess{chess}, computer{computer}, whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {}

LevelOne::~LevelOne() {}