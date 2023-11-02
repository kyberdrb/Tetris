//
// Created by laptop on 9/19/23.
//

#pragma once

#include "Monomino.h"

#include <memory>
#include <vector>
#include <deque>

class Domino {
public:
    Domino();

    int_fast32_t getRowOfFirstMonomino() const;
    int_fast32_t getColumnOfFirstMonomino() const;

    int_fast32_t getRowOfSecondMonomino() const;
    int_fast32_t getColumnOfSecondMonomino() const;

    bool isVisible() const;
    bool isFirstMonominoVisible() const;
    bool isSecondMonominoVisible() const;
    void makeVisible();
    void hideFirstMonomino();
    void hideSecondMonomino();

    int_fast32_t lookBelowFirstMonomino() const;
    int_fast32_t lookBelowSecondMonomino() const;
    void moveDown();
    void moveFirstMonominoDown();
    void moveSecondMonominoDown();

    int_fast32_t lookLeft() const;
    void moveLeft();

    int_fast32_t lookRight() const;
    void moveRight();

    int_fast32_t lookUp() const;

    void rotateClockwise();
    std::vector<std::pair<int_fast32_t, int_fast32_t>> lookAroundFirstMonomino() const;
    void clearOrthogonallyAdjacentNeighboursToFirstMonomino();
    void addRotationCoordinate(std::pair<int_fast32_t, int_fast32_t> coordinates);
    void nextClockwiseRotationPosition();
    void adjustRotationCoordinatesOrderByCurrentOrientation();

    bool isVertical() const;

private:
    std::unique_ptr<Monomino> firstMonomino;
    std::unique_ptr<Monomino> secondMonomino;
    std::deque<std::pair<int_fast32_t, int_fast32_t>> freeOrthogonalNeighboursForFirstMonomino; // TODO store instances of 'std::unique_ptr<Coordinates>' , instead of std::pair elements

    void moveFrontOrthogonalNeighbourToBack();
};
