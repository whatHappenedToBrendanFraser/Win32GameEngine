#include <vector>
#include "Grid.h"

class RenderEngine
{
    private:
        Grid *map;
        int fps;
        int previousTime;
        vector<vector<bool>> findChanges();

    public:
        RenderEngine(Grid *targetMap, int xOff, int yOff);

        void setTarget(Grid *targetMap, int xOff, int yOff); /*redefine enviroment*/
        void render(); /*renders changes*/
        void reset(); /*resets frame*/   

        static int getFps(); /*returns #frames passed / time passed*/     
};
