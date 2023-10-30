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

bool Domino::isFirstMonominoVisible() const {
    return this->firstMonomino->isVisible();
}

bool Domino::isSecondMonominoVisible() const {
    return this->secondMonomino->isVisible();
}

void Domino::makeVisible() {
    this->firstMonomino->makeVisible();
    this->secondMonomino->makeVisible();
}

void Domino::hideFirstMonomino() {
    this->firstMonomino->hide();
}

void Domino::hideSecondMonomino() {
    this->secondMonomino->hide();
}

int_fast32_t Domino::lookBelowFirstMonomino() const {
    return this->firstMonomino->lookBelow();
}

int_fast32_t Domino::lookBelowSecondMonomino() const {
    return this->secondMonomino->lookBelow();
}

void Domino::moveDown() {
    this->firstMonomino->moveDown();
    this->secondMonomino->moveDown();
}

void Domino::moveFirstMonominoDown() {
    this->firstMonomino->moveDown();
}

void Domino::moveSecondMonominoDown() {
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

int_fast32_t Domino::lookUp() const {
    return this->secondMonomino->lookUp();
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
    // TODO implement full clockwise rotation pattern
    // Naïve/Simplified implementation
    bool isDominoInHorizontalPosition = this->firstMonomino->getRow() == this->secondMonomino->getRow();
    if (isDominoInHorizontalPosition) {
        // first monomino (pivot) =         (2, 4)
        // second monomino =                (2, 5)
        // second monomino (desired) =      (3, 4)
        this->secondMonomino->moveDown(); // 3, 5
        this->secondMonomino->moveLeft(); // 3, 4
        return;
    }

    this->secondMonomino->moveUp();
    this->secondMonomino->moveRight();

    // 0 -> 270
    // fs -> f
    //       s
    bool isDominoInZeroDegreePosition =
        (this->firstMonomino->getRow() == this->secondMonomino->getRow() ) &&
        (this->firstMonomino->getColumn() < this->secondMonomino->getColumn() );
//    if (isDominoInZeroDegreePosition) {
//    this->secondMonomino->moveDown(); // 3, 5
//    this->secondMonomino->moveLeft(); // 3, 4
//    return;
//}

    // 270 -> 180
    // f -> sf
    // s
    bool isDominoIn270DegreePosition =
        (this->firstMonomino->getColumn() == this->secondMonomino->getColumn() ) &&
        (this->firstMonomino->getRow() > this->secondMonomino->getRow() );
//    if (isDominoIn270DegreePosition) {
//        this->secondMonomino->moveUp();
//        this->secondMonomino->moveLeft();
//        return;
//    }

    // 180 -> 90
    // sf -> s
    //       f
    bool isDominoIn180DegreePosition =
        (this->firstMonomino->getRow() == this->secondMonomino->getRow() ) &&
        (this->firstMonomino->getColumn() > this->secondMonomino->getColumn() );
//    if (isDominoIn180DegreePosition) {
//        this->secondMonomino->moveUp();
//        this->secondMonomino->moveRight();
//        return;
//    }

    // domino is in vertical position
    // current (version 1: simplified): 270 -> 0
    // desired: 90 -> 0
    // s -> fs
    // f
    bool isDominoIn90DegreePosition =
        (this->firstMonomino->getRow() < this->secondMonomino->getRow() ) &&
        (this->firstMonomino->getColumn() == this->secondMonomino->getColumn() );
//    if (isDominoIn90DegreePosition) {
//        this->secondMonomino->moveDown();
//        this->secondMonomino->moveRight();
//        return;
//    }
}

std::vector<std::pair<int_fast32_t, int_fast32_t>> Domino::lookAroundFirstMonomino() const {
    std::vector<std::pair<int_fast32_t, int_fast32_t>> orthogonalNeighbours;
    orthogonalNeighbours.reserve(4);
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->lookBelow(), this->firstMonomino->getColumn() ) );
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->getRow(), this->firstMonomino->lookLeft() ) );
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->lookUp(), this->firstMonomino->getColumn() ) );
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->getRow(), this->firstMonomino->lookRight() ) );
    return orthogonalNeighbours;
}

bool Domino::isVertical() const {
    return this->firstMonomino->getColumn() == this->secondMonomino->getColumn();
}
