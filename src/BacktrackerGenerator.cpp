#include "BacktrackerGenerator.h"

#include <algorithm>
#include <random>

namespace {

    // Прокладывает коридоры из комнаты (r, c)
    void carve(int r, int c, std::vector<std::string>& lines,
               std::vector<std::vector<bool>>& visited, std::mt19937& rng) {
        visited[r][c] = true;
        lines[2 * r + 1][2 * c + 1] = '.';

        Point dirs[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        std::shuffle(std::begin(dirs), std::end(dirs), rng);

        int height = static_cast<int>(visited.size());
        int width = static_cast<int>(visited[0].size());

        for (auto [dr, dc] : dirs) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr < 0 || nr >= height || nc < 0 || nc >= width || visited[nr][nc])
                continue;
            
            lines[2 * r + 1 + dr][2 * c + 1 + dc] = '.';
            carve(nr, nc, lines, visited, rng);
        }
    }

} // namespace

Grid BacktrackerGenerator::generate(int height, int width, unsigned seed) const {
    std::vector<std::string> lines = wallsOnly(height, width);
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::mt19937 rng(seed);

    carve(0, 0, lines, visited, rng);
    return finishMaze(lines);
}