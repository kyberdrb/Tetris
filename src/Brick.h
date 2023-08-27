#pragma once

#include <cstdint>
#include <string>

class Brick {
public:
    Brick();

    int_fast32_t getRow() const;
    int_fast32_t getColumn() const;

    std::string getBrickSign() const;

    bool isVisible() const;
    void makeVisible();

//    void deactivate();

    int_fast32_t lookBelow() const;
    void moveDown();

    int_fast32_t lookLeft() const;
    void moveLeft();

    int_fast32_t lookRight() const;
    void moveRight();

private:
    int_fast32_t row;
    int_fast32_t column;
    bool isBrickVisible;
//    bool isBrickActive;
};
