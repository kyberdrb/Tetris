#include "Game.h"

#include <thread>
#include <iostream>

Game::Game() :
//    constructionSite(std::make_unique<ConstructionSite>(3, 5))
//    constructionSite(std::make_unique<ConstructionSite>(5, 7))
    constructionSite(std::make_unique<ConstructionSite>(5, 6))
{}

void Game::startGame() {
    while (this->keyboardInputCharacters != "q") {
        // GAME LOOP: DRAW / REDRAW
        this->clearTerminal();
        this->drawFrameOnTerminal();

        // GAME LOOP: LOAD INPUT
        this->loadInputFromTerminal();

        // GAME LOOP: MODIFY GAME STATE / RECALCULATE GAME STATE
        if (this->constructionSite->isActiveBrickHidden() ) {
            this->constructionSite->makeActiveBrickVisible();
            continue;
        }

        if (this->keyboardInputCharacters == "d") {
            this->constructionSite->moveActiveBrickDown();
//            continue;
        }
        if (this->keyboardInputCharacters == "l") {
            this->constructionSite->moveActiveBrickLeft();
//            continue;
        }
        if (this->keyboardInputCharacters == "r") {
            this->constructionSite->moveActiveBrickRight();
//            continue;
        }
    }
// WHILE LOOP - GAME LOOP - END
}

void Game::loadInputFromTerminal() {
    std::cout << "enter command(s): ";
    std::cin >> this->keyboardInputCharacters;
    // TODO process input
};

void Game::recalculateGameLogic() {
    // TODO recalculate game logic according to the user's input
    // if brick_1 is not visible
        // make it visible
        // return / switch to other state?
    // if brick_1 is visible
        // put it down
        // return / switch to other state?
    // if brick_1 is deactivated
        // create a new brick_1/building block
        // return / switch to other state?
    // if there are consecutive lines in the ConstructionSite's playingField
        // remove them
        // rearrange the playingField by gravity
        // return / switch to other state?
}

void Game::drawFrameOnTerminal() const {
    std::cout << constructionSite->getCurrentPlayingField() << std::flush;
}

void Game::clearTerminal() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
