#pragma once

#include <functional>
#include <tuple>

int random(int start, int end);
bool inRange(int value, int start, int end);
void clearInput();

template <typename T>
std::tuple<bool, T> input(std::function<bool()> validator);