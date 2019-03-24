#pragma once
#include "Grid.h"
#include <math.h>

class Graphics
{
    private:
        Graphics();
    public:
        enum direction {up, down, left, right};

        struct point 
        {
            int x, y, z;
            point(int x1, int y1){x = x1; y = y1;z = 0;}
            point(int x1, int y1, int z1){x = x1; y = y1;z = z1;}
            point(){}
        };

        struct line
        {
            point p1, p2;
            line(point _p1, point _p2){p1 = _p1;p2 = _p2;}
            line(int x1, int y1, int x2, int y2){p1 = point(x1, y1);p2 = point(x2, y2);}
            line(){}
        };

        struct square
        {
            point p1, p2;
            square(point _p1, point _p2){p1 = _p1;p2 = _p2;}
            square(int x1, int y1, int x2, int y2){p1 = point(x1, y1);p2 = point(x2, y2);}
            square(){}
        };

        static void drawLine(Grid *grid, line l, int z)
        {
            //not functional
            int xDiff, yDiff;
            direction yDir;
            int hRate, vRate;

            yDir = l.p1.y-l.p2.y > 1? up:down;
            xDiff = l.p2.x-l.p1.x;
            yDiff = abs(l.p1.y-l.p2.y);

            if (xDiff > yDiff)
            {
                hRate = ceil((double)xDiff / yDiff);
                vRate = 1;
            }
            else if (yDiff > xDiff)
            {
                vRate = ceil((double)yDiff / xDiff);
                hRate = 1;               
            }
            else 
            {
                hRate = 1;
                vRate = 1;
            }

            point cursor (l.p1.x, l.p1.y);


        }

        static void drawSquare(Grid *grid, point p1, point p2, int lineChar, int fillChar, int lineColor, int fillColor)
        {
            /*
                if fillColor or fillChar is null, no fill.
                */

            for (int y = p1.y; y <= p2.y; y++)
            {
                for (int x = p1.x; x <= p2.x; x++)
                {
                    if (y == p1.y || y == p2.y || x == p1.x || x == p2.x)   
                    {
                        grid->charGrid[p1.z][y][x] = lineChar;
                        grid->colorGrid[p1.z][y][x] = lineColor;
                    }
                    else if (fillChar != NULL || fillColor != NULL)
                    {
                        grid->charGrid[p1.z][y][x] = fillChar;
                        grid->colorGrid[p1.z][y][x] = fillColor;
                    }
                }
            }  

        }

        static void setText(Grid *grid, point origin, std::string text)
        {
            for (int i = 0; i < text.length(); i++)
                grid->charGrid[origin.z][origin.y][origin.x+ i] = text[i];
        }
};