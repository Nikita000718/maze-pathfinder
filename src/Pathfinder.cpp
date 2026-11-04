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
