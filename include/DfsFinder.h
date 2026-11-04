#pragma once

#include "Pathfinder.h"

class DfsFinder : public IPathfinder
{
public:
    std::string name() const override { return "DFS"; }
    Result find(const Grid& grid) const override;
};