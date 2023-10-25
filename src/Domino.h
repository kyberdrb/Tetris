//
// Created by laptop on 9/19/23.
//

#pragma once

#include "Monomino.h"

#include <memory>

class Domino {
public:
    Domino();

    int_fast32_t getRowOfFirstMonomino() const;
    int_fast32_t getColumnOfFirstMonomino() const;

    int_fast32_t getRowOfSecondMonomino() const;
    int_fast32_t getColumnOfSecondMonomino() const;

    bool isVisible() const;
    void makeVisible();
    void hideFirstMonomino();
    void hideSecondMonomino();

    int_fast32_t lookBelowFirstMonomino() const;
    int_fast32_t lookBelowSecondMonomino() const;
    void moveDown();

    int_fast32_t lookLeft() const;
    void moveLeft();

    int_fast32_t lookRight() const;
    void moveRight();

    void rotateClockwise();
    bool isVertical() const;

private:
    std::unique_ptr<Monomino> firstMonomino;
    std::unique_ptr<Monomino> secondMonomino;
};
