#pragma once

#include "ConstructionSite.h"

#include <memory>

class Game {
public:
    Game();

    void startGameForMonominos();
//    void startGameForDominos();

private:
    std::unique_ptr<ConstructionSite> constructionSite;
    std::string keyboardInputCharacters;

    void loadInputFromTerminal();
    void recalculateGameLogic();
    void clearTerminal();
    void drawFrameOnTerminal() const;
};
