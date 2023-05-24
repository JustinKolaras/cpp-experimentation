#include <iostream>
#include <random>

#include "util.h"

// Generates a random number inclusive of the start and end parameters.
int random(const int start, const int end) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(start, end);

    return distribution(eng);
}

// Checks if a value is within a range.
bool inRange(const int value, const int start, const int end) {
    return value >= start && value <= end;
}

// Clears the input buffer.
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Receives input via cin with an optional validator.
// A tuple is returned, in which the first value represents the success of the operation and the second value denoting the input
// if applicable. If the operation was not successful, the second value will be the default value of the type.
// If no validator is provided, it will be assumed that the input is valid.
// This function will clear the input buffer as appropriate.
template <typename T>
std::tuple<bool, T> input(const std::function<bool()> validator = true) {
    T value{};

    if (!(std::cin >> value) || !validator()) {
        clearInput();
        return std::make_tuple(false, T{});
    }

    return std::make_tuple(true, value);
}