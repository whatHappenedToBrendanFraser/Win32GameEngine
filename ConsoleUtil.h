#include <windows.h>

class ConsoleUtil
{
	public:
		static CONSOLE_SCREEN_BUFFER_INFO getCSBI()
		{
		    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		    CONSOLE_SCREEN_BUFFER_INFO csbi;
		    GetConsoleScreenBufferInfo(consoleHandle, &csbi);

		    return csbi;
		}

		static HANDLE getHandle()
		{
			return GetStdHandle(STD_OUTPUT_HANDLE);
		}

		static void setCursor(short x, short y)
		{
			COORD coord = {x, y};
			SetConsoleCursorPosition(getHandle(), coord);
		}

		static void setColor(int color)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		}

		static void clear()
		{
		    COORD coord = {0, 0};
		    DWORD count;

		    CONSOLE_SCREEN_BUFFER_INFO c = getCSBI();
		    //This fills the buffer with a given character (in this case 32=space).
		    FillConsoleOutputCharacter(getHandle(), (TCHAR) 32, c.dwSize.X * c.dwSize.Y, coord, &count);
		    FillConsoleOutputAttribute(getHandle(), 7, c.dwSize.X * c.dwSize.Y + 1, coord, &count);
		    //This will set our cursor position for the next print statement.
		    SetConsoleCursorPosition(getHandle(), coord);
		}

		static int getWindowWidth()
		{
			return getCSBI().srWindow.Right - getCSBI().srWindow.Left + 1;
		}

		static int getWindowHeight()
		{
			return getCSBI().srWindow.Bottom - getCSBI().srWindow.Top + 1;
		}

	private:
	

};