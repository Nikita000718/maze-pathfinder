#include "Generator.h"

#include <stdexcept>

std::vector<std::string> wallsOnly(int height, int width) {
    if (height < 2 || width < 2)
        throw std::invalid_argument("Maze must be at least 2x2 rooms");
    return std::vector<std::string>(2 * height + 1, std::string(2 * width + 1, '#'));
}

Grid finishMaze(std::vector<std::string> lines) {
    int rows = static_cast<int>(lines.size());
    int cols = static_cast<int>(lines[0].size());
    lines[1][1] = 'S';
    lines[rows - 2][cols - 2] = 'E';
    return Grid(lines);
}