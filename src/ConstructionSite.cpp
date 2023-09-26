#include "Monomino.h"
#include "ConstructionSite.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>

const std::string FLOOR = "`"; // BACKTICK
const std::string WALL = "|"; // PIPE
const std::string BLANK = " "; // SPACE

const std::string BRICK = "#";  // HASHTAG/POUNDSIGN
                                // '■' - BLACK SQUARE - u9632
                                // '⎕ - Apl Functional Symbol Quad'
                                // '□ - White Square'
                                // '⌷ - Apl Functional Symbol Squish Quad'

// TODO parametrize with args, i.e. "argv" and with constructor, and maybe add a setter to dynamically resize the playground during the game
// TODO manually enlarge the playingField in order to test multiple descends and/or input commands - preparation for testing in a while loop
ConstructionSite::ConstructionSite(uint_fast32_t rows, uint_fast32_t columns) :
        rows(rows),
        columns(columns),
        // TODO calculate middle Y-coordinate (horizontal center) for Monomino + adjust constructor for that matter for Monomino class
        activeMonomino(std::make_unique<Monomino>() )
//        activeDomino(std::make_unique<Domino>() )
{
    // TODO adjustPlaygroundDimensions()
    //  - check if at least one brick_1 fits in the playground: rows is greater or equal than 3; columns are greater or equal than 3

    // TODO encapsulate to function reserveCapacity()
    playingField.resize(rows);
    for (auto& row : playingField) {
        row.resize(columns);
    }

    //TODO encapsulate to function initializePlayingField()
    uint_fast32_t forelastRowIndex = this->bottomRowIndexOfUsablePlayingArea();
    for (uint_fast32_t row = 0; row <= forelastRowIndex; ++row) {
        for (uint_fast32_t column = 0; column < columns; ++column) {
            // check first and forelast column - fill them with WALL character
            // TODO encapsulate condition to 'bool isSideBorder = isLeftBorder || isRightBorder;
            bool isLeftBorder = column == 0;
            bool isRightBorder = column == columns - 1;
            bool isSideBorder = isLeftBorder || isRightBorder;
            if (isSideBorder) {
                playingField.at(row).at(column) = WALL;
                continue;
            }

            //fill the rest with BLANK character
            playingField.at(row).at(column) = BLANK;
        }
    }

    //iterate the last line in a separate loop - fill it with FLOOR character
    uint_fast32_t lastRowIndex = rows - 1;
    auto& lastRow = playingField.at(lastRowIndex);
    for (int column = 0; column < columns; ++column) {
        lastRow.at(column).assign(FLOOR);
    }
}

uint_fast32_t ConstructionSite::getNumberOfRows() const {
    return this->rows;
}
uint_fast32_t ConstructionSite::getNumberOfColumns() const {
    return this->columns;
}

std::string ConstructionSite::getCurrentPlayingFieldOfMonominos() {
    if (this->activeMonomino->isVisible()) {
        this->showActiveMonominoOnPlayingField();
    }
//    if (this->activeDomino->isVisible()) {
//        this->showActiveDominoOnPlayingField();
//    }

    for (const auto& frozenMonomino : this->frozenMonominos ) {
        if (frozenMonomino->isVisible() ) {
            showFrozenMonominoOnPlayingField(*frozenMonomino);
        }
    }
//    for (const auto& frozenDomino : this->frozenDominos ) {
//        if (frozenDomino->isVisible() ) {
//            showFrozenDominoOnPlayingField(*frozenDomino);
//        }
//    }

    std::stringstream buffer;
    for (const auto& row : playingField) {
        for (const auto& column : row) {
            buffer << column;
        }
        buffer << "\n";
    }
    return buffer.str();
}

//std::string ConstructionSite::getCurrentPlayingFieldOfDominos() {
//    if (this->activeDomino->isVisible()) {
//        this->showActiveDominoOnPlayingField();
//    }
//
//    for (const auto& frozenDomino : this->frozenDominos ) {
//        if (frozenDomino->isVisible() ) {
//            showFrozenDominoOnPlayingField(*frozenDomino);
//        }
//    }
//
//    std::stringstream buffer;
//    for (const auto& row : playingField) {
//        for (const auto& column : row) {
//            buffer << column;
//        }
//        buffer << "\n";
//    }
//    return buffer.str();
//}

void ConstructionSite::showActiveMonominoOnPlayingField() {
    this->playingField
            .at(this->activeMonomino->getRow())
            .at(this->activeMonomino->getColumn())
            .assign(BRICK);
}

//void ConstructionSite::showActiveDominoOnPlayingField() {
//
//}

void ConstructionSite::showFrozenMonominoOnPlayingField(const Monomino& brick) {
    this->playingField
        .at(brick.getRow() )
        .at(brick.getColumn() )
        .assign(BRICK);
}

//void ConstructionSite::showFrozenDominoOnPlayingField(const Domino& brick) {
//
//}

bool ConstructionSite::isMonominoSpawningSpotPopulatedWithFrozenMonomino() {
    for (const auto & frozenMonomino : frozenMonominos) {
        if (this->activeMonomino->getRow() == frozenMonomino->getRow() && this->activeMonomino->getColumn() == frozenMonomino->getColumn() ) {
            return true;
        }
    }
    return false;
}

