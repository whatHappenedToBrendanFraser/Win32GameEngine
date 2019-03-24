#include <iostream>
#include <string>
#include <Windows.h>
#include "RenderEngine.h"
#include "Grid.h"
#include "ConsoleUtil.h"
#include "MapUtils.h"
#include "Log.h"

Grid *map;
int xOffset, yOffset;

vector<vector<int>> lastCharFrame;
vector<vector<int>> lastColorFrame;

RenderEngine::RenderEngine(Grid *targetMap, int xOff, int yOff)
{
    map = targetMap;
    xOffset = xOff;
    yOffset = yOff;

}

void RenderEngine::setTarget(Grid *targetMap, int xOff, int yOff)
{
    map = targetMap;
    xOffset = xOff;
    yOffset = yOff;
}

void RenderEngine::reset()
{
    ConsoleUtil::clear();
    /*account for vertical offset*/
    for (int i = 0; i <= yOffset; i++)
        cout << endl;
    string indent (xOffset, ' ');
    
    /*print compressed top down map*/
    int yIndex = 0;
    vector<vector<int>> colorFrame = MapUtils::compressColor(*map);
    for (vector<int> y : MapUtils::compressChar(*map))
    {
        /*account for horizontal offset*/
        cout << indent;

        int currentColor = colorFrame[yIndex][0];
        ConsoleUtil::setColor(currentColor);
        int xIndex = 0;
        for (int x : y)
        {
            if (colorFrame[yIndex][xIndex] != currentColor)
            {
                ConsoleUtil::setColor(colorFrame[yIndex][xIndex]);
                currentColor = colorFrame[yIndex][xIndex];
            }
            cout << (char)x;
            xIndex++;
        }

        ConsoleUtil::setColor(7);
        cout << endl;
        yIndex++;
    }

    lastCharFrame = MapUtils::compressChar(*map);
    lastColorFrame = MapUtils::compressColor(*map);

}

void RenderEngine::render()
{
    vector<vector<bool>> changes = findChanges();
    vector<vector<int>> charFrame = MapUtils::compressChar(*map);
    vector<vector<int>> colorFrame = MapUtils::compressColor(*map);

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (changes[y][x])
            {
                ConsoleUtil::setCursor(x + xOffset, y + yOffset);
                ConsoleUtil::setColor(colorFrame[y][x]);
                cout << (char)charFrame[y][x];
                Log::log({"change", std::to_string(x), std::to_string(y)}, "Render Engine");
            }
        }
    }

    lastCharFrame = MapUtils::compressChar(*map);
    lastColorFrame = MapUtils::compressColor(*map);
}

vector<vector<bool>> RenderEngine::findChanges()
{
    vector<vector<bool>> changes (map->height, vector<bool> (map->width, false));
    
    /*check for changes between top down of map and the  last frame*/
    /*if we find one, we flag it*/ 
    int yIndex = 0;
    for (vector<int> y : MapUtils::compressChar(*map))
    {
        int xIndex = 0;
        for (int x : y)
        {
            if (x != lastCharFrame[yIndex][xIndex])
            {
                changes[yIndex][xIndex] = true;
                Log::log({"change found at:", to_string(xIndex), to_string(yIndex), "from",
                    to_string(lastCharFrame[yIndex][xIndex]), "to", to_string(x)}, "Render Engine");
            }
            xIndex++;
        }

        yIndex++;
    }

    yIndex = 0;
    for (vector<int> y : MapUtils::compressColor(*map))
    {
        int xIndex = 0;
        for (int x : y)
        {
            if (x != lastColorFrame[yIndex][xIndex])
                changes[yIndex][xIndex] = true;
            xIndex++;
        }

        yIndex++;
    }

    return changes;
}