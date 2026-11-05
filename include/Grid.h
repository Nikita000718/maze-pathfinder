#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "Cell.h"
#include "Point.h"

class Grid
{
public:
    explicit Grid(const std::vector<std::string>& lines);

    int rows() const { return rows_; }
    int cols() const { return cols_; }
    Point start() const { return start_; }
    Point end() const { return end_; }

    bool inBounds(Point p) const;
    bool isWalkable(Point p) const;
    Cell at(Point p) const;

    // Стоимость входа в клетку
    int cost(Point p) const { return costs_[p.row][p.col]; }

    void set(Point p, Cell cell);

    // Помечает клетки пути символом '*'
    void markPath(const std::vector<Point>& path);

    // Соседние наравление в которые можно шагнуть (4)
    std::vector<Point> neighbors(Point p) const;

    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);

    // Загрузка лабиринта из текстового файла
    static Grid fromFile(const std::string& path);

private:
    int rows_ = 0;
    int cols_ = 0;
    std::vector<std::vector<Cell>> cells_;
    std::vector<std::vector<int>> costs_;
    Point start_;
    Point end_;
};