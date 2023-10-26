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
//        activeMonomino(std::make_unique<Monomino>() )
        activeDomino(std::make_unique<Domino>() )
{
    // TODO adjustPlaygroundDimensions()
    //  - check if at least one brick_1 fits in the playground: rows is greater or equal than 3; columns are greater or equal than 3 in 5x6 playing field

    reserveCapacity();
    initializePlayingFieldBoundaries();
}

void ConstructionSite::reserveCapacity() {
    playingField.resize(rows);
    for (auto& row : playingField) {
        row.resize(columns);
    }
}

void ConstructionSite::initializePlayingFieldBoundaries() {
    uint_fast32_t forelastRowIndex = bottomRowIndexOfUsablePlayingArea();
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

//std::string ConstructionSite::getCurrentPlayingFieldOfMonominos() {
//    if (this->activeMonomino->isVisible()) {
//        this->showActiveMonominoOnPlayingField();
//    }
//
//    for (const auto& frozenMonomino : this->frozenMonominos ) {
//        if (frozenMonomino->isVisible() ) {
//            showFrozenMonominoOnPlayingField(*frozenMonomino);
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

std::string ConstructionSite::getCurrentPlayingFieldOfDominos() {
    if (this->activeDomino->isVisible()) {
        this->showActiveDominoOnPlayingField();
    }

    for (const auto& frozenDomino : this->frozenDominos ) {
        showFrozenDominoOnPlayingField(*frozenDomino);
    }

    std::stringstream buffer;
    for (const auto& row : playingField) {
        for (const auto& column : row) {
            buffer << column;
        }
        buffer << "\n";
    }
    return buffer.str();
}

//void ConstructionSite::showActiveMonominoOnPlayingField() {
//    this->playingField
//            .at(this->activeMonomino->getRowOfFirstMonomino())
//            .at(this->activeMonomino->getColumnOfFirstMonomino())
//            .assign(BRICK);
//}

void ConstructionSite::showActiveDominoOnPlayingField() {
    this->playingField
        .at(this->activeDomino->getRowOfFirstMonomino())
        .at(this->activeDomino->getColumnOfFirstMonomino())
        .assign(BRICK);

    this->playingField
        .at(this->activeDomino->getRowOfSecondMonomino())
        .at(this->activeDomino->getColumnOfSecondMonomino())
        .assign(BRICK);
}

//void ConstructionSite::showFrozenMonominoOnPlayingField(const Monomino& brick) {
//    this->playingField
//        .at(brick.getRowOfFirstMonomino() )
//        .at(brick.getColumnOfFirstMonomino() )
//        .assign(BRICK);
//}

void ConstructionSite::showFrozenDominoOnPlayingField(const Domino& domino) {
    if (domino.isVisible() ) {
        this->playingField
            .at(domino.getRowOfFirstMonomino())
            .at(domino.getColumnOfFirstMonomino())
            .assign(BRICK);
    }

    if (domino.isVisible() ) {
        this->playingField
            .at(domino.getRowOfSecondMonomino())
            .at(domino.getColumnOfSecondMonomino())
            .assign(BRICK);
    }
}

//bool ConstructionSite::isMonominoSpawningSpotPopulatedWithFrozenMonomino() {
//    for (const auto & frozenMonomino : frozenMonominos) {
//        if (this->activeMonomino->getRowOfFirstMonomino() == frozenMonomino->getRow() && this->activeMonomino->getColumn() == frozenMonomino->getColumnOfFirstMonomino() ) {
//            return true;
//        }
//    }
//    return false;
//}

bool ConstructionSite::isDominoSpawningSpotPopulatedWithFrozenDomino() {
    for (const auto & frozenDomino : frozenDominos) {
        bool isFirstMonominoOfDominoCollidingWithFrozenDomino =
            (this->activeDomino->getRowOfFirstMonomino() == frozenDomino->getRowOfFirstMonomino() &&
             this->activeDomino->getColumnOfFirstMonomino() == frozenDomino->getColumnOfFirstMonomino() )
            ||
            (this->activeDomino->getRowOfFirstMonomino() == frozenDomino->getRowOfSecondMonomino() &&
             this->activeDomino->getColumnOfFirstMonomino() == frozenDomino->getColumnOfSecondMonomino() );
        
        bool isSecondMonominoOfDominoCollidingWithFrozenDomino =
            (this->activeDomino->getRowOfSecondMonomino() == frozenDomino->getRowOfSecondMonomino() &&
             this->activeDomino->getColumnOfSecondMonomino() == frozenDomino->getColumnOfSecondMonomino() )
             ||
            (this->activeDomino->getRowOfSecondMonomino() == frozenDomino->getRowOfFirstMonomino() &&
             this->activeDomino->getColumnOfSecondMonomino() == frozenDomino->getColumnOfFirstMonomino() );

        bool isActiveDominoCollidingWithFrozenDomino =
            isFirstMonominoOfDominoCollidingWithFrozenDomino || isSecondMonominoOfDominoCollidingWithFrozenDomino;

        if (isActiveDominoCollidingWithFrozenDomino) {
            return true;
        }
    }
    return false;
}

//bool ConstructionSite::isActiveMonominoHidden() {
//    return !(this->activeMonomino->isVisible() );
//}

bool ConstructionSite::isActiveDominoHidden() {
    return !(this->activeDomino->isVisible() );
}

//void ConstructionSite::makeActiveMonominoVisible() {
//    this->activeMonomino->makeVisible();
//}

void ConstructionSite::makeActiveDominoVisible() {
    this->activeDomino->makeVisible();
}

//void ConstructionSite::moveActiveMonominoDown() {
//    bool hasFreeSpaceFromFloorOrOtherMonominos = this->playingField
//            .at(this->activeMonomino->lookBelowFirstMonomino() )
//            .at(this->activeMonomino->getColumnOfFirstMonomino() ) == BLANK;
//
//    if (hasFreeSpaceFromFloorOrOtherMonominos) {
//        this->playingField
//            .at(this->activeMonomino->getRowOfFirstMonomino() )
//            .at(this->activeMonomino->getColumnOfFirstMonomino() )
//            .assign(BLANK);
//
//        this->activeMonomino->moveDown();
//        return;
//    }
//
//    this->freezeActiveMonomino();
//    this->removeLastLineOfMonominosWhenFull();
//    this->createNewActiveMonomino();
//}

void ConstructionSite::moveActiveDominoDown() {
    bool hasFirstMonominoFreeSpaceFromFloorOrOtherMonominos =
        this->playingField
            .at(this->activeDomino->lookBelowFirstMonomino() )
            .at(this->activeDomino->getColumnOfFirstMonomino() ) == BLANK;

    bool hasSecondMonominoFreeSpaceFromFloorOrOtherMonominos =
        this->playingField
            .at(this->activeDomino->lookBelowSecondMonomino() )
            .at(this->activeDomino->getColumnOfSecondMonomino() ) == BLANK;

    bool hasFreeSpaceFromFloorOrOtherMonominos =
        hasFirstMonominoFreeSpaceFromFloorOrOtherMonominos && hasSecondMonominoFreeSpaceFromFloorOrOtherMonominos;

    if (this->activeDomino->isVertical() ) {
        hasFreeSpaceFromFloorOrOtherMonominos =
            hasFirstMonominoFreeSpaceFromFloorOrOtherMonominos || hasSecondMonominoFreeSpaceFromFloorOrOtherMonominos;
    }

    if (hasFreeSpaceFromFloorOrOtherMonominos) {
        this->playingField
            .at(this->activeDomino->getRowOfFirstMonomino())
            .at(this->activeDomino->getColumnOfFirstMonomino())
            .assign(BLANK);

        this->playingField
            .at(this->activeDomino->getRowOfSecondMonomino())
            .at(this->activeDomino->getColumnOfSecondMonomino())
            .assign(BLANK);

        this->activeDomino->moveDown();
        return;
    }

    this->freezeActiveDomino();
    this->removeLastLineOfDominosWhenFull();
    this->createNewActiveDomino();
}

void ConstructionSite::rotateActiveDominoCounterclockwise() {
    // Clear previous position of second monomino
    this->playingField
            .at(this->activeDomino->getRowOfSecondMonomino())
            .at(this->activeDomino->getColumnOfSecondMonomino())
            .assign(BLANK);

    this->activeDomino->rotateClockwise();
}

//void ConstructionSite::freezeActiveMonomino() {
//    this->frozenMonominos.emplace_back(std::move(this->activeMonomino) );
//}

void ConstructionSite::freezeActiveDomino() {
    this->frozenDominos.emplace_back(std::move(this->activeDomino) );
}

//void ConstructionSite::createNewActiveMonomino() {
//    this->activeMonomino = std::make_unique<Monomino>();
//}

void ConstructionSite::createNewActiveDomino() {
    this->activeDomino = std::make_unique<Domino>();
}

//void ConstructionSite::removeLastLineOfMonominosWhenFull() {
//    for (int column = this->leftColumnIndexOfUsablePlayingArea(); column <= this->rightColumnIndexOfUsablePlayingArea(); ++column) {
//        if (this->playingField.at(this->bottomRowIndexOfUsablePlayingArea() ).at(column) == BLANK) {
//            return;
//        }
//    }
//
//    // delete frozen bricks in the last row from frozen bricks and from the playingField
//    this->frozenMonominos.erase(
//        std::remove_if(this->frozenMonominos.begin(), this->frozenMonominos.end(),
//            [&](const auto & frozenMonomino) {
//                if (frozenMonomino->getRowOfFirstMonomino() == this->bottomRowIndexOfUsablePlayingArea() ) {
//                    this->playingField
//                        .at(frozenMonomino->getRowOfFirstMonomino())
//                        .at(frozenMonomino->getColumnOfFirstMonomino())
//                        .assign(BLANK);
//                }
//
//                return frozenMonomino->getRowOfFirstMonomino() == this->bottomRowIndexOfUsablePlayingArea();
//            }),
//        this->frozenMonominos.end() );
//
//    // move all remaining frozen brick one level down
//    for (const auto& frozenMonomino : this->frozenMonominos) {
//        this->playingField
//            .at(frozenMonomino->getRowOfFirstMonomino())
//            .at(frozenMonomino->getColumnOfFirstMonomino())
//            .assign(BLANK);
//
//        frozenMonomino->moveDown();
//    }
//}

void ConstructionSite::removeLastLineOfDominosWhenFull() {
    // TODO implement deletion of multiple full rows at once
//    std::vector<uint_fast32_t> fullRowsIndexesInUsablePlayingArea;

    // TODO extend logic for vertical Domino
    //  implement deletion of a Monomino in a Domino which is in a full row - partial Domino deletion
    // find the full row
    uint_fast32_t fullRowIndex = 0;
    bool areRowsPartiallyFull = true;
    for (uint_fast32_t rowInUsablePlayingArea = 0; rowInUsablePlayingArea <= this->bottomRowIndexOfUsablePlayingArea(); ++rowInUsablePlayingArea) {
        const bool isRowFull = this->isRowFull(this->playingField.at(rowInUsablePlayingArea));

        if (isRowFull) {
            fullRowIndex = rowInUsablePlayingArea;
            areRowsPartiallyFull = false;
            break;
        }
    }

    if (areRowsPartiallyFull) {
        return;
    }

    // TODO **delete** all horizontal Dominoes in the full row:
    //  erase + remove_if , i. e. restore previous code, but as a removal condition use:
    //    frozenDomino->getRowOfFirstMonomino() == frozenDomino->getRowOfSecondMonomino()
    //  Then wrap it to a Domino member function 'bool isHorizontal()'
    // delete all horizontal Dominoes in the full row
    this->frozenDominos.erase(
        std::remove_if(this->frozenDominos.begin(), this->frozenDominos.end(),
            [&](const auto & frozenDomino) {
                if (frozenDomino->getRowOfFirstMonomino() == fullRowIndex ) {
                    this->playingField
                        .at(frozenDomino->getRowOfFirstMonomino())
                        .at(frozenDomino->getColumnOfFirstMonomino())
                        .assign(BLANK);

                    this->playingField
                        .at(frozenDomino->getRowOfSecondMonomino())
                        .at(frozenDomino->getColumnOfSecondMonomino())
                        .assign(BLANK);
                }

                return (frozenDomino->getRowOfFirstMonomino() == fullRowIndex) && (frozenDomino->getRowOfSecondMonomino() == fullRowIndex);
            }),
            this->frozenDominos.end() );

    // TODO **hide** Monominos of the Domino when at least one of its Monominos is a part of the full row - partial hiding/deletion
    for (const auto& frozenDomino : this->frozenDominos) {
        if (frozenDomino->getRowOfFirstMonomino() == fullRowIndex) {
            this->playingField
                .at(frozenDomino->getRowOfFirstMonomino())
                .at(frozenDomino->getColumnOfFirstMonomino())
                .assign(BLANK);

            frozenDomino->hideFirstMonomino();
        }

        if (frozenDomino->getRowOfSecondMonomino() == fullRowIndex) {
            this->playingField
                .at(frozenDomino->getRowOfSecondMonomino())
                .at(frozenDomino->getColumnOfSecondMonomino())
                .assign(BLANK);

            frozenDomino->hideSecondMonomino();
        }
    }

    // push Dominos down
    // TODO let only those Monominos of the Domino fall, which are hidden/not visible - check visibility too?
    for (const auto & frozenDomino : this->frozenDominos) {
        if (frozenDomino->getRowOfFirstMonomino() < fullRowIndex) {
            // TODO implement function
            //   then combine the two if statements into one compount condition
//            if (frozenDomino->isFirstMonominoVisible() ) {
                this->playingField
                        .at(frozenDomino->getRowOfFirstMonomino())
                        .at(frozenDomino->getColumnOfFirstMonomino())
                        .assign(BLANK);

                // TODO implement function
//                frozenDomino->moveFirstMonominoDown();
//            }

        if (frozenDomino->getRowOfSecondMonomino() < fullRowIndex) {
            // TODO implement function
            //   then combine the two if statements into one compount condition
//            if (frozenDomino->isSecondMonominoVisible() ) {
                this->playingField
                        .at(frozenDomino->getRowOfSecondMonomino())
                        .at(frozenDomino->getColumnOfSecondMonomino())
                        .assign(BLANK);

                // TODO implement function
//                frozenDomino->moveSecondMonominoDown();
//            }
        }

            // TODO Split to two functions 'moveDownFirstMonomino' and 'moveDownSecondMonomino'?
            //  move only when visible? i.e. allow overlapping Monominos in a Domino?
            //frozenDomino->moveDown();
        }
    }
}

uint_fast32_t ConstructionSite::bottomRowIndexOfUsablePlayingArea() const {
    return this->rows - 2;
}

bool ConstructionSite::isRowFull(std::vector<std::string>& row) const {
    for (   uint_fast32_t column = this->leftColumnIndexOfUsablePlayingArea();
            column <= this->rightColumnIndexOfUsablePlayingArea();
            ++column)
    {
        std::string signInRow = row.at(column);

        if (signInRow == BLANK) {
            return false;
        }
    }
    return true;
}

//void ConstructionSite::moveActiveMonominoLeft() {
//    bool hasDistanceFromLeftWall = this->activeMonomino->getColumnOfFirstMonomino() > this->leftColumnIndexOfUsablePlayingArea();
//    bool hasFreeSpaceOnLeftSide = this->playingField
//            .at(this->activeMonomino->getRowOfFirstMonomino())
//            .at(this->activeMonomino->lookLeft() ) == BLANK;
//
//    if (hasDistanceFromLeftWall && hasFreeSpaceOnLeftSide) {
//        this->playingField
//            .at(this->activeMonomino->getRowOfFirstMonomino())
//            .at(this->activeMonomino->getColumnOfFirstMonomino())
//            .assign(BLANK);
//
//        this->activeMonomino->moveLeft();
//    }
//}

void ConstructionSite::moveActiveDominoLeft() {
    bool hasDistanceFromLeftWall =
        (this->activeDomino->getColumnOfFirstMonomino() > this->leftColumnIndexOfUsablePlayingArea() ) ||
        (this->activeDomino->getColumnOfSecondMonomino() > this->leftColumnIndexOfUsablePlayingArea() );

    if (this->activeDomino->isVertical() ) {
        hasDistanceFromLeftWall =
            (this->activeDomino->getColumnOfFirstMonomino() > this->leftColumnIndexOfUsablePlayingArea() ) &&
            (this->activeDomino->getColumnOfSecondMonomino() > this->leftColumnIndexOfUsablePlayingArea() );
    }

    bool hasFreeSpaceOnLeftSide =
        (this->playingField
            .at(this->activeDomino->getRowOfFirstMonomino())
            .at(this->activeDomino->lookLeft() ) == BLANK)
        ||
        (this->playingField
             .at(this->activeDomino->getRowOfSecondMonomino())
             .at(this->activeDomino->lookLeft() ) == BLANK);

    if (this->activeDomino->isVertical() ) {
        hasFreeSpaceOnLeftSide =
            (this->playingField
                .at(this->activeDomino->getRowOfFirstMonomino())
                .at(this->activeDomino->lookLeft() ) == BLANK)
            &&
            (this->playingField
                 .at(this->activeDomino->getRowOfSecondMonomino())
                 .at(this->activeDomino->lookLeft() ) == BLANK);
    }

    if (hasDistanceFromLeftWall && hasFreeSpaceOnLeftSide) {
        this->playingField
            .at(this->activeDomino->getRowOfFirstMonomino())
            .at(this->activeDomino->getColumnOfFirstMonomino())
            .assign(BLANK);

        this->playingField
            .at(this->activeDomino->getRowOfSecondMonomino())
            .at(this->activeDomino->getColumnOfSecondMonomino())
            .assign(BLANK);

        this->activeDomino->moveLeft();
    }
}

//void ConstructionSite::moveActiveMonominoRight() {
//    bool hasDistanceFromRightWall = this->activeMonomino->getColumnOfFirstMonomino() < this->rightColumnIndexOfUsablePlayingArea();
//    bool hasFreeSpaceOnRightSide = this->playingField
//            .at(this->activeMonomino->getRowOfFirstMonomino())
//            .at(this->activeMonomino->lookRight() ) == BLANK;
//
//    if (hasDistanceFromRightWall && hasFreeSpaceOnRightSide) {
//        this->playingField
//                .at(this->activeMonomino->getRowOfFirstMonomino())
//                .at(this->activeMonomino->getColumnOfFirstMonomino())
//                .assign(BLANK);
//
//        this->activeMonomino->moveRight();
//    }
//}

void ConstructionSite::moveActiveDominoRight() {
    bool hasDistanceFromRightWall =
        (this->activeDomino->getColumnOfFirstMonomino() < this->rightColumnIndexOfUsablePlayingArea() ) ||
        (this->activeDomino->getColumnOfSecondMonomino() < this->rightColumnIndexOfUsablePlayingArea() );

    bool hasFreeSpaceOnRightSide =
        (this->playingField
             .at(this->activeDomino->getRowOfFirstMonomino())
             .at(this->activeDomino->lookRight()) == BLANK)
        ||
        (this->playingField
            .at(this->activeDomino->getRowOfSecondMonomino())
            .at(this->activeDomino->lookRight()) == BLANK);

    if (hasDistanceFromRightWall && hasFreeSpaceOnRightSide) {
        this->playingField
                .at(this->activeDomino->getRowOfFirstMonomino())
                .at(this->activeDomino->getColumnOfFirstMonomino())
                .assign(BLANK);

        this->playingField
                .at(this->activeDomino->getRowOfSecondMonomino())
                .at(this->activeDomino->getColumnOfSecondMonomino())
                .assign(BLANK);

        this->activeDomino->moveRight();
    }
}

uint_fast32_t ConstructionSite::leftColumnIndexOfUsablePlayingArea() const {
    return 1;
}

uint_fast32_t ConstructionSite::rightColumnIndexOfUsablePlayingArea() const {
    return this->columns - 2;
}

uint_fast32_t ConstructionSite::getNumberOfRows() const {
    return this->rows;
}

uint_fast32_t ConstructionSite::getNumberOfColumns() const {
    return this->columns;
}
