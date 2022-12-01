#include "computer.h"

Computer::Computer(std::shared_ptr<Chess> chess, std::string whitePlayer, std::string blackPlayer): chess{chess}, whitePlayer{whitePlayer}, blackPlayer{blackPlayer} {}

Computer::~Computer() {}