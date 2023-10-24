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

    int_fast32_t lookBelow() const;
    void moveDown();

    int_fast32_t lookLeft() const;
    void moveLeft();

    int_fast32_t lookRight() const;
    void moveRight();

    // TODO implement rotation

private:
    std::unique_ptr<Monomino> firstMonomino;
    std::unique_ptr<Monomino> secondMonomino;
};
