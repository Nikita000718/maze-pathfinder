#include "DijkstraFinder.h"

#include <climits>
#include <functional>
#include <queue>

Result DijkstraFinder::find(const Grid &grid) const {
    const Point start = grid.start();
    const Point end = grid.end();

    std::vector<std::vector<int>> dist(
        grid.rows(), std::vector<int>(grid.cols(), INT_MAX));
    std::vector<std::vector<Point>> parent(
        grid.rows(), std::vector<Point>(grid.cols(), Point{-1, -1}));

    // Пара {стоимость, клетка};
    using Item = std::pair<int, Point>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> queue;

    dist[start.row][start.col] = 0;
    queue.push({0, start});

    Result result;
    while (!queue.empty()) {
        auto [d, current] = queue.top();
        queue.pop();

        if (d > dist[current.row][current.col])
            continue;
        ++result.visited;

        if (current == end) {
            result.path = restorePath(parent, start, end);
            break;
        }

        for (Point next : grid.neighbors(current)) {
            int newDist = d + grid.cost(next);
            if (newDist < dist[next.row][next.col]) {
                dist[next.row][next.col] = newDist;
                parent[next.row][next.col] = current;
                queue.push({newDist, next});
            }
        }
    }
    return result;
}
