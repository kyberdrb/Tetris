#pragma once

#include "Monomino.h"
#include "Domino.h"

#include <memory>
#include <string>
#include <vector>

class ConstructionSite {
public:
    ConstructionSite(uint_fast32_t rows, uint_fast32_t columns);

//    std::string getCurrentPlayingFieldOfMonominos();
    std::string getCurrentPlayingFieldOfDominos();

//    bool isMonominoSpawningSpotPopulatedWithFrozenMonomino();
    bool isDominoSpawningSpotPopulatedWithFrozenDomino();

//    bool isActiveMonominoHidden();
    bool isActiveDominoHidden();
//    void makeActiveMonominoVisible();
    void makeActiveDominoVisible();

//    void moveActiveMonominoDown();
    void moveActiveDominoDown();

//    void moveActiveMonominoLeft();
    void moveActiveDominoLeft();
//    void moveActiveMonominoRight();
    void moveActiveDominoRight();

//    void freezeActiveMonomino();
    void freezeActiveDomino();
//    void createNewActiveMonomino();
    void createNewActiveDomino();

private:
    uint_fast32_t rows;
    uint_fast32_t columns;

//    std::unique_ptr<Monomino> activeMonomino;
//    std::vector<std::unique_ptr<Monomino>> frozenMonominos;

    std::unique_ptr<Domino> activeDomino;
    std::vector<std::unique_ptr<Domino>> frozenDominos;

    std::vector<std::vector<std::string>> playingField;

    uint_fast32_t getNumberOfRows() const;
    uint_fast32_t getNumberOfColumns() const;
    uint_fast32_t bottomRowIndexOfUsablePlayingArea() const;
    uint_fast32_t leftColumnIndexOfUsablePlayingArea() const;
    uint_fast32_t rightColumnIndexOfUsablePlayingArea() const;

//    void showActiveMonominoOnPlayingField();
    void showActiveDominoOnPlayingField();
//    void showFrozenMonominoOnPlayingField(const Monomino& brick);
    void showFrozenDominoOnPlayingField(const Domino& brick);

//    void removeLastLineOfMonominosWhenFull();
    void removeLastLineOfDominosWhenFull();
};
