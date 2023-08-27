#include "Brick.h"

Brick::Brick() :
    row(0),
    column(2),
    isBrickVisible(false)
{}

int_fast32_t Brick::getRow() const {
    return this->row;
}

int_fast32_t Brick::getColumn() const {
    return this->column;
}

std::string Brick::getBrickSign() const {
    return "#";
//    return "■"; // '■' - BLACK SQUARE - u9632
//    return "⎕"; // '⎕ - Apl Functional Symbol Quad'
//    return "□";  // '□ - White Square'
//    return "⌷";  // '⌷ - Apl Functional Symbol Squish Quad'
}

bool Brick::isVisible() const {
    return this->isBrickVisible;
}

void Brick::makeVisible() {
    this->isBrickVisible = true;
}

int_fast32_t Brick::lookBelow() const {
    return this->row + 1;
}

void Brick::moveDown() {
    this->row += 1;
}

int_fast32_t Brick::lookLeft() const {
    return this->column - 1;
}

void Brick::moveLeft() {
    this->column -= 1;
}

int_fast32_t Brick::lookRight() const {
    return this->column + 1;
}

void Brick::moveRight() {
    this->column += 1;
}
