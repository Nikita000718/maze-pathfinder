#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "AStarFinder.h"
#include "BacktrackerGenerator.h"
#include "BfsFinder.h"
#include "DfsFinder.h"
#include "DijkstraFinder.h"
#include "Grid.h"
#include "KruskalGenerator.h"

namespace {

using Finders = std::vector<std::unique_ptr<IPathfinder>>;

int readInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        int value;
        if (std::cin >> value && value >= min && value <= max)
            return value;

        if (std::cin.eof())
            throw std::runtime_error("Input closed");

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number from " << min << " to " << max << '\n';
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    // ws пропускает перевод строки, оставшийся после ввода числа
    std::getline(std::cin >> std::ws, line);
    return line;
}

Finders makeFinders() {
    Finders finders;
    finders.push_back(std::make_unique<BfsFinder>());
    finders.push_back(std::make_unique<DfsFinder>());
    finders.push_back(std::make_unique<DijkstraFinder>());
    finders.push_back(std::make_unique<AStarFinder>(Heuristic::Manhattan));
    finders.push_back(std::make_unique<AStarFinder>(Heuristic::Euclidean));
    return finders;
}

Grid generateMaze(const IGenerator& generator) {
    int height = readInt("Height in rooms (2-100): ", 2, 100);
    int width = readInt("Width in rooms (2-100): ", 2, 100);
    int seed = readInt("Seed (0 = random): ", 0, 1'000'000'000);

    unsigned actual = seed == 0 ? std::random_device{}() : static_cast<unsigned>(seed);
    // Печатаем seed, чтобы можно было повторить тот же лабиринт
    std::cout << generator.name() << ", seed " << actual << '\n';
    return generator.generate(height, width, actual);
}

struct Timed {
    Result result;
    double ms = 0;
};

// Запускает алгоритм и замеряет время в миллисекундах
Timed measure(const IPathfinder& finder, const Grid& grid) {
    auto begin = std::chrono::steady_clock::now();
    Result result = finder.find(grid);
    auto end = std::chrono::steady_clock::now();
    return {result, std::chrono::duration<double, std::milli>(end - begin).count()};
}

void solveOne(const Grid& grid, const Finders& finders) {
    for (size_t i = 0; i < finders.size(); ++i)
        std::cout << i + 1 << ". " << finders[i]->name() << '\n';
    int choice = readInt("Algorithm: ", 1, static_cast<int>(finders.size()));

    const IPathfinder& finder = *finders[choice - 1];
    Timed t = measure(finder, grid);
    if (!t.result.found()) {
        std::cout << "Path not found\n";
        return;
    }

    Grid solved = grid;
    solved.markPath(t.result.path);
    std::cout << solved
              << finder.name() << ": length " << t.result.path.size() - 1
              << ", cost " << pathCost(grid, t.result.path)
              << ", visited " << t.result.visited
              << ", time " << std::fixed << std::setprecision(3) << t.ms << " ms\n";
}

void compareAll(const Grid& grid, const Finders& finders) {
    std::cout << std::left << std::setw(16) << "Algorithm" << std::right
              << std::setw(8) << "Length"
              << std::setw(8) << "Cost"
              << std::setw(10) << "Visited"
              << std::setw(12) << "Time, ms" << '\n'
              << std::string(54, '-') << '\n';

    for (const auto& finder : finders) {
        Timed t = measure(*finder, grid);

        std::cout << std::left << std::setw(16) << finder->name() << std::right;
        if (t.result.found())
            std::cout << std::setw(8) << t.result.path.size() - 1
                      << std::setw(8) << pathCost(grid, t.result.path);
        else
            std::cout << std::setw(8) << "-" << std::setw(8) << "-";
        std::cout << std::setw(10) << t.result.visited
                  << std::setw(12) << std::fixed << std::setprecision(3) << t.ms << '\n';
    }
}

void printMenu(bool hasMaze) {
    std::cout << "\n=== Maze Pathfinder ===\n"
              << "1. Load maze from file\n"
              << "2. Generate maze (Backtracker)\n"
              << "3. Generate maze (Kruskal)\n";
    // Пункты для работы с лабиринтом показываем, только когда он есть
    if (hasMaze)
        std::cout << "4. Show maze\n"
                  << "5. Solve with one algorithm\n"
                  << "6. Compare all algorithms\n";
    std::cout << "0. Exit\n";
}

} // namespace

int main() {
    Finders finders = makeFinders();
    std::optional<Grid> grid;  // пусто, пока лабиринт не загружен

    try {
        while (true) {
            printMenu(grid.has_value());
            int choice = readInt("> ", 0, grid ? 6 : 3);
            if (choice == 0)
                return 0;

            try {
                switch (choice) {
                    case 1: grid = Grid::fromFile(readLine("File path: ")); break;
                    case 2: grid = generateMaze(BacktrackerGenerator{}); break;
                    case 3: grid = generateMaze(KruskalGenerator{}); break;
                    case 4: std::cout << *grid; break;
                    case 5: solveOne(*grid, finders); break;
                    case 6: compareAll(*grid, finders); break;
                }
                if (choice <= 3)
                    std::cout << "Maze " << grid->rows() << "x" << grid->cols() << " ready\n";
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << '\n';
        return 1;
    }
}