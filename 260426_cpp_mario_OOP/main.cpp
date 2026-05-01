#include <iostream>
#include <windows.h>
#include <math.h>

class GameObject
{
	private:
		float x, y;
		float height, width;
		char kind;

	public:		
		GameObject() // for derived
		{
			x = 0;
			y = 0;
			height = 0;
			width = 0;
			kind = ' ';
		}
		
		void set_object_pos(float obj_pos_x, float obj_pos_y)
		{
			x = obj_pos_x;
			y = obj_pos_y;
		}
		
		void init_object(float init_x, float init_y, float init_width, float init_height, char init_kind)
		{
			set_object_pos(init_x, init_y);
			width = init_width;
			height = init_height;
			kind = init_kind;
		}

		bool check_collision(const GameObject& obj)
		{
			return (x +  width) > obj.x
			&& x < (obj.x + obj.width)
			&& (y +  height) > obj.y 
			&& y < (obj.y + obj.height);
		}
		
		float get_x() const { return x; }
		float get_y() const { return y; }
		float get_height() const { return height; }
		float get_width() const { return width; }
		char get_kind() const { return kind; }
};

class MovingObject: public GameObject
{
	private:
		float vertical_speed;
		float horizontal_speed;
		
	public:
		void init_object(float init_x, float init_y, float init_width, float init_height, char init_kind)
		{
			GameObject::init_object(init_x, init_y, init_width, init_height, init_kind);
			vertical_speed = 0;
			horizontal_speed = 0.2;
		}
		
		void vertical_move_object(const GameObject& obj)
		{
			vertical_speed += 0.05;
			float old_y = get_y();
			GameObject::set_object_pos(get_x(), get_y() + vertical_speed);
			
			if (check_collision(obj))
			{
				GameObject::set_object_pos(get_x(), old_y);
				vertical_speed = 0;
			}
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
		
		bool object_within_map(int x, int y)
		{
			return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
		}
		
		void add_object_on_map(const GameObject& obj)
		{
			int int_x = (int)round(obj.get_x());
			int int_y = (int)round(obj.get_y());
			int int_width = (int)round(obj.get_width());
			int int_height = (int)round(obj.get_height());
			
			for (int i = int_x; i < (int_x + int_width); i++)
				for (int j = int_y; j < (int_y + int_height); j++)
					if (object_within_map(i, j))
						map[j][i] = obj.get_kind();
		}
};

int main()
{
	Map map;
	MovingObject player;
	player.init_object(39, 10, 3, 3, '@');
	GameObject background_elem;
	background_elem.init_object(20, 20, 40, 5, '#');
	
	do
	{
		map.clear_map();
		player.vertical_move_object(background_elem);
		map.add_object_on_map(background_elem);
		map.add_object_on_map(player);
		map.show_map();
		
		Sleep(10);
	} 
	while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}