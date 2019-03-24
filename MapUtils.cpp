#include <vector>
#include <iostream>
#include "Grid.h"
#include "MapUtils.h"
#include "ConsoleUtil.h"

using namespace std;

MapUtils::MapUtils()
{

}

void MapUtils::print(Grid map)
{
    int z_ = 0;
    for (vector<vector<int>> z : map.charGrid)
    {
        int y_ = 0;
        cout << "\n--layer--\n"; 
        for (vector<int> y : z)
        {
            int x_ = 0;
            for (int x : y)
            {
                if (x == NULL)
                {
                    if(map.colorGrid[z_][y_][x_] != NULL)
                        ConsoleUtil::setColor(map.colorGrid[z_][y_][x_]);
                    cout << "(NULL)";
                    ConsoleUtil::setColor(15);

                }
                else
                {
                    if(map.colorGrid[z_][y_][x_] != NULL)
                        ConsoleUtil::setColor(map.colorGrid[z_][y_][x_]);
                    cout << "  " << (char)x << "   ";
                    ConsoleUtil::setColor(15);
                }
                x_++;
            }
            y_++;
            cout << endl;
        }
        z_++;
    }
    
}

vector<vector<int>> MapUtils::compressChar(Grid map)
{
    vector<vector<int>> charFrame(map.height, vector<int> (map.width, NULL));
    for (int z = map.depth - 1; z >= 0; z--)
    {
        for (int y = 0; y < map.height; y++)
        {
            for (int x = 0; x < map.width; x++)
            {
                if (charFrame[y][x] == NULL && map.charGrid[z][y][x] != NULL)
                    charFrame[y][x] = map.charGrid[z][y][x];
            }
        }
    }

    return charFrame;
}

vector<vector<int>> MapUtils::compressColor(Grid map)
{
    vector<vector<int>> colorFrame(map.height, vector<int> (map.width, NULL));
    for (int z = map.depth - 1; z >= 0; z--)
    {
        for (int y = 0; y < map.height; y++)
        {
            for (int x = 0; x < map.width; x++)
            {
                if (colorFrame[y][x] == NULL && map.colorGrid[z][y][x] != NULL)
                    colorFrame[y][x] = map.colorGrid[z][y][x];
            }
        }
    }

    return colorFrame;
}

void MapUtils::clearZ (Grid *grid, int z)
{
    grid->charGrid[z] = vector<vector<int>> (grid->height, vector<int> (grid->width, NULL));
    grid->colorGrid[z] = vector<vector<int>> (grid->height, vector<int> (grid->width, NULL));
}

void MapUtils::move