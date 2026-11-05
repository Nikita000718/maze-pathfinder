#include <iostream>
#include <random>
#include <string>

#include "AStarFinder.h"
#include "BacktrackerGenerator.h"
#include "BfsFinder.h"
#include "DfsFinder.h"
#include "DijkstraFinder.h"
#include "Grid.h"
#include "KruskalGenerator.h"

void run(const IPathfinder& finder, const Grid& grid) {
    Result result = finder.find(grid);

    std::cout << finder.name() << ": ";
    if (!result.found()) {
        std::cout << "path not found, visited " << result.visited << " cells\n";
        return;
    }
    std::cout << "path length " << result.path.size() - 1
          << ", cost " << pathCost(grid, result.path)
          << ", visited " << result.visited << " cells\n";

    Grid solved = grid;  // копия, чтобы не портить исходный лабиринт
    solved.markPath(result.path);
    std::cout << solved << '\n';
}

Grid loadGrid(const std::string& arg) {
    unsigned seed = std::random_device{}();
    if (arg == "--backtracker")
        return BacktrackerGenerator{}.generate(8, 20, seed);
    if (arg == "--kruskal")
        return KruskalGenerator{}.generate(8, 20, seed);
    return Grid::fromFile(arg);
}

int main(int argc, char* argv[]) {
    std::string path = argc > 1 ? argv[1] : "mazes/medium.txt";

    try {
        Grid grid = loadGrid(path);
        std::cout << grid << '\n';

        run(BfsFinder{}, grid);
        run(DfsFinder{}, grid);
        run(DijkstraFinder{}, grid);
        run(AStarFinder{Heuristic::Manhattan}, grid);
        run(AStarFinder{Heuristic::Euclidean}, grid);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}