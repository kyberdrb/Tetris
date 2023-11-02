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
    if (this->firstMonomino->getColumn() < this->secondMonomino->getColumn() ) {
        return this->firstMonomino->lookLeft();
    }
    return this->secondMonomino->lookLeft();
}

void Domino::moveLeft() {
    this->firstMonomino->moveLeft();
    this->secondMonomino->moveLeft();
}

int_fast32_t Domino::lookRight() const {
    if (this->firstMonomino->getColumn() > this->secondMonomino->getColumn() ) {
        return this->firstMonomino->lookRight();
    }
    return this->secondMonomino->lookRight();
}

void Domino::moveRight() {
    this->firstMonomino->moveRight();
    this->secondMonomino->moveRight();
}

int_fast32_t Domino::lookUp() const {
    return this->secondMonomino->lookUp();
}

bool Domino::isVertical() const {
    return this->firstMonomino->getColumn() == this->secondMonomino->getColumn();
}

void Domino::rotateClockwise() {
    auto rotationCoordinatesForSecondMonomino = this->freeOrthogonalNeighboursForFirstMonomino.front();

    auto targetRowOfSecondMonomino = rotationCoordinatesForSecondMonomino.first;
    if (targetRowOfSecondMonomino < this->secondMonomino->getRow() ) {
        auto numberOfNeededUpMoves = this->secondMonomino->getRow() - targetRowOfSecondMonomino;
        for (int moveCount = 0; moveCount < numberOfNeededUpMoves; ++moveCount) {
            this->secondMonomino->moveUp();
        }
    }
    if (targetRowOfSecondMonomino > this->secondMonomino->getRow() ) {
        auto numberOfNeededDownMoves = targetRowOfSecondMonomino - this->secondMonomino->getRow();
        for (int moveCount = 0; moveCount < numberOfNeededDownMoves; ++moveCount) {
            this->secondMonomino->moveDown();
        }
    }

    auto targetColumnOfSecondMonomino = rotationCoordinatesForSecondMonomino.second;
    if (targetColumnOfSecondMonomino < this->secondMonomino->getColumn() ) {
        auto numberOfNeededLeftMoves = this->secondMonomino->getColumn() - targetColumnOfSecondMonomino;
        for (int moveCount = 0; moveCount < numberOfNeededLeftMoves; ++moveCount) {
            this->secondMonomino->moveLeft();
        }
    }
    if (targetColumnOfSecondMonomino > this->secondMonomino->getColumn() ) {
        auto numberOfNeededRightMoves = targetColumnOfSecondMonomino - this->secondMonomino->getColumn();
        for (int moveCount = 0; moveCount < numberOfNeededRightMoves; ++moveCount) {
            this->secondMonomino->moveRight();
        }
    }

    this->freeOrthogonalNeighboursForFirstMonomino.pop_front();
    this->freeOrthogonalNeighboursForFirstMonomino.push_back(rotationCoordinatesForSecondMonomino);
}

void Domino::clearOrthogonallyAdjacentNeighboursToFirstMonomino() {
    this->freeOrthogonalNeighboursForFirstMonomino.clear();
}

void Domino::addRotationCoordinate(std::pair<int_fast32_t, int_fast32_t> coordinates) {
    this->freeOrthogonalNeighboursForFirstMonomino.push_front(coordinates);
}

std::vector<std::pair<int_fast32_t, int_fast32_t>> Domino::lookAroundFirstMonomino() const {
    std::vector<std::pair<int_fast32_t, int_fast32_t>> orthogonalNeighbours;
    orthogonalNeighbours.reserve(4);
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->getRow(), this->firstMonomino->lookRight() ) );
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->lookUp(), this->firstMonomino->getColumn() ) );
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->getRow(), this->firstMonomino->lookLeft() ) );
    orthogonalNeighbours.emplace_back(std::make_pair<int_fast32_t, int_fast32_t>(this->firstMonomino->lookBelow(), this->firstMonomino->getColumn() ) );
    return orthogonalNeighbours;
}

void Domino::adjustRotationCoordinatesOrderByCurrentOrientation() {
    // Current -> Desired next clockwise orientation
    // 270 -> 180
    //  f  -> sf
    //  s
    bool isDominoIn270DegreeOrientation =
        (this->firstMonomino->getRow() < this->secondMonomino->getRow() ) &&
        (this->firstMonomino->getColumn() == this->secondMonomino->getColumn() );
    if (isDominoIn270DegreeOrientation) {
        moveFrontOrthogonalNeighbourToBack();
        return;
    }

    // 180 -> 90
    // sf  -> s
    //        f
    bool isDominoIn180DegreeOrientation =
        (this->firstMonomino->getRow() == this->secondMonomino->getRow() ) &&
        (this->firstMonomino->getColumn() > this->secondMonomino->getColumn() );
    if (isDominoIn180DegreeOrientation) {
        for (int i = 0; i < 2; ++i) {
            moveFrontOrthogonalNeighbourToBack();
        }
        return;
    }

    // 90 -> 0
    // s  -> fs
    // f
    bool isDominoIn90DegreeOrientation =
        (this->firstMonomino->getRow() > this->secondMonomino->getRow() ) &&
        (this->firstMonomino->getColumn() == this->secondMonomino->getColumn() );
    if (isDominoIn90DegreeOrientation) {
        for (int i = 0; i < 3; ++i) {
            moveFrontOrthogonalNeighbourToBack();
        }
        return;
    }
}

void Domino::moveFrontOrthogonalNeighbourToBack() {
    auto frontElement = this->freeOrthogonalNeighboursForFirstMonomino.front();
    this->freeOrthogonalNeighboursForFirstMonomino.pop_front();
    this->freeOrthogonalNeighboursForFirstMonomino.push_back(frontElement);
}
