#include "Game.h"

#include <thread>
#include <iostream>

Game::Game() :
//    constructionSite(std::make_unique<ConstructionSite>(3, 5))
//    constructionSite(std::make_unique<ConstructionSite>(5, 7))
    constructionSite(std::make_unique<ConstructionSite>(5, 6))
{}

//void Game::startGameForMonominos() {
//    // WHILE LOOP - GAME LOOP - BEGIN
//    while (this->keyboardInputCharacters != "q") {
//        // GAME LOOP: DRAW / REDRAW
//        this->clearTerminal();
//        this->drawFrameOnTerminalForMonominos();
//
//        // GAME LOOP: LOAD INPUT
//        this->loadInputFromTerminal();
//
//        // GAME LOOP: MODIFY GAME STATE / RECALCULATE GAME STATE...
//        //   ...by internal state
//        if (this->constructionSite->isMonominoSpawningSpotPopulatedWithFrozenMonomino() ) {
//            break;
//        }
//
//        if (this->constructionSite->isActiveMonominoHidden() ) {
//            this->constructionSite->makeActiveMonominoVisible();
//            continue;
//        }
//
//        //   ...by external input
//        if (this->keyboardInputCharacters == "d") {
//            this->constructionSite->moveActiveMonominoDown();
//            continue;
//        }
//        if (this->keyboardInputCharacters == "l") {
//            this->constructionSite->moveActiveMonominoLeft();
//            continue;
//        }
//        if (this->keyboardInputCharacters == "r") {
//            this->constructionSite->moveActiveMonominoRight();
//            continue;
//        }
//    }
//    // WHILE LOOP - GAME LOOP - END
//}

void Game::startGameForDominos() {
    // WHILE LOOP - GAME LOOP - BEGIN
    while (this->keyboardInputCharacters != "q") {
        // GAME LOOP: DRAW / REDRAW
        this->clearTerminal();
        this->drawFrameOnTerminalForDominos();

        // GAME LOOP: LOAD INPUT
        this->loadInputFromTerminal();

        // GAME LOOP: MODIFY GAME STATE / RECALCULATE GAME STATE...
        //   ...by internal state
        if (this->constructionSite->isDominoSpawningSpotPopulatedWithFrozenDomino() ) {
            break;
        }

        if (this->constructionSite->isActiveDominoHidden() ) {
            this->constructionSite->makeActiveDominoVisible();
            continue;
        }

        //   ...by external input
        if (this->keyboardInputCharacters == "d") {
            this->constructionSite->moveActiveDominoDown();
            continue;
        }
        if (this->keyboardInputCharacters == "l") {
            this->constructionSite->moveActiveDominoLeft();
            continue;
        }
        if (this->keyboardInputCharacters == "r") {
            this->constructionSite->moveActiveDominoRight();
            continue;
        }
        if (this->keyboardInputCharacters == "c") {
            // TODO implement Domino rotation - clockwise, but the direction is irrelevant
            this->constructionSite->rotateActiveDominoCounterclockwise();
            continue;
        }
    }
    // WHILE LOOP - GAME LOOP - END
}

void Game::loadInputFromTerminal() {
    std::cout << "enter command(s): ";
    std::cin >> this->keyboardInputCharacters;
};

void Game::recalculateGameLogic() {
    // TODO recalculate game logic according to the user's input
    // if brick_1 is not visible
        // make it visible
        // return / switch to other state?
    // if brick_1 is visible
        // put it down
        // return / switch to other state?
    // if brick_1 is fallen
        // create a new brick_1/building block
        // return / switch to other state?
    // if there are consecutive lines in the ConstructionSite's playingField
        // remove them
        // rearrange the playingField by gravity
        // return / switch to other state?
}

//void Game::drawFrameOnTerminalForMonominos() const {
//    std::cout << constructionSite->getCurrentPlayingFieldOfMonominos() << std::flush;
//}

void Game::drawFrameOnTerminalForDominos() const {
    std::cout << constructionSite->getCurrentPlayingFieldOfDominos() << std::flush;
}

void Game::clearTerminal() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
