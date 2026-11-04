#include <catch2/catch_test_macros.hpp>

#include <cstdlib>

#include "BfsFinder.h"
#include "DfsFinder.h"

TEST_CASE("DFS finds a valid path") {
    Grid grid({
        "#######",
        "#S....#",
        "#.###.#",
        "#....E#",
        "#######",
    });
    Result result = DfsFinder{}.find(grid);

    REQUIRE(result.found());
    REQUIRE(result.path.front() == grid.start());
    REQUIRE(result.path.back() == grid.end());

    for (size_t i = 1; i < result.path.size(); ++i) {
        Point a = result.path[i - 1];
        Point b = result.path[i];
        REQUIRE(std::abs(a.row - b.row) + std::abs(a.col - b.col) == 1);
        REQUIRE(grid.isWalkable(b));
    }
}

TEST_CASE("DFS path is never shorter than BFS") {
    Grid grid({
        "#######",
        "#S....#",
        "#.....#",
        "#....E#",
        "#######",
    });
    Result dfs = DfsFinder{}.find(grid);
    Result bfs = BfsFinder{}.find(grid);

    // BFS находит кратчайший путь, DFS может только длиннее или равный
    REQUIRE(dfs.path.size() >= bfs.path.size());
}

TEST_CASE("DFS returns empty path when there is no way") {
    Grid grid({
        "#####",
        "#S#E#",
        "#####",
    });
    REQUIRE_FALSE(DfsFinder{}.find(grid).found());
}