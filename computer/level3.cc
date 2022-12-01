#include "level3.h"

LevelThree::LevelThree(std::shared_ptr<Chess> chess, std::shared_ptr<Computer> computer, std::string whitePlayer, std::string blackPlayer): chess{chess}, computer{computer}, whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {}

LevelThree::~LevelThree() {}