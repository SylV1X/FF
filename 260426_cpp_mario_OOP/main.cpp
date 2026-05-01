#include <iostream>
#include <windows.h>

class Map
{
	private:
		static const int MAP_HEIGHT = 40;
		static const int MAP_WIDTH = 80;
		char map[MAP_HEIGHT][MAP_WIDTH + 1];
		
	public:
		void clear_map()
		{
			for (int i = 0; i < MAP_WIDTH; i++)
				map[0][i] = '.';
			map[0][MAP_WIDTH] = '\0';
			for (int j = 1; j < MAP_HEIGHT; j++)
				for (int k = 0; k < MAP_WIDTH + 1; k++)
					map[j][k] = map[0][k];
		}
		
		void show_map()
		{
			COORD coord = { 0, 0 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			for (int j = 0; j < MAP_HEIGHT; j++)
				std::cout << map[j] << '\n';
		}
};

int main()
{
	Map map;
	map.clear_map();
	map.show_map();
	return 0;
}