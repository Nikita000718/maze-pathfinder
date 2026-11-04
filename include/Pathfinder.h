#pragma once

#include <string>
#include <vector>

#include <Grid.h>

struct Result
{
    std::vector<Point> path;
    int visited = 0;

    bool found() const { return !path.empty(); }
};

// Общий интерфейс для всех алгоритмов поиска пути
class IPathfinder
{
public:
    virtual ~IPathfinder() = default;
    virtual std::string name() const = 0;
    virtual Result find(const Grid& grid) const = 0;
};

// Собирает путь по массиву
std::vector<Point> restorePath(const std::vector<std::vector<Point>>& parent,
                               Point start, Point end);