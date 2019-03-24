#include <Windows.h>
#include <vector>
#include <unordered_set>
using namespace std;

class InputStream
{
    private:
        static unordered_set<char> filters;
        static unordered_set<char> pressed;

    public:
        static void addFilter (char filter, string modifier)
        {
            filters.insert(filter);
        }

        static void update()
        {
            pressed.clear();

            for (char c : filters)
                if (GetKeyState(c) & 0x8000)
                    pressed.insert(c);
        }  

        static bool isPressed(char c)
        {
            return (pressed.find(c) != pressed.end());
        }

};