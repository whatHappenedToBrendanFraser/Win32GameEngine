#include <iostream>
// #include <stdlib.h>     /* srand, rand */
#include <string> 
#include <chrono>
#include "Grid.h"
#include "RenderEngine.h"
#include "MapUtils.h"
#include "ConsoleUtil.h"
#include "Graphics.h"
#include "ImgTxt.h"
#include "InputStream.h"
#include "Player.h"
#include "Log.h"

using namespace std;

int main ()
{
    Grid grid(100, 25, 4);
    grid.resetGrid(
        {176 , NULL, NULL, NULL},
        {8, NULL, NULL, 30}
    );

    RenderEngine renderer(&grid, 25, 3);
    renderer.reset();

    Player p = Player(1, 1, 1);
    InputStream::update();

    // grid.charGrid[2][5][10] = 178;
    // grid.colorGrid[2][5][10] = 16;

    Graphics::drawSquare(&grid, Graphics::point(2,2,1), Graphics::point(15,9,1), 176, 177, 7,7);
    Graphics::setText(&grid, Graphics::point(grid.left, grid.bottom - 2), "Hello, this is test text.");

    while (1)
    {
        InputStream::update();
        
        renderer.render();
    }
    
    return 0;
}

//// ImgTxt::loadFromFile("imgtxt\\test1.txt");
    // while (true)
    // {
    //     renderer.render();
    // }
    // grid.charGrid[1][1][1] = 133;
    // grid.colorGrid[1][1][1] = 20;

    // grid.colorGrid[2][5][3] = 20;
    // grid.charGrid[2][6][1] = 133;

    // srand(time(NULL));
    // while (1)
    // {
    //     int color = rand() % (200) + 1;
    //     int chara = rand() % 200 + 1;
    //     int x = rand() % 49 + 1;
    //     int y = rand() % 24 + 1;

    //     grid.colorGrid[2][y][x] = color;
    //     grid.charGrid[2][y][x] = chara;

    //     renderer.render();

        // ConsoleUtil::setColor(color);
        // cout << (char)chara << endl;

    // }