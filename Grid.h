#pragma once
#include <vector>
#include <iostream>

using namespace std;

struct Grid
{
    int width, height, depth; /*z,y,x*/
    vector<vector<vector<int>>> charGrid;
    vector<vector<vector<int>>> colorGrid;
    vector<int> charNormal;
    vector<int> colorNormal;

    int bottom, top, right, left;

    Grid(int x, int y) /*for 2d grid (sprites, ect.)*/
    {
        width = x;
        height = y;
        depth = 1;
    }

    Grid(int x, int y, int z)
    {
        width = x;
        height = y;
        depth = z;
    }

    Grid(){}

    void resetGrid(vector<int> newCharNormal, vector<int> newColorNormal)
    {
        /*initializes grid with correct defaults (normals)*/
        /*must be called after initialization of grid*/
        bottom = height - 1;
        top = 0;
        right = width - 1;
        left = 0;

        charNormal = newCharNormal;
        colorNormal = newColorNormal;

        charGrid = vector<vector<vector<int>>> (depth);
        colorGrid = vector<vector<vector<int>>> (depth);

        /*only first layer is initialized to it's normal*/
        /*create first layer*/
        vector<vector<int>> charLayer (height);
        vector<vector<int>> colorLayer (height);

        for (int i = 0; i < height; i++)
        {
            vector<int> charRow (width);
            vector<int> colorRow (width);
            fill(charRow.begin(), charRow.end(), charNormal[0]);
            fill(colorRow.begin(), colorRow.end(), colorNormal[0]);
            charLayer[i] = charRow;
            colorLayer[i] = colorRow;
        }

        charGrid[0] = charLayer;
        colorGrid[0] = colorLayer;

        if(depth > 1)
        {
            /*initialize rest of layers to NULL*/
            for (int z = 1; z < depth; z++)
            {     
                for (int y = 0; y < height; y++)
                {
                    vector<int> charRow (width);
                    vector<int> colorRow (width);
                    fill(charRow.begin(), charRow.end(), NULL);
                    fill(colorRow.begin(), colorRow.end(), NULL);
                    charLayer[y] = charRow;
                    colorLayer[y] = colorRow;
                }
                    
                charGrid[z] = charLayer;
                colorGrid[z] = colorLayer;
            }
        }
    }
};