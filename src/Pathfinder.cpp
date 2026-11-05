#include "Pathfinder.h"

#include <algorithm>

std::vector<Point> restorePath(const std::vector<std::vector<Point>>& parent, Point start, Point end)
{
    std::vector<Point> path;
    for (Point p = end; p != start; p = parent[p.row][p.col])
        path.push_back(p);
    path.push_back(start);

    std::reverse(path.begin(), path.end());
    return path;
}

int pathCost(const Grid &grid, const std::vector<Point>& path) {
    int total = 0;

    for (size_t i = 1; i < path.size(); ++i)
        total += grid.cost(path[i]);
    return total;
}
