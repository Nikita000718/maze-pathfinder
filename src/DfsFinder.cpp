#include "DfsFinder.h"

#include <stack>

Result DfsFinder::find(const Grid& grid) const
{
    const Point start = grid.start();
    const Point end = grid.end();

    std::vector<std::vector<Point>> parent(
        grid.rows(), std::vector<Point>(grid.cols(), Point{-1, -1}));
    std::vector<std::vector<bool>> visited(
        grid.rows(), std::vector<bool>(grid.cols(), false));

    std::stack<Point> stack;
    stack.push(start);

    Result result;
    while (!stack.empty())
    {
        Point current = stack.top();
        stack.pop();

        if (visited[current.row][current.col])
            continue;
        visited[current.row][current.col] = true;
        ++result.visited;

        if (current == end)
        {
            result.path = restorePath(parent, start, end);
            break;
        }

        for (Point next : grid.neighbors(current))
        {
            if (!visited[next.row][next.col])
            {
                parent[next.row][next.col] = current;
                stack.push(next);
            }
        }
    }
    return result;
}
