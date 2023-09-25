//
// Created by laptop on 9/19/23.
//

#pragma once

#include "Monomino.h"

#include <memory>

class Domino {
public:
    Domino();

    int_fast32_t getRow() const;
    int_fast32_t getColumn() const;

    bool isVisible() const;
    void makeVisible();

    int_fast32_t lookBelow() const;
    void moveDown();

    int_fast32_t lookLeft() const;
    void moveLeft();

    int_fast32_t lookRight() const;
    void moveRight();

private:
    std::unique_ptr<Monomino> firstMonomino;
    std::unique_ptr<Monomino> secondMonomino;
};