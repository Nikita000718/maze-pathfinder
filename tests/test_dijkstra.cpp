#include <catch2/catch_test_macros.hpp>

#include "BfsFinder.h"
#include "DijkstraFinder.h"

TEST_CASE("Grid reads cell costs") {
    Grid grid({"#S5E#"});
    REQUIRE(grid.cost({0, 1}) == 1);
    REQUIRE(grid.cost({0, 2}) == 5);
}

TEST_CASE("Dijkstra avoids expensive cells") {
    Grid grid({
        "###########",
        "#S..999..E#",
        "#.#######.#",
        "#.........#",
        "###########",
    });
    Result dijkstra = DijkstraFinder{}.find(grid);
    Result bfs = BfsFinder{}.find(grid);

    REQUIRE(dijkstra.found());
    REQUIRE(pathCost(grid, dijkstra.path) == 12);

    // BFS идёт напрямую: шагов меньше, но дороже
    REQUIRE(bfs.path.size() < dijkstra.path.size());
    REQUIRE(pathCost(grid, bfs.path) == 32);
}

TEST_CASE("Dijkstra equals BFS without weights") {
    Grid grid({
        "#######",
        "#S....#",
        "#.###.#",
        "#....E#",
        "#######",
    });
    REQUIRE(DijkstraFinder{}.find(grid).path.size() ==
            BfsFinder{}.find(grid).path.size());
}