//
// Created by laptop on 9/19/23.
//

#include "Domino.h"

Domino::Domino() :
    firstMonomino(std::make_unique<Monomino>()),
    secondMonomino(std::make_unique<Monomino>())
{
    this->secondMonomino->moveRight();
}

int_fast32_t Domino::getRowOfFirstMonomino() const {
    return this->firstMonomino->getRow();
}
int_fast32_t Domino::getColumnOfFirstMonomino() const {
    return this->firstMonomino->getColumn();
}

int_fast32_t Domino::getRowOfSecondMonomino() const {
    return this->secondMonomino->getRow();
}
int_fast32_t Domino::getColumnOfSecondMonomino() const {
    return this->secondMonomino->getColumn();
}

bool Domino::isVisible() const {
    bool areBothMonominosVisible = this->firstMonomino->isVisible() && this->secondMonomino->isVisible();
    return areBothMonominosVisible;
}

void Domino::makeVisible() {
    this->firstMonomino->makeVisible();
    this->secondMonomino->makeVisible();
}

int_fast32_t Domino::lookBelow() const {
    // TODO consider the position of each monomino, e.g. after move or rotation
    return this->firstMonomino->lookBelow();
}

void Domino::moveDown() {
    this->firstMonomino->moveDown();
    this->secondMonomino->moveDown();
}

int_fast32_t Domino::lookLeft() const {
    // TODO consider the position of each monomino, e.g. after move or rotation
    return this->firstMonomino->lookLeft();
}

void Domino::moveLeft() {
    this->firstMonomino->moveLeft();
    this->secondMonomino->moveLeft();
}

int_fast32_t Domino::lookRight() const {
    // TODO consider the position of each monomino, e.g. after move or rotation
    return this->secondMonomino->lookRight();
}

void Domino::moveRight() {
    this->firstMonomino->moveRight();
    this->secondMonomino->moveRight();
}

// Rotate domino by the pivot - the first monomino
// f: first monomino - the pivot
// s: second monomino
//
//         s
// fs f sf f
//    s
//
// ##            -> # (2, 4)
// (2, 4) (2, 5)    # (3, 4)    second monomino: move down, move left
//
// # (2, 4) -> ## (2, 4) (2, 5) second monomino: move right, move up
// # (3, 4)
void Domino::rotateClockwise() {
    bool isDominoInHorizontalPosition = this->firstMonomino->getRow() == this->secondMonomino->getRow();
    if (isDominoInHorizontalPosition) {
        // first monomino (pivot) =         (2, 4)
        // second monomino =                (2, 5)
        // second monomino (desired) =      (3, 4)
        this->secondMonomino->moveDown(); // 3, 5
        this->secondMonomino->moveLeft(); // 3, 4
        return;
    }

    // domino is in vertical position
    this->secondMonomino->moveRight();
    this->secondMonomino->moveUp();
}
