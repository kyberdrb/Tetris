#pragma once

#include "Monomino.h"

#include <memory>
#include <string>
#include <vector>

class ConstructionSite {
public:
    ConstructionSite(uint_fast32_t rows, uint_fast32_t columns);

    uint_fast32_t getNumberOfRows() const;
    uint_fast32_t getNumberOfColumns() const;

    std::string getCurrentPlayingField();

    bool isMonominoSpawningSpotPopulatedWithFrozenMonomino();

    bool isActiveMonominoHidden();
    void makeActiveMonominoVisible();

    void moveActiveMonominoDown();

    void moveActiveMonominoLeft();
    void moveActiveMonominoRight();

    void freezeActiveMonomino();
    void createNewActiveMonomino();

private:
    uint_fast32_t rows;
    uint_fast32_t columns;

    std::unique_ptr<Monomino> activeMonomino;
    std::vector<std::unique_ptr<Monomino>> frozenMonominos;

    std::vector<std::vector<std::string>> playingField;

    const std::string FLOOR = "`"; // BACKTICK
    const std::string WALL = "|"; // PIPE
    const std::string BLANK = " "; // SPACE

    void showActiveMonominoOnPlayingField();
    void showFrozenMonominoOnPlayingField(const Monomino& brick);

    uint_fast32_t bottomRowIndexOfUsablePlayingArea() const;
    uint_fast32_t leftColumnIndexOfUsablePlayingArea() const;
    uint_fast32_t rightColumnIndexOfUsablePlayingArea() const;

    void removeLastLineWhenFull();
};
