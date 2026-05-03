#include <iostream>
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <sstream>

class GameObject
{
	protected:
		float x, y;
		float height, width;
		char kind;
		friend class Map;

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
		
		void set_x(float new_x){ x = new_x; }		
		void set_kind(char new_kind){ kind = new_kind; }
};

class MovingObject: public GameObject
{
	protected:
		float vertical_speed;
		float horizontal_speed;
		bool isFly;
		
	public:
		void init_object(float init_x, float init_y, float init_width, float init_height, char init_kind)
		{
			GameObject::init_object(init_x, init_y, init_width, init_height, init_kind);
			vertical_speed = 0;
			horizontal_speed = 0.2;
		}

		float get_vertical_speed() const { return vertical_speed; }
		float get_horizontal_speed() const { return horizontal_speed; }
		bool get_isFly() const { return isFly; }
		
		void set_vertical_speed(float new_vertical_speed){ vertical_speed = new_vertical_speed; }
};

class Sprite: public MovingObject
{
	public:
		bool vertical_move_object(GameObject*& background_elems, int background_elems_count) 
		{
			isFly = true;
			vertical_speed += 0.05;
			GameObject::set_object_pos(x, y + vertical_speed);
			for (int i = 0; i < background_elems_count; i++)
			{
				if (check_collision(background_elems[i]))
				{
					if (vertical_speed > 0) isFly = false;
					y -= vertical_speed;
					vertical_speed = 0;
					isFly = false;
				}
			}
			return false;
		}
		
		void horizontal_move_object(Sprite& obj, GameObject*& background_elems, int background_elems_count)
		{
			obj.set_x(obj.get_x() + horizontal_speed);
			
			for (int i = 0; i < background_elems_count; i++)
				if (check_collision(background_elems[i]))
				{
					obj.set_x(obj.get_x() - horizontal_speed);
					horizontal_speed = -horizontal_speed;
					return;
				}
			
			if (obj.get_kind() == 'o')
			{
				Sprite tmp = obj;
				tmp.vertical_move_object(background_elems, background_elems_count);
				if (tmp.get_isFly())
				{
					obj.set_x(obj.get_x() - horizontal_speed);
					horizontal_speed = -horizontal_speed;	
				}
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
				map[0][i] = ' ';
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
			int int_x = (int)round(obj.x);
			int int_y = (int)round(obj.y);
			int int_width = (int)round(obj.width);
			int int_height = (int)round(obj.height);
			
			for (int i = int_x; i < (int_x + int_width); i++)
				for (int j = int_y; j < (int_y + int_height); j++)
					if (object_within_map(i, j))
						map[j][i] = obj.kind;
		}
		
		void scroll_map(float dx, GameObject& player, GameObject*& background_elems, int background_elems_count, Sprite*& sprites, int& sprites_count)
		{
			player.set_x(player.x - dx);
			for (int i = 0; i < background_elems_count; i++)
				if (player.check_collision(background_elems[i]))
				{
					player.set_x(player.x + dx);
					return;
				}
			player.set_x(player.x + dx);
			for (int i = 0; i < background_elems_count; i++)
				background_elems[i].set_x(background_elems[i].x + dx);
			for (int i = 0; i < sprites_count; i++)
				sprites[i].set_x(sprites[i].x + dx);
		}
		
		void show_score(int score)
		{
			std::ostringstream ss;
			ss << "Score: " << score;
			std::string text = ss.str();
			for (int i = 0; i < text.length(); i++)
				map[1][i + 5] = text[i];
		}
		
		float get_MAP_HEIGHT() const { return MAP_HEIGHT; }
};

class Level
{
	private:
		int current_level = 1;
		int max_level = 3;
		
	public:
		void add_new_background_elem(GameObject*& background_elems, int& background_elems_count, float x, float y, float height, float width, char kind)
		{
			GameObject* background_elems_update = new GameObject[background_elems_count + 1];
			for (int i = 0; i < background_elems_count; i++)
				background_elems_update[i] = background_elems[i];
			delete[] background_elems;
			background_elems = background_elems_update;
			background_elems[background_elems_count].init_object(x, y, height, width, kind);
			background_elems_count++;
		}
		
		void delete_background_elems(GameObject*& background_elems, int& background_elems_count)
		{
			delete[] background_elems;
			background_elems = nullptr;
			background_elems_count = 0;
		}
		
		void add_new_sprite(Sprite*& sprites, int& sprites_count, float x, float y, float height, float width, char kind)
		{
			Sprite* sprites_update = new Sprite[sprites_count + 1];
			for (int i = 0; i < sprites_count; i++)
				sprites_update[i] = sprites[i];
			delete[] sprites;
			sprites = sprites_update;
			sprites[sprites_count].init_object(x, y, height, width, kind);
			sprites_count++;
		}
		
