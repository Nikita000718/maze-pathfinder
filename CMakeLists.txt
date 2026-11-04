cmake_minimum_required(VERSION 3.20)
project(maze_pathfinder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(maze_core
        src/Grid.cpp
        src/Pathfinder.cpp
        src/BfsFinder.cpp
)
target_include_directories(maze_core PUBLIC include)
target_compile_options(maze_core PUBLIC -Wall -Wextra -Wpedantic)

add_executable(maze src/main.cpp)
target_link_libraries(maze PRIVATE maze_core)

# Тесты
include(FetchContent)
FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
        tests/test_grid.cpp
        tests/test_bfs.cpp
)
target_link_libraries(tests PRIVATE maze_core Catch2::Catch2WithMain)