//bool ConstructionSite::isDominoSpawningSpotPopulatedWithFrozenDomino() {
//    for (const auto& frozenDomino : frozenDominos) {
//        if (this->activeDomino->getRow() == frozenDomino->getRow() && this->activeDomino->getColumn() == frozenDomino->getColumn() ) {
//            return true;
//        }
//    }
//    return false;
//}

bool ConstructionSite::isActiveMonominoHidden() {
    return !(this->activeMonomino->isVisible() );
}

//bool ConstructionSite::isActiveDominoHidden() {
//    return !(this->activeDomino->isVisible() );
//}

void ConstructionSite::makeActiveMonominoVisible() {
    this->activeMonomino->makeVisible();
}

//void ConstructionSite::makeActiveDominoVisible() {
//    this->activeDomino->makeVisible();
//}

uint_fast32_t ConstructionSite::bottomRowIndexOfUsablePlayingArea() const {
    return this->rows - 2;
}

void ConstructionSite::moveActiveMonominoDown() {
    bool hasFreeSpaceFromFloorOrOtherMonominos = this->playingField
            .at(this->activeMonomino->lookBelow() )
            .at(this->activeMonomino->getColumn() ) == BLANK;

    if (hasFreeSpaceFromFloorOrOtherMonominos) {
        this->playingField
            .at(this->activeMonomino->getRow() )
            .at(this->activeMonomino->getColumn() )
            .assign(BLANK);

        this->activeMonomino->moveDown();
        return;
    }

    this->freezeActiveMonomino();
    this->removeLastLineOfMonominosWhenFull();
    this->createNewActiveMonomino();
}

//void ConstructionSite::moveActiveDominoDown() {
//
//}

void ConstructionSite::freezeActiveMonomino() {
    this->frozenMonominos.emplace_back(std::move(this->activeMonomino) );
}

//void ConstructionSite::freezeActiveDomino() {
//    this->frozenDominos.emplace_back(std::move(this->activeDomino) );
//}

void ConstructionSite::createNewActiveMonomino() {
    this->activeMonomino = std::make_unique<Monomino>();
}

//void ConstructionSite::createNewActiveDomino() {
//    this->activeDomino = std::make_unique<Domino>();
//}

void ConstructionSite::removeLastLineOfMonominosWhenFull() {
    for (int column = this->leftColumnIndexOfUsablePlayingArea(); column <= this->rightColumnIndexOfUsablePlayingArea(); ++column) {
        if (this->playingField.at(this->bottomRowIndexOfUsablePlayingArea() ).at(column) == BLANK) {
            return;
        }
    }

    // delete frozen bricks in the last row from frozen bricks and from the playingField
    this->frozenMonominos.erase(
        std::remove_if(this->frozenMonominos.begin(), this->frozenMonominos.end(),
            [&](const auto & frozenMonomino) {
                if (frozenMonomino->getRow() == this->bottomRowIndexOfUsablePlayingArea() ) {
                    this->playingField
                        .at(frozenMonomino->getRow())
                        .at(frozenMonomino->getColumn())
                        .assign(BLANK);
                }

                return frozenMonomino->getRow() == this->bottomRowIndexOfUsablePlayingArea();
            }),
        this->frozenMonominos.end() );

    // move all remaining frozen brick one level down
    for (const auto& frozenMonomino : this->frozenMonominos) {
        this->playingField
            .at(frozenMonomino->getRow())
            .at(frozenMonomino->getColumn())
            .assign(BLANK);

        frozenMonomino->moveDown();
    }
}

//void ConstructionSite::removeLastLineOfDominosWhenFull() {
//
//}

void ConstructionSite::moveActiveMonominoLeft() {
    bool hasDistanceFromLeftWall = this->activeMonomino->getColumn() > this->leftColumnIndexOfUsablePlayingArea();
    bool hasFreeSpaceOnLeftSide = this->playingField
            .at(this->activeMonomino->getRow())
            .at(this->activeMonomino->lookLeft() ) == BLANK;

    if (hasDistanceFromLeftWall && hasFreeSpaceOnLeftSide) {
        this->playingField
            .at(this->activeMonomino->getRow())
            .at(this->activeMonomino->getColumn())
            .assign(BLANK);

        this->activeMonomino->moveLeft();
    }
}

//void ConstructionSite::moveActiveDominoLeft() {
//
//}

void ConstructionSite::moveActiveMonominoRight() {
    bool hasDistanceFromRightWall = this->activeMonomino->getColumn() < this->rightColumnIndexOfUsablePlayingArea();
    bool hasFreeSpaceOnRightSide = this->playingField
            .at(this->activeMonomino->getRow())
            .at(this->activeMonomino->lookRight() ) == BLANK;

    if (hasDistanceFromRightWall && hasFreeSpaceOnRightSide) {
        this->playingField
                .at(this->activeMonomino->getRow())
                .at(this->activeMonomino->getColumn())
                .assign(BLANK);

        this->activeMonomino->moveRight();
    }
}

//void ConstructionSite::moveActiveDominoRight() {
//
//}

uint_fast32_t ConstructionSite::leftColumnIndexOfUsablePlayingArea() const {
    return 1;
}

uint_fast32_t ConstructionSite::rightColumnIndexOfUsablePlayingArea() const {
    return this->columns - 2;
}
