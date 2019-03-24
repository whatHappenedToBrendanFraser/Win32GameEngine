#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "Grid.h"
#include "MapUtils.h"

using namespace std;

class ImgTxt
{
    private:
        ImgTxt()
        {

        }

    public:
        static Grid loadFromFile(string path)
        {
            Grid grid;

            ifstream file (path);
            vector<string> lines (100); // this means the max length of the file is 100 lines;
            string line;
            int x = 0;
            while (std::getline(file, line))
            {
                lines[x] = line;
                x++;
            }
            lines[x] == "eof";

            int width, height;
            vector<vector<int>> variables;

            int y = 0;

            for (string l : lines)
            {
                cout << l << endl;
                if (l.substr(0,3) == "DIM")
                {
                    width = stoi(l.substr(3, l.find("x", 3)-(3)));
                    height = stoi(l.substr(l.find("x", 3)+1));

                    grid = Grid (width, height);
                    grid.resetGrid({NULL}, {NULL});
                }
                else if (l.substr(0, 4) == "VARS")
                {
                    string varLine = l.substr(5);
                    vector<string> varVector;
                    stringstream varSS;
                    string tmpC;
                    for (char c : varLine)
                    {
                        if (c != ',')
                        {
                            tmpC = c;
                            varSS << tmpC;
                        }
                        else
                        {
                            varVector.push_back(varSS.str());
                            varSS.str(string());
                        }
                    }
                    if(varSS.str() != "" || varSS.str() != " ")
                    {
                        varVector.push_back(varSS.str());
                        varSS.str(string());
                    }

                    variables = vector<vector<int>> (varVector.size(), vector<int> (3));

                    for (int x = 0; x < varVector.size(); x++)
                    {
                        //identifier (character)
                        variables [x][0] = (int) varVector[x][0];
                        //character
                        if (varVector[x][2] == 'C')
                        {
                            variables[x][1] = (int)varVector[x][3];
                        }
                        else if (varVector[x][2] == '#')
                        {
                            variables[x][1] = stoi(varVector[x].substr(3, varVector[x].find("/")-3));
                        }
                        else
                        {
                            //log error
                        }
                        //color code
                        variables[x][2] = stoi(varVector[x].substr(varVector[x].find("/") + 1));
                    }
                }
                if(l.find("eof") != string::npos)
                    break;

                if(l[0] == '+')
                {
                    int x = 0;
                    for (char c : l.substr(1))
                    {
                        if (c == ' ')
                            continue;
                        else if (c == '_')
                        {
                            grid.charGrid[0][y][x] = NULL;
                            grid.colorGrid[0][y][x] = NULL;
                        }
                        else 
                        {
                            for (int i = 0; i < variables.size(); i++)
                            {
                                if ((int)c == variables[i][0])
                                {
                                    grid.charGrid[0][y][x] = variables[i][1];
                                    grid.colorGrid[0][y][x] = variables[i][2];
                                }
                            }
                        }
                        x++;
                    }
                    y++;    
                }
            }
            MapUtils::print(grid);
        }
};