		void delete_sprites(Sprite*& sprites, int& sprites_count)
		{
			delete[] sprites;
			sprites = nullptr;
			sprites_count = 0;
		}		
		
		void remove_sprite(int index, Sprite*& sprites, int& sprites_count)
		{
			sprites_count--;
			sprites[index] = sprites[sprites_count];

			if (sprites_count == 0)
			{
				delete[] sprites;
				sprites = nullptr;
			}
			else
			{
				Sprite* sprites_update = new Sprite[sprites_count];
				for (int i = 0; i < sprites_count; i++)
					sprites_update[i] = sprites[i];
				delete[] sprites;
				sprites = sprites_update;
			}
		}
		
		void create_level(GameObject& player, GameObject*& background_elems, int& background_elems_count, Sprite*& sprites, int& sprites_count, int& score)
		{
			system("color 9F");
			
			delete_background_elems(background_elems, background_elems_count);
			background_elems = nullptr;
			background_elems_count = 0;
			
			delete_sprites(sprites, sprites_count);
			sprites = nullptr;
			sprites_count = 0;

			player.init_object(39, 10, 3, 3, '@');
			score = 0;
			
			if (current_level == 1)
			{
				add_new_background_elem(background_elems, background_elems_count, 20, 20, 40, 5, '#');		
				add_new_background_elem(background_elems, background_elems_count, 60, 15, 40, 10, '#');
				add_new_background_elem(background_elems, background_elems_count, 100, 20, 20, 5, '#');
				add_new_background_elem(background_elems, background_elems_count, 120, 15, 10, 10, '#');
				add_new_background_elem(background_elems, background_elems_count, 150, 20, 40, 5, '#');
				add_new_background_elem(background_elems, background_elems_count, 30, 10, 5, 3, '?');
				add_new_background_elem(background_elems, background_elems_count, 50, 10, 5, 3, '?');
				add_new_background_elem(background_elems, background_elems_count, 70, 5, 5, 3, '?');
				add_new_background_elem(background_elems, background_elems_count, 80, 5, 5, 3, '?');
				add_new_background_elem(background_elems, background_elems_count, 60, 5, 10, 3, '-');
				add_new_background_elem(background_elems, background_elems_count, 75, 5, 5, 3, '-');
				add_new_background_elem(background_elems, background_elems_count, 85, 5, 10, 3, '-');
				add_new_background_elem(background_elems, background_elems_count, 210, 15, 10, 10, '+');
				
				add_new_sprite(sprites, sprites_count, 25, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 80, 10, 3, 2, 'o');	
			}
			
			if (current_level == 2)
			{
				add_new_background_elem(background_elems, background_elems_count, 20, 20, 40, 5, '#');
				add_new_background_elem(background_elems, background_elems_count, 60, 15, 10, 10, '#');
				add_new_background_elem(background_elems, background_elems_count, 80, 20, 20, 5, '#');
				add_new_background_elem(background_elems, background_elems_count, 120, 15, 10, 10, '#');
				add_new_background_elem(background_elems, background_elems_count, 150, 20, 40, 5, '#');
				add_new_background_elem(background_elems, background_elems_count, 210, 15, 10, 10, '+');
				
				add_new_sprite(sprites, sprites_count, 25, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 80, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 65, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 120, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 160, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 175, 10, 3, 2, 'o');
			}
			
			if (current_level == 3)
			{
				add_new_background_elem(background_elems, background_elems_count, 20, 20, 40, 5, '#');
				add_new_background_elem(background_elems, background_elems_count, 80, 20, 15, 5, '#');
				add_new_background_elem(background_elems, background_elems_count, 120, 15, 15, 10, '#');
				add_new_background_elem(background_elems, background_elems_count, 160, 10, 15, 15, '+');
				
				add_new_sprite(sprites, sprites_count, 25, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 50, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 80, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 90, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 120, 10, 3, 2, 'o');
				add_new_sprite(sprites, sprites_count, 130, 10, 3, 2, 'o');
			}
		}
		
		void next_level(GameObject& player, GameObject*& background_elems, int& background_elems_count, Sprite*& sprites, int& sprites_count, int& score)
		{
			current_level++;
			if (current_level > max_level)
				current_level = 1;
			
			system("color 2F");
			Sleep(500);
			create_level(player, background_elems, background_elems_count, sprites, sprites_count, score);
		}
		
		void restart_level(GameObject& player, GameObject*& background_elems, int& background_elems_count, Sprite*& sprites, int& sprites_count, int& score)
		{
			system("color 4F");
			Sleep(500);
			create_level(player, background_elems, background_elems_count, sprites, sprites_count, score);
		}
		
