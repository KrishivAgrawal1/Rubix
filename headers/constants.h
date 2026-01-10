#pragma once
#include "geometry.h"
#include <map>
#include <vector>

inline constexpr int SCREEN_WIDTH = 1200;
inline constexpr int SCREEN_HEIGHT = 900;
inline constexpr double pi = 3.14159265358979323846;
inline constexpr double scale = 0.7;

inline constexpr double opacity = 0.2;

inline const color white(255, 255, 255);
inline const color yellow(255, 215, 0);
inline const color red(220, 20, 60);
inline const color orange(255, 140, 0);
inline const color blue(30, 144, 255);
inline const color green(3, 160, 98);

inline const std::map<int, color> colors{
    {0, white}, {1, yellow}, {2, red}, {3, orange}, {4, blue}, {5, green},
};

inline const std::vector<std::vector<int>> coordinates{
    {-1, 1}, {0, 1},   {1, 1},  {-1, 0}, {0, 0},
    {1, 0},  {-1, -1}, {0, -1}, {1, -1}};
