#pragma once

#include "Pathfinder.h"

class BfsFinder : public IPathfinder
{
public:
    std::string name() const override { return "BFS"; }
    Result find(const Grid& grid) const override;
};