#pragma once

#include "Generator.h"

class KruskalGenerator : public IGenerator {
public:
    std::string name() const override { return "Kruskal"; }
    Grid generate(int height, int width, unsigned seed) const override;
};