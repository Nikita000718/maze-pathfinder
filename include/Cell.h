#pragma once

enum class Cell { Wall, Free, Start, End, Path};

// Символ для вывода клетки в консоль
constexpr char toChar(Cell cell)
{
    switch (cell)
    {
    case Cell::Wall: return '#';
    case Cell::Free: return '.';
    case Cell::Start: return 'S';
    case Cell::End:   return 'E';
    case Cell::Path:  return '*';
    }
    return '?';
}