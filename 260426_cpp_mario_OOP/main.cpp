#include <iostream>
#include <windows.h>
#include <math.h>

class GameObject
{
	public:
		float x, y;
		float height, width;
		char kind;
		
		GameObject()
		{
			this->x = 0;
			this->y = 0;
			this->height = 0;
			this->width = 0;
			this->kind = ' '
		}
		
		GameObject(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
		
		void set_object_pos(float obj_pos_x, float obj_pos_y)
		{
			this->x = obj_pos_x;
			this->y = obj_pos_y;
		}
		
		void init_object(float init_x, float init_y, float init_width, float init_height, char init_kind)
		{
			set_object_pos(init_x, init_y);
			this->width = init_width;
			this->height = init_height;
			this->kind = init_kind;
		}
};

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
		
		void add_object_on_map(const GameObject& obj)
		{
			int int_x = (int)round(obj.x);
			int int_y = (int)round(obj.y);
			int int_width = (int)round(obj.width);
			int int_height = (int)round(obj.height);

			for (int i = int_x; i < (int_x + int_width); i++)
				for (int j = int_y; j < (int_y + int_height); j++)
					map[j][i] = obj.kind;
		}
};

int main()
{
	Map map;
	GameObject mario;
	
	mario.init_object(39, 10, 3, 3, '@');
	map.clear_map();
	map.add_object_on_map(mario);
	map.show_map();
	
	return 0;
}