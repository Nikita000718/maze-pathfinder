#include <catch2/catch_test_macros.hpp>

#include "AStarFinder.h"
#include "DijkstraFinder.h"

TEST_CASE("A* finds the cheapest path like Dijkstra") {
    Grid grid({
        "###########",
        "#S..999..E#",
        "#.#######.#",
        "#.........#",
        "###########",
    });
    // Проверяем обе эвристики
    for (Heuristic h : {Heuristic::Manhattan, Heuristic::Euclidean}) {
        Result astar = AStarFinder{h}.find(grid);
        REQUIRE(astar.found());
        REQUIRE(pathCost(grid, astar.path) == 12);
    }
}

TEST_CASE("A* visits fewer cells than Dijkstra") {
    Grid grid({
        "#######",
        "#S....#",
        "#.....#",
        "#....E#",
        "#######",
    });
    Result astar = AStarFinder{}.find(grid);
    Result dijkstra = DijkstraFinder{}.find(grid);

    REQUIRE(pathCost(grid, astar.path) == pathCost(grid, dijkstra.path));
    REQUIRE(astar.visited < dijkstra.visited);
}

TEST_CASE("A* returns empty path when there is no way") {
    Grid grid({
        "#####",
        "#S#E#",
        "#####",
    });
    REQUIRE_FALSE(AStarFinder{}.find(grid).found());
}