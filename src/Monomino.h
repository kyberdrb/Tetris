#pragma once

#include <cstdint>
#include <string>

class Monomino {
public:
    Monomino();

    int_fast32_t getRow() const;
    int_fast32_t getColumn() const;

    bool isVisible() const;
    void makeVisible();
    void hide();

    int_fast32_t lookBelow() const;
    void moveDown();

    int_fast32_t lookUp() const;
    void moveUp();

    int_fast32_t lookLeft() const;
    void moveLeft();

    int_fast32_t lookRight() const;
    void moveRight();

private:
    int_fast32_t row;
    int_fast32_t column;
    bool isMonominoVisible;
};
