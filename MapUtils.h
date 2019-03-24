#pragma once

#include <vector>
#include "Grid.h" 

class MapUtils
{
    private:
        MapUtils();
    public:
        static void print(Grid map); /*for debugging a grid, not for rendering*/
        static vector<vector<int>> compressChar(Grid map);/*get 2d top down representation of map*/
        static vector<vector<int>> compressColor(Grid map);
        static void clearZ (Grid *grid, int z);

};