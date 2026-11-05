#include "Grid.h"

#include <fstream>
#include <stdexcept>


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
    costs_.assign(rows_, std::vector<int>(cols_, 1));

    int startCount = 0;
    int endCount = 0;

    for (int r = 0; r < rows_; ++r)
    {
        if (static_cast<int>(lines[r].size()) != cols_)
            throw std::invalid_argument("Rows have different lengths");

        for (int c = 0; c < cols_; ++c) {
            char ch = lines[r][c];

            // Цифра 1-9: проходимая клетка со стоимостью
            if (ch >= '1' && ch <= '9') {
                cells_[r][c] = Cell::Free;
                costs_[r][c] = ch - '0';
                continue;
            }

            Cell cell = fromChar(ch);
            cells_[r][c] = cell;

            if (cell == Cell::Start) { start_ = {r, c}; ++startCount; }
            if (cell == Cell::End)   { end_ = {r, c};   ++endCount; }
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
    for (int r = 0; r < grid.rows_; ++r) {
        for (int c = 0; c < grid.cols_; ++c) {
            Cell cell = grid.cells_[r][c];
            int cost = grid.costs_[r][c];

            if (cell == Cell::Free && cost > 1)
                os << static_cast<char>('0' + cost);
            else
                os << toChar(cell);
        }
        os << '\n';
    }
    return os;
}

Grid Grid::fromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Cannot open file: " + path);

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        // Если файл сохранен в Windows
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!line.empty())
            lines.push_back(line);
    }
    return Grid(lines);
}

void Grid::markPath(const std::vector<Point>& path)
{
    for (Point p : path)
        if (at(p) == Cell::Free)
            set(p, Cell::Path);
}
