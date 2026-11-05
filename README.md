# maze-pathfinder

Console maze generator and pathfinding visualizer written in C++20.
Load a maze from a text file or generate one, then solve it with different
algorithms and compare them side by side.

## Features

- **Pathfinding:** BFS, DFS, Dijkstra, A* (Manhattan and Euclidean heuristics)
- **Weighted cells:** digits `1`–`9` make a cell more expensive to enter
- **Maze generation:** recursive backtracker and Kruskal's algorithm (with a disjoint set)
- **Comparison table:** path length, path cost, visited cells and run time
- Unit tests with Catch2

## Algorithms

| Algorithm | Data structure | Shortest by steps | Cheapest by cost |
|---|---|---|---|
| BFS | queue | yes | no |
| DFS | stack | no | no |
| Dijkstra | priority queue | yes | yes |
| A* | priority queue + heuristic | yes | yes |

A* finds the same path as Dijkstra but usually visits far fewer cells.

## Build

Requires CMake 3.20+ and a C++20 compiler. Catch2 is downloaded automatically.

```bash
cmake -S . -B build
cmake --build build
```

Run from the project root so that paths like `mazes/medium.txt` work:

```bash
./build/maze          # interactive menu
./build/maze_tests    # unit tests
```

## Maze format

| Symbol | Meaning |
|---|---|
| `#` | wall |
| `.` | free cell (cost 1) |
| `1`–`9` | free cell with the given cost |
| `S` | start |
| `E` | end |

Example (`mazes/weighted.txt`): the short route goes through expensive cells.

```
###########
#S..999..E#
#.#######.#
#.........#
###########
```

BFS and DFS take the top route (length 8, cost 32).
Dijkstra and A* go around (length 12, cost 12):

```
###########
#S..999..E#
#*#######*#
#*********#
###########
```

## Project structure

```
include/   headers
src/       library sources and main.cpp
tests/     Catch2 unit tests
mazes/     example mazes
```