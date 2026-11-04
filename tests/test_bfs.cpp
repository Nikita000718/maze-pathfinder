#include <catch2/catch_test_macros.hpp>

#include <cstdlib>

#include "BfsFinder.h"

TEST_CASE("BFS finds shortest path") {
    Grid grid({
        "#######",
        "#S....#",
        "#.###.#",
        "#....E#",
        "#######",
    });
    Result result = BfsFinder{}.find(grid);

    REQUIRE(result.found());
    REQUIRE(result.path.front() == grid.start());
    REQUIRE(result.path.back() == grid.end());
    REQUIRE(result.path.size() == 7);  // 7 клеток = 6 шагов

    for (size_t i = 1; i < result.path.size(); ++i) {
        Point a = result.path[i - 1];
        Point b = result.path[i];
        REQUIRE(std::abs(a.row - b.row) + std::abs(a.col - b.col) == 1);
        REQUIRE(grid.isWalkable(b));
    }
}

TEST_CASE("BFS returns empty path when there is no way") {
    Grid grid({
        "#####",
        "#S#E#",
        "#####",
    });
    Result result = BfsFinder{}.find(grid);

    REQUIRE_FALSE(result.found());
}