#include "Brick.h"
#include "ConstructionSite.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>

// TODO parametrize with args, i.e. "argv" and with constructor, and maybe add a setter to dynamically resize the playground during the game
// TODO manually enlarge the playingField in order to test multiple descends and/or input commands - preparation for testing in a while loop
ConstructionSite::ConstructionSite(uint_fast32_t rows, uint_fast32_t columns) :
        rows(rows),
        columns(columns),
        // TODO calculate middle Y-coordinate (horizontal center) for Brick + adjust constructor for that matter for Brick class
        activeBrick(std::make_unique<Brick>() )
{
    // TODO adjustPlaygroundDimensions() - check if at least one brick_1 fits in the playground: rows is greater or equal than 3; columns are greater or equal than 3

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

std::string ConstructionSite::getCurrentPlayingField() {
    if (this->activeBrick->isVisible()) {
        this->showActiveBrickOnPlayingField();
    }

    for (const auto& frozenBrick : this->frozenBricks ) {
        if (frozenBrick->isVisible() ) {
            showFrozenBrickOnPlayingField(*frozenBrick);
        }
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

void ConstructionSite::showActiveBrickOnPlayingField() {
    this->playingField
            .at(this->activeBrick->getRow())
            .at(this->activeBrick->getColumn())
            .assign(this->activeBrick->getBrickSign());
}

void ConstructionSite::showFrozenBrickOnPlayingField(const Brick& brick) {
    this->playingField
        .at(brick.getRow() )
        .at(brick.getColumn() )
        .assign(brick.getBrickSign() );
}

bool ConstructionSite::isBrickSpawningSpotPopulatedWithFrozenBrick() {
    for (const auto & frozenBrick : frozenBricks) {
        if (this->activeBrick->getRow() == frozenBrick->getRow() && this->activeBrick->getColumn() == frozenBrick->getColumn() ) {
            return true;
        }
    }
    return false;
}

bool ConstructionSite::isActiveBrickHidden() {
    return !(this->activeBrick->isVisible() );
}

void ConstructionSite::makeActiveBrickVisible() {
    this->activeBrick->makeVisible();
}

uint_fast32_t ConstructionSite::bottomRowIndexOfUsablePlayingArea() const {
    return this->rows - 2;
}

void ConstructionSite::moveActiveBrickDown() {
    bool hasFreeSpaceFromFloorOrOtherBricks = this->playingField
            .at(this->activeBrick->lookBelow() )
            .at(this->activeBrick->getColumn() ) == BLANK;

    if (hasFreeSpaceFromFloorOrOtherBricks) {
        this->playingField
            .at(this->activeBrick->getRow() )
            .at(this->activeBrick->getColumn() )
            .assign(BLANK);

        this->activeBrick->moveDown();
        return;
    }

    this->freezeActiveBrick();
    this->removeLastLineWhenFull();
    this->createNewActiveBrick();
}

void ConstructionSite::freezeActiveBrick() {
    this->frozenBricks.emplace_back(std::move(this->activeBrick) );
}

void ConstructionSite::createNewActiveBrick() {
    this->activeBrick = std::make_unique<Brick>();
}

void ConstructionSite::removeLastLineWhenFull() {
    for (int column = this->leftColumnIndexOfUsablePlayingArea(); column <= this->rightColumnIndexOfUsablePlayingArea(); ++column) {
        if (this->playingField.at(this->bottomRowIndexOfUsablePlayingArea() ).at(column) == BLANK) {
            return;
        }
    }

    // delete frozen bricks in the last row from frozen bricks and from the playingField
    this->frozenBricks.erase(
        std::remove_if(this->frozenBricks.begin(), this->frozenBricks.end(),
            [&](const auto & frozenBrick) {
                if (frozenBrick->getRow() == this->bottomRowIndexOfUsablePlayingArea() ) {
                    this->playingField
                        .at(frozenBrick->getRow())
                        .at(frozenBrick->getColumn())
                        .assign(BLANK);
                }

                return frozenBrick->getRow() == this->bottomRowIndexOfUsablePlayingArea();
            }),
        this->frozenBricks.end() );

    // move all remaining frozen brick one level down
    for (const auto& frozenBrick : this->frozenBricks) {
        this->playingField
            .at(frozenBrick->getRow())
            .at(frozenBrick->getColumn())
            .assign(BLANK);

        frozenBrick->moveDown();
    }
}

void ConstructionSite::moveActiveBrickLeft() {
    bool hasDistanceFromLeftWall = this->activeBrick->getColumn() > this->leftColumnIndexOfUsablePlayingArea();
    bool hasFreeSpaceOnLeftSide = this->playingField
            .at(this->activeBrick->getRow())
            .at(this->activeBrick->lookLeft() ) == BLANK;

    if (hasDistanceFromLeftWall && hasFreeSpaceOnLeftSide) {
        this->playingField
            .at(this->activeBrick->getRow())
            .at(this->activeBrick->getColumn())
            .assign(BLANK);

        this->activeBrick->moveLeft();
    }
}

void ConstructionSite::moveActiveBrickRight() {
    bool hasDistanceFromRightWall = this->activeBrick->getColumn() < this->rightColumnIndexOfUsablePlayingArea();
    bool hasFreeSpaceOnRightSide = this->playingField
            .at(this->activeBrick->getRow())
            .at(this->activeBrick->lookRight() ) == BLANK;

    if (hasDistanceFromRightWall && hasFreeSpaceOnRightSide) {
        this->playingField
                .at(this->activeBrick->getRow())
                .at(this->activeBrick->getColumn())
                .assign(BLANK);

        this->activeBrick->moveRight();
    }
}

uint_fast32_t ConstructionSite::leftColumnIndexOfUsablePlayingArea() const {
    return 1;
}

uint_fast32_t ConstructionSite::rightColumnIndexOfUsablePlayingArea() const {
    return this->columns - 2;
}
