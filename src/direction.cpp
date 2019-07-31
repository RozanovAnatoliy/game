#include "direction.h"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace Utils;

void Direction::invert()
{
    switch (value) {
        case Direction::DOWN:
            value = Direction::UP;
            break;
        case Direction::UP:
            value = Direction::DOWN;
            break;
        case Direction::RIGHT:
            value = Direction::LEFT;
            break;
        case Direction::LEFT:
            value = Direction::RIGHT;
            break;
    }
}

void Direction::set_direction(int direction)
{
    this->value = direction;
}

void Direction::rand(int except)
{
    std::vector<int> directions = { Direction::DOWN, Direction::LEFT, Direction::RIGHT, Direction::UP };
    auto except_element = std::find(directions.begin(), directions.end(), except);
    if (except_element != directions.end()) {
        directions.erase(except_element);
    }

    int new_direction = std::rand() % directions.size();
    value = directions[new_direction];
}