		float get_level_num() const { return current_level; }
		void set_level_num(float new_num){ current_level = new_num; }
};

class Player: public MovingObject
{
	public:
		void jump()
		{
			if (!isFly && GetKeyState(VK_SPACE) < 0) 
				 vertical_speed = -1;
		}
		
		bool vertical_move_object(Level& level, GameObject*& background_elems, int background_elems_count, Sprite*& sprites, int& sprites_count)
		{
			isFly = true;
			vertical_speed += 0.05;
			GameObject::set_object_pos(x, y + vertical_speed);
			for (int i = 0; i < background_elems_count; i++)
			{
				if (check_collision(background_elems[i]))
				{
					if (vertical_speed > 0) isFly = false;
										
					if ((background_elems[i].get_kind() == '?') && (vertical_speed < 0))
					{
						background_elems[i].set_kind('-');
						level.add_new_sprite(sprites, sprites_count, background_elems[i].get_x(), background_elems[i].get_y() - 3, 3, 2, '$');
						sprites[sprites_count - 1].set_vertical_speed(sprites[sprites_count - 1].get_vertical_speed() - 0.7);
					}
					
					y -= vertical_speed;
					vertical_speed = 0;
	
					if (background_elems[i].get_kind() == '+') return true; 
					// Внук имеет доступ к полю protected Деда только для this, для других объектов - нет, поэтому использовать геттер.
				}
			}
			return false;
		}
		
		bool player_collision_model(Level& level, Sprite*& sprites, int& sprites_count, int& score)
		{
			for (int i = 0; i < sprites_count; i++)
				if (check_collision(sprites[i]))
				{
					if (sprites[i].get_kind() == 'o')
					{
						if (isFly == true
							&& vertical_speed > 0
							&& y + height < sprites[i].get_y() + sprites[i].get_height() * 0.5)
						{
							score += 50;
							level.remove_sprite(i, sprites, sprites_count);
							i--;
							continue;
						}
						else
							return true;
					}
					
					if (sprites[i].get_kind() == '$')
					{
						score += 100;
						level.remove_sprite(i, sprites, sprites_count);
						i--;
						continue;
					}
				}
			return false;
		}		
};

class Game
{
	private:
		GameObject* background_elems;
		Sprite* sprites;
		Player player;
		Level level;
		
		Map map;
		
		int sprites_count;
		int background_elems_count;	

		int score;
		
		void player_position()
		{
			player.jump();
			
			if (GetKeyState('A') < 0) map.scroll_map(1, player, background_elems, background_elems_count, sprites, sprites_count);
			
			if (GetKeyState('D') < 0) map.scroll_map(-1, player, background_elems, background_elems_count, sprites, sprites_count);
			
			if (player.vertical_move_object(level, background_elems, background_elems_count, sprites, sprites_count)) level.next_level(player, background_elems, background_elems_count, sprites, sprites_count, score);
		}
		
		void sprites_position()
		{
			for (int i = 0; i < sprites_count; i++)
			{
				sprites[i].horizontal_move_object(sprites[i], background_elems, background_elems_count);
				sprites[i].vertical_move_object(background_elems, background_elems_count);
			}
		}
		
		void death_check()
		{
		if (player.get_y() > map.get_MAP_HEIGHT()) level.restart_level(player, background_elems, background_elems_count, sprites, sprites_count, score);
		
		if (player.player_collision_model(level, sprites, sprites_count, score)) level.restart_level(player, background_elems, background_elems_count, sprites, sprites_count, score);
		}
		
		void new_frame()
		{
			player_position();
			sprites_position();
			death_check();
		}
		
		void rendering()
		{	
			map.clear_map();
			
			for (int i = 0; i < background_elems_count; i++)
				map.add_object_on_map(background_elems[i]);
			for (int i = 0; i < sprites_count; i++)
				map.add_object_on_map(sprites[i]);
			
			map.add_object_on_map(player);
			map.show_score(score);
			map.show_map();
		}
	public:
		Game()
		{
			background_elems = nullptr;
			sprites = nullptr;
			background_elems_count = 0;
			sprites_count = 0;
			score = 0;
			
			level.create_level(player, background_elems, background_elems_count, sprites, sprites_count, score);
		}
		~Game()
		{
			delete[] background_elems;
			background_elems = nullptr;
			delete[] sprites;
			sprites = nullptr;
		}
		
		Game(const Game& x) = delete;
		Game(Game&& x) = delete;
		Game& operator = (const Game& x) = delete;
		Game& operator = (Game&& x) = delete;
		
		void run()
		{
			do
			{
				new_frame();
				rendering();
				Sleep(10);
			}
			while (GetKeyState(VK_ESCAPE) >= 0);
		}
};


int main()
{
	Game game;
	game.run();
	return 0;
}
