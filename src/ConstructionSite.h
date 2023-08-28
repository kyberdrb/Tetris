#pragma once

#include "Brick.h"

#include <memory>
#include <string>
#include <vector>

class ConstructionSite {
public:
    ConstructionSite(uint_fast32_t rows, uint_fast32_t columns);

    uint_fast32_t getNumberOfRows() const;
    uint_fast32_t getNumberOfColumns() const;

    std::string getCurrentPlayingField();

    bool isBrickSpawningSpotPopulatedWithFrozenBrick();

    bool isActiveBrickHidden();
    void makeActiveBrickVisible();

    void moveActiveBrickDown();

    void moveActiveBrickLeft();
    void moveActiveBrickRight();

    void freezeActiveBrick();
    void createNewActiveBrick();

private:
    uint_fast32_t rows;
    uint_fast32_t columns;

    std::unique_ptr<Brick> activeBrick;
    std::vector<std::unique_ptr<Brick>> frozenBricks;

    std::vector<std::vector<std::string>> playingField;

    const std::string FLOOR = "`"; // BACKTICK
    const std::string WALL = "|"; // PIPE
    const std::string BLANK = " "; // SPACE

    void showActiveBrickOnPlayingField();
    void showFrozenBrickOnPlayingField(const Brick& brick);

    uint_fast32_t bottomRowIndexOfUsablePlayingArea() const;
    uint_fast32_t leftColumnIndexOfUsablePlayingArea() const;
    uint_fast32_t rightColumnIndexOfUsablePlayingArea() const;

    void removeLastLineWhenFull();
};
