#pragma once

#include "Pathfinder.h"

class DijkstraFinder : public IPathfinder {
public:
    std::string name() const override { return "Dijkstra"; }
    Result find(const Grid& grid) const override;
};