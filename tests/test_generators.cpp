#include <catch2/catch_test_macros.hpp>

#include <sstream>

#include "BacktrackerGenerator.h"
#include "BfsFinder.h"
#include "DisjointSet.h"
#include "KruskalGenerator.h"

TEST_CASE("DisjointSet unites sets") {
    DisjointSet dsu(5);
    REQUIRE(dsu.unite(0, 1));
    REQUIRE(dsu.unite(1, 2));
    REQUIRE(dsu.find(0) == dsu.find(2));
    REQUIRE(dsu.find(0) != dsu.find(3));
    REQUIRE_FALSE(dsu.unite(0, 2));  // уже в одном множестве
}

TEST_CASE("Generated mazes are perfect") {
    BacktrackerGenerator backtracker;
    KruskalGenerator kruskal;
    const IGenerator* generators[] = {&backtracker, &kruskal};

    for (const IGenerator* gen : generators) {
        Grid grid = gen->generate(8, 12, 42);
        REQUIRE(grid.rows() == 17);
        REQUIRE(grid.cols() == 25);

        // Дерево из 96 комнат: 96 комнат + 95 сломанных стен
        int open = 0;
        for (int r = 0; r < grid.rows(); ++r)
            for (int c = 0; c < grid.cols(); ++c)
                if (grid.at({r, c}) != Cell::Wall)
                    ++open;
        REQUIRE(open == 8 * 12 * 2 - 1);

        REQUIRE(BfsFinder{}.find(grid).found());
    }
}

TEST_CASE("Same seed gives the same maze") {
    std::ostringstream a;
    std::ostringstream b;
    a << KruskalGenerator{}.generate(5, 5, 7);
    b << KruskalGenerator{}.generate(5, 5, 7);
    REQUIRE(a.str() == b.str());
}