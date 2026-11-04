#include <iostream>
#include <string>

#include "Grid.h"

int main(int argc, char* argv[])
{
    std::string path = argc > 1 ? argv[1] : "mazes/simple.txt";

    try
    {
        Grid grid = Grid::fromFile(path);

        std::cout << grid << '\n';
        std::cout << "Size: " << grid.rows() << "x" << grid.cols() << '\n';

        // Проверка соседей старта
        std::cout << "Start neighbors:";
        for (Point p : grid.neighbors(grid.start()))
            std::cout << " (" << p.row << ", " << p.col << ")";
        std::cout << '\n';
    } catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}