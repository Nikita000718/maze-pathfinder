#include "AStarFinder.h"

#include <climits>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <queue>
#include <tuple>

std::string AStarFinder::name() const {
    return heuristic_ == Heuristic::Manhattan ? "A* (Manhattan)" : "A* (Euclidean)";
}

Result AStarFinder::find(const Grid& grid) const {
    const Point start = grid.start();
    const Point end = grid.end();

    auto h = [&](Point p) -> double {
        int dr = std::abs(p.row - end.row);
        int dc = std::abs(p.col - end.col);
        if (heuristic_ == Heuristic::Manhattan)
            return dr + dc;
        return std::sqrt(dr * dr + dc * dc);
    };

    std::vector<std::vector<int>> dist(
        grid.rows(), std::vector<int>(grid.cols(), INT_MAX));
    std::vector<std::vector<Point>> parent(
        grid.rows(), std::vector<Point>(grid.cols(), Point{-1, -1}));
    std::vector<std::vector<bool>> closed(
        grid.rows(), std::vector<bool>(grid.cols(), false));

    // {f = g + h, h, клетка}: при равном f берём клетку ближе к финишу
    using Item = std::tuple<double, double, Point>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> open;

    dist[start.row][start.col] = 0;
    open.push({h(start), h(start), start});

    Result result;
    while (!open.empty()) {
        Point current = std::get<2>(open.top());
        open.pop();

        // Клетка уже обработана через более выгодную запись
        if (closed[current.row][current.col])
            continue;
        closed[current.row][current.col] = true;
        ++result.visited;

        if (current == end) {
            result.path = restorePath(parent, start, end);
            break;
        }

        for (Point next : grid.neighbors(current)) {
            int newDist = dist[current.row][current.col] + grid.cost(next);
            if (newDist < dist[next.row][next.col]) {
                dist[next.row][next.col] = newDist;
                parent[next.row][next.col] = current;
                double hNext = h(next);
                open.push({newDist + hNext, hNext, next});
            }
        }
    }
    return result;
}