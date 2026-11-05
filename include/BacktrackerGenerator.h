#pragma once

#include "Generator.h"

class BacktrackerGenerator : public IGenerator {
public:
    std::string name() const override { return "Backtracker"; }
    Grid generate(int height, int width, unsigned seed) const override;
};