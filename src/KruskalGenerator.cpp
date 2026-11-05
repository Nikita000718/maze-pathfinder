#include "KruskalGenerator.h"

#include <algorithm>
#include <random>

#include "DisjointSet.h"

namespace {

    struct Edge {
        Point a;
        Point b;
    };

} // namespace

Grid KruskalGenerator::generate(int height, int width, unsigned seed) const {
    std::vector<std::string> lines = wallsOnly(height, width);

    std::vector<Edge> edges;
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            lines[2 * r + 1][2 * c + 1] = '.';
            if (c + 1 < width)  edges.push_back({{r, c}, {r, c + 1}});
            if (r + 1 < height) edges.push_back({{r, c}, {r + 1, c}});
        }
    }

    std::mt19937 rng(seed);
    std::shuffle(edges.begin(), edges.end(), rng);

    // Комната (r, c) в DSU имеет номер r * width + c
    DisjointSet rooms(height * width);
    for (const Edge& e : edges) {
        if (rooms.unite(e.a.row * width + e.a.col, e.b.row * width + e.b.col))
            lines[e.a.row + e.b.row + 1][e.a.col + e.b.col + 1] = '.';
    }
    return finishMaze(lines);
}