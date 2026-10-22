#pragma once

#include <compare>

struct Point
{
    int row = 0;
    int col = 0;

    auto operator<=>(const Point&) const = default;
};