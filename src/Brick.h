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

    bool isActive();
    void deactivate();

    int_fast32_t lookBelow();
    void moveDown();

    int_fast32_t lookLeft();
    void moveLeft();

    int_fast32_t lookRight();
    void moveRight();

private:
    int_fast32_t row;
    int_fast32_t column;
    bool isBrickVisible;
    bool isBrickActive;
};
