#include "BfsFinder.h"

#include <queue>

Result BfsFinder::find(const Grid& grid) const
{
    const Point start = grid.start();
    const Point end = grid.end();

    std::vector<std::vector<Point>> parent(
        grid.rows(), std::vector<Point>(grid.cols(), Point{-1, -1}));
    std::vector<std::vector<bool>> seen(
        grid.rows(), std::vector<bool>(grid.cols(), false));

    std::queue<Point> queue;
    queue.push(start);
    seen[start.row][start.col] = true;

    Result result;
    while (!queue.empty())
    {
        Point current = queue.front();
        queue.pop();
        ++result.visited;

        if (current == end)
        {
            result.path = restorePath(parent, start, end);
            break;
        }

        for (Point next : grid.neighbors(current))
        {
            if (!seen[next.row][next.col])
            {
                seen[next.row][next.col] = true;
                parent[next.row][next.col] = current;
                queue.push(next);
            }
        }
    }
    return result;
}
