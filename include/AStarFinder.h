#pragma once

#include "Pathfinder.h"

enum class Heuristic { Manhattan, Euclidean };

class AStarFinder : public IPathfinder {
public:
    explicit AStarFinder(Heuristic heuristic = Heuristic::Manhattan)
        : heuristic_(heuristic) {}

    std::string name() const override;
    Result find(const Grid& grid) const override;

private:
    Heuristic heuristic_;
};