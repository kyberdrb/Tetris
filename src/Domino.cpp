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

int_fast32_t Domino::getRow() const {
    return this->firstMonomino->getRow();
}
int_fast32_t Domino::getColumn() const {
    return this->firstMonomino->getColumn();
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
    return this->firstMonomino->lookRight();
}

void Domino::moveRight() {
    this->firstMonomino->moveRight();
    this->secondMonomino->moveRight();
}
