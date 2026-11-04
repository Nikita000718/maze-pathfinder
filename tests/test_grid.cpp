#include <catch2/catch_test_macros.hpp>

#include "Grid.h"

TEST_CASE("Grid finds start and end") {
    Grid grid({
        "#####",
        "#S.E#",
        "#####",
    });
    REQUIRE(grid.rows() == 3);
    REQUIRE(grid.cols() == 5);
    REQUIRE(grid.start() == Point{1, 1});
    REQUIRE(grid.end() == Point{1, 3});

    // У старта один сосед: клетка справа
    auto n = grid.neighbors(grid.start());
    REQUIRE(n.size() == 1);
    REQUIRE(n[0] == Point{1, 2});
}

TEST_CASE("Grid rejects invalid mazes") {
    REQUIRE_THROWS(Grid({"#S.#"}));
    REQUIRE_THROWS(Grid({"#S.E#", "##"}));
    REQUIRE_THROWS(Grid({"#SXE#"}));
}