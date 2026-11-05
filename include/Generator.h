#pragma once

#include <string>
#include <vector>

#include "Grid.h"

// Генератор
class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual std::string name() const = 0;
    // height x width — число комнат, итоговая сетка (2*height+1) x (2*width+1)
    virtual Grid generate(int height, int width, unsigned seed) const = 0;
};

// Заготовка из одних стен
std::vector<std::string> wallsOnly(int height, int width);

// Ставит S в левую верхнюю комнату, E в правую нижнюю и строит Grid
Grid finishMaze(std::vector<std::string> lines);