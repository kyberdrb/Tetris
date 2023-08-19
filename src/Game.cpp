#include "Game.h"

#include <chrono>
#include <thread>
#include <iostream>

Game::Game() :
    constructionSite(std::make_unique<ConstructionSite>(3, 5))
{}

void Game::runGame() {
    clearTerminal();

    // TODO transform linear steps in Game into a for/while loop
    //while (true) {
        //loadInputFromTerminal();
        //recalculateGameLogic();
        //drawFrameOnTerminal();
        //clearTerminal();
    //}

    drawFrameOnTerminal();
    loadInputFromTerminal();
    clearTerminal();

    constructionSite->makeBrickVisible();
    drawFrameOnTerminal();
    loadInputFromTerminal();
    clearTerminal();

    constructionSite->moveBrickLower();
    drawFrameOnTerminal();
}

void Game::loadInputFromTerminal() {
    std::cout << "enter command(s): ";
    std::cin >> keyboardInputCharacters;
};

void Game::recalculateGameLogic() {
    // if brick is not visible
        // make it visible
        // return / switch to other state?
    // if brick is visible
        // put it down
        // return / switch to other state?
    // if brick is deactivated
        // create a new brick/building block
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
