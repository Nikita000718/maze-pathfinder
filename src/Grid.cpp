#include "Grid.h"
#include "../include/Grid.h"

#include <stdexcept>

#include "../include/Cell.h"

namespace
{
    Cell fromChar(char ch)
    {
        switch (ch)
        {
        case '#': return Cell::Wall;
        case '.': return Cell::Free;
        case 'S': return Cell::Start;
        case 'E': return Cell::End;
        default:
            throw std::invalid_argument(std::string("Unknown symbol: ") + ch);
        }
    }

} // namespace

Grid::Grid(const std::vector<std::string>& lines)
{
    if (lines.empty() || lines[0].empty())
        throw std::invalid_argument("Empty maze");

    rows_ = static_cast<int>(lines.size());
    cols_ = static_cast<int>(lines[0].size());
    cells_.assign(rows_, std::vector<Cell>(cols()));

    int startCount = 0;
    int endCount = 0;

    for (int r = 0; r < rows_; ++r)
    {
        if (static_cast<int>(lines[r].size()) != cols_)
            throw std::invalid_argument("Rows have different lengths");

        for (int c = 0; c < cols_; ++c)
        {
            Cell cell = fromChar(lines[r][c]);
            cells_[r][c] = cell;

            if (cell == Cell::Start) { start_ = {r, c}; ++startCount; }
            if (cell == Cell::End) {end_ = {r, c}; ++endCount; }
        }
    }

    // Старт и финиш должны быть ровно по одному
    if (startCount != 1 || endCount != 1)
        throw std::invalid_argument("Maze must have exactly one S and one E");
}

bool Grid::inBounds(Point p) const
{
    return p.row >= 0 && p.row < rows_ && p.col >= 0 && p.col < cols_;
}

bool Grid::isWalkable(Point p) const
{
    return inBounds(p) && at(p) != Cell::Wall;
}

Cell Grid::at(Point p) const
{
    return cells_[p.row][p.col];
}

void Grid::set(Point p, Cell cell)
{
    cells_[p.row][p.col] = cell;
}

std::vector<Point> Grid::neighbors(Point p) const
{
    static constexpr Point dirs[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::vector<Point> result;
    for (auto [dr, dc] : dirs)
    {
        Point next{p.row + dr, p.col + dc};
        if (isWalkable(next))
            result.push_back(next);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Grid& grid) {
    for (const auto& row : grid.cells_) {
        for (Cell cell : row)
            os << toChar(cell);
        os << '\n';
    }
    return os;
}