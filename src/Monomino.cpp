#include "Monomino.h"

Monomino::Monomino() :
    row(0),
    column(2),
    isMonominoVisible(false)
{}

int_fast32_t Monomino::getRow() const {
    return this->row;
}

int_fast32_t Monomino::getColumn() const {
    return this->column;
}

bool Monomino::isVisible() const {
    return this->isMonominoVisible;
}

void Monomino::makeVisible() {
    this->isMonominoVisible = true;
}

void Monomino::hide() {
    this->isMonominoVisible = false;
}

int_fast32_t Monomino::lookBelow() const {
    return this->row + 1;
}

void Monomino::moveDown() {
    this->row += 1;
}

int_fast32_t Monomino::lookUp() const {
    return this->row - 1;
}

void Monomino::moveUp() {
    this->row -= 1;
}

int_fast32_t Monomino::lookLeft() const {
    return this->column - 1;
}

void Monomino::moveLeft() {
    this->column -= 1;
}

int_fast32_t Monomino::lookRight() const {
    return this->column + 1;
}

void Monomino::moveRight() {
    this->column += 1;
}
