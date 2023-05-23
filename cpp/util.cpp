#include <iostream>
#include <random>

#include "util.h"

int random(int start, int end) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(start, end);

    return distribution(eng);
}

bool inRange(int value, int start, int end) {
    return value >= start && value <= end;
}