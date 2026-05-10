#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <windows.h>

enum Section : char {
	BOX = '-',
	COIN = '$',
	FINISH = '+',
	FULL_BOX = '?',
	ENEMY = 'o',
	MARIO = '@',
	PLATFORM = '#'
};

class GameObject
{
	protected:
		friend class Map;
		float x, y;
		float height, width;
		char kind;

	public:		
		GameObject();
		
		bool check_collision(const GameObject& obj);
		
		float get_height() const;
		char get_kind() const;
		float get_width() const;
		float get_x() const;
		float get_y() const;
		
		void init_object(
			float init_x, float init_y, 
			float init_width, float init_height, 
			char init_kind
		);
		
		void set_kind(char new_kind);
		void set_object_pos(float obj_pos_x, float obj_pos_y);
		void set_x(float new_x);
};

class MovingObject: public GameObject
{
	protected:
		bool is_fly;
		float horizontal_speed;
		float vertical_speed;

	public:
		bool get_is_fly() const;
		float get_horizontal_speed() const;
		float get_vertical_speed() const;
		
		void init_object(
			float init_x, float init_y, 
			float init_width, float init_height, 
			char init_kind
		);
	
		void set_vertical_speed(float new_vertical_speed);
};

class Sprite: public MovingObject
{
	public:
		void horizontal_move_object(
			Sprite& obj, 
			GameObject*& blocks, int blocks_count
		);	
		bool vertical_move_object(GameObject*& blocks, int blocks_count);
};

class Map
{
	private:
		static const int MAP_HEIGHT = 28;
		static const int MAP_WIDTH = 80;
		char map[MAP_HEIGHT][MAP_WIDTH + 1];
		
	public:
		void add_object_on_map(const GameObject& obj);
		
		void clear_map();
		
		float get_MAP_HEIGHT() const;
		
		bool object_within_map(int x, int y);
		
		void scroll_map(
			float dx, 
			GameObject& player, GameObject*& blocks, 
			int blocks_count, Sprite*& sprites, int& sprites_count
		);
		void show_map();
		void show_score(int score);

};

class Level
{
	private:
		int current_level = 1;
		int max_level = 3;
		
	public:
		void add_new_block(
			GameObject*& blocks, int& blocks_count, 
			float x, float y, 
			float height, float width, 
			char kind
		);
		void add_new_sprite(
			Sprite*& sprites, int& sprites_count, 
			float x, float y, 
			float height, float width, 
			char kind
		);
		
		void create_level(
			GameObject& player, 
			GameObject*& blocks, int& blocks_count, 
			Sprite*& sprites, int& sprites_count, 
			int& score
		);
		
		void delete_blocks(GameObject*& blocks, int& blocks_count);
		void delete_sprites(Sprite*& sprites, int& sprites_count);
		
		float get_level_num() const;
		
		void next_level(
			GameObject& player, 
			GameObject*& blocks, int& blocks_count, 
			Sprite*& sprites, int& sprites_count, 
			int& score
		);
		
		void remove_sprite(int index, Sprite*& sprites, int& sprites_count);
		void restart_level(
			GameObject& player, 
			GameObject*& blocks, int& blocks_count, 
			Sprite*& sprites, int& sprites_count, 
			int& score
		);
		
		void set_level_num(float new_num);
};

class Player: public MovingObject
{
	public:
		void jump();
		
		bool player_collision_model(
			Level& level, 
			Sprite*& sprites, int& sprites_count, 
			int& score
		);
		
		bool vertical_move_object(
			Level& level, 
			GameObject*& blocks, int blocks_count, 
			Sprite*& sprites, int& sprites_count
		);
};

int main()
{
	GameObject* blocks = nullptr;
	Sprite* sprites = nullptr;
	Player player;
	Level level;
	
	Map map;
	
	int sprites_count = 0;
	int blocks_count = 0;	

	int score = 0;
	
	level.create_level(player, blocks, blocks_count, sprites, sprites_count, score);

	do
	{
		player.jump();
		
		if (GetKeyState('A') < 0) 
			map.scroll_map(1, player, blocks, blocks_count, sprites, sprites_count);
		
		if (GetKeyState('D') < 0) 
			map.scroll_map(-1, player, blocks, blocks_count, sprites, sprites_count);
		
		if (player.vertical_move_object(
				level, 
				blocks, blocks_count, 
				sprites, sprites_count)
			) 
			level.next_level(
					player, 
					blocks, blocks_count, 
					sprites, sprites_count, 
					score
				);
	
		for (int i = 0; i < sprites_count; i++)
		{
			sprites[i].horizontal_move_object(sprites[i], blocks, blocks_count);
			sprites[i].vertical_move_object(blocks, blocks_count);
		}

		if (player.get_y() > map.get_MAP_HEIGHT()) 
			level.restart_level(
					player, 
					blocks, blocks_count, 
					sprites, sprites_count, 
					score
				);
		
		if (player.player_collision_model(level, sprites, sprites_count, score)) 
			level.restart_level(
					player, 
					blocks, blocks_count, 
					sprites, sprites_count, 
					score
				);
		
		map.clear_map();
		
		for (int i = 0; i < blocks_count; i++)
			map.add_object_on_map(blocks[i]);
		for (int i = 0; i < sprites_count; i++)
			map.add_object_on_map(sprites[i]);
		
		map.add_object_on_map(player);
		map.show_score(score);
		map.show_map();
		
		Sleep(10);

	} 
	while (GetKeyState(VK_ESCAPE) >= 0);

	delete[] blocks;
	blocks = nullptr;
	delete[] sprites;
	sprites = nullptr;

	return 0;
}

// --------------------------------------------------------------------------------------
// GameObject
// --------------------------------------------------------------------------------------
GameObject::GameObject()
{
	x = 0;
	y = 0;
	height = 0;
	width = 0;
	kind = ' ';
}

bool GameObject::check_collision(const GameObject& obj)
{
	return (x +  width) > obj.x
	&& x < (obj.x + obj.width)
	&& (y +  height) > obj.y 
	&& y < (obj.y + obj.height);
}

float GameObject::get_height() const { return height; }
char GameObject::get_kind() const { return kind; }
float GameObject::get_width() const { return width; }
float GameObject::get_x() const { return x; }
float GameObject::get_y() const { return y; }

void GameObject::init_object(
	float init_x, float init_y, 
	float init_width, float init_height, 
	char init_kind
) {
	set_object_pos(init_x, init_y);
	width = init_width;
	height = init_height;
	kind = init_kind;
}
	
void GameObject::set_kind(char new_kind) { kind = new_kind; }
void GameObject::set_object_pos(float obj_pos_x, float obj_pos_y)
{
	x = obj_pos_x;
	y = obj_pos_y;
}
void GameObject::set_x(float new_x) { x = new_x; }	

// --------------------------------------------------------------------------------------
// MovingObject
// --------------------------------------------------------------------------------------
float MovingObject::get_vertical_speed() const { return vertical_speed; }
float MovingObject::get_horizontal_speed() const { return horizontal_speed; }
bool MovingObject::get_is_fly() const { return is_fly; }

void MovingObject::init_object(
	float init_x, float init_y, 
	float init_width, float init_height, 
	char init_kind
) {
	GameObject::init_object(
		init_x, init_y, 
		init_width, init_height, 
		init_kind
	);
	vertical_speed = 0;
	horizontal_speed = 0.2;
}

void MovingObject::set_vertical_speed(float new_vertical_speed)
	{ vertical_speed = new_vertical_speed; }

// --------------------------------------------------------------------------------------
// Sprite
// --------------------------------------------------------------------------------------
void Sprite::horizontal_move_object(
	Sprite& obj, 
	GameObject*& blocks, int blocks_count
) {
	obj.set_x(obj.get_x() + horizontal_speed);
	
	for (int i = 0; i < blocks_count; i++)
		if (check_collision(blocks[i]))
		{
			obj.set_x(obj.get_x() - horizontal_speed);
			horizontal_speed = -horizontal_speed;
			return;
		}
	
	if (obj.get_kind() == ENEMY)
	{
		Sprite tmp = obj;
		tmp.vertical_move_object(blocks, blocks_count);
		if (tmp.get_is_fly())
		{
			obj.set_x(obj.get_x() - horizontal_speed);
			horizontal_speed = -horizontal_speed;	
		}
	}
}

bool Sprite::vertical_move_object(GameObject*& blocks, int blocks_count) 
{
	is_fly = true;
	vertical_speed += 0.05;
	GameObject::set_object_pos(x, y + vertical_speed);
	for (int i = 0; i < blocks_count; i++)
	{
		if (check_collision(blocks[i]))
		{
			if (vertical_speed > 0) is_fly = false;
			y -= vertical_speed;
			vertical_speed = 0;
			is_fly = false;
		}
	}
	return false;
}

// --------------------------------------------------------------------------------------
// Map
// --------------------------------------------------------------------------------------
void Map::add_object_on_map(const GameObject& obj)
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

void Map::clear_map()
{
	for (int i = 0; i < MAP_WIDTH; i++)
		map[0][i] = ' ';
	map[0][MAP_WIDTH] = '\0';
	for (int j = 1; j < MAP_HEIGHT; j++)
		for (int k = 0; k < MAP_WIDTH + 1; k++)
			map[j][k] = map[0][k];
}

float Map::get_MAP_HEIGHT() const { return MAP_HEIGHT; }

bool Map::object_within_map(int x, int y)
{
	return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
}

void Map::scroll_map(
	float dx, 
	GameObject& player, GameObject*& blocks, 
	int blocks_count, Sprite*& sprites, int& sprites_count
) {
	player.set_x(player.x - dx);
	for (int i = 0; i < blocks_count; i++)
		if (player.check_collision(blocks[i]))
		{
			player.set_x(player.x + dx);
			return;
		}
	player.set_x(player.x + dx);
	for (int i = 0; i < blocks_count; i++)
		blocks[i].set_x(blocks[i].x + dx);
	for (int i = 0; i < sprites_count; i++)
		sprites[i].set_x(sprites[i].x + dx);
}

void Map::show_map()
{
	COORD coord = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int j = 0; j < MAP_HEIGHT; j++)
		std::cout << map[j] << '\n';
}

void Map::show_score(int score)
{
	std::ostringstream ss;
	ss << "Score: " << score;
	std::string text = ss.str();
	for (int i = 0; i < text.length(); i++)
		map[1][i + 5] = text[i];
}

// --------------------------------------------------------------------------------------
// Level
// --------------------------------------------------------------------------------------
void Level::add_new_block(
	GameObject*& blocks, int& blocks_count, 
	float x, float y, 
	float height, float width, 
	char kind
) {
	GameObject* blocks_update = new GameObject[blocks_count + 1];
	for (int i = 0; i < blocks_count; i++)
		blocks_update[i] = blocks[i];
	delete[] blocks;
	blocks = blocks_update;
	blocks[blocks_count].init_object(x, y, height, width, kind);
	blocks_count++;
}

void Level::add_new_sprite(
	Sprite*& sprites, int& sprites_count, 
	float x, float y, 
	float height, float width, 
	char kind
) {
	Sprite* sprites_update = new Sprite[sprites_count + 1];
	for (int i = 0; i < sprites_count; i++)
		sprites_update[i] = sprites[i];
	delete[] sprites;
	sprites = sprites_update;
	sprites[sprites_count].init_object(x, y, height, width, kind);
	sprites_count++;
}

void Level::create_level(
	GameObject& player, 
	GameObject*& blocks, int& blocks_count, 
	Sprite*& sprites, int& sprites_count, 
	int& score
) {
	system("color 9F");
	
	delete_blocks(blocks, blocks_count);
	blocks = nullptr;
	blocks_count = 0;
	
	delete_sprites(sprites, sprites_count);
	sprites = nullptr;
	sprites_count = 0;

	player.init_object(39, 10, 3, 3, MARIO);
	score = 0;
	
	if (current_level == 1)
	{
		add_new_block(blocks, blocks_count, 20, 20, 40, 5, PLATFORM);		
		add_new_block(blocks, blocks_count, 60, 15, 40, 10, PLATFORM);
		add_new_block(blocks, blocks_count, 100, 20, 20, 5, PLATFORM);
		add_new_block(blocks, blocks_count, 120, 15, 10, 10, PLATFORM);
		add_new_block(blocks, blocks_count, 150, 20, 40, 5, PLATFORM);
		add_new_block(blocks, blocks_count, 30, 10, 5, 3, FULL_BOX);
		add_new_block(blocks, blocks_count, 50, 10, 5, 3, FULL_BOX);
		add_new_block(blocks, blocks_count, 70, 5, 5, 3, FULL_BOX);
		add_new_block(blocks, blocks_count, 80, 5, 5, 3, FULL_BOX);
		add_new_block(blocks, blocks_count, 60, 5, 10, 3, BOX);
		add_new_block(blocks, blocks_count, 75, 5, 5, 3, BOX);
		add_new_block(blocks, blocks_count, 85, 5, 10, 3, BOX);
		add_new_block(blocks, blocks_count, 210, 15, 10, 10, FINISH);
		
		add_new_sprite(sprites, sprites_count, 25, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 80, 10, 3, 2, ENEMY);	
	}
	
	if (current_level == 2)
	{
		add_new_block(blocks, blocks_count, 20, 20, 40, 5, PLATFORM);
		add_new_block(blocks, blocks_count, 60, 15, 10, 10, PLATFORM);
		add_new_block(blocks, blocks_count, 80, 20, 20, 5, PLATFORM);
		add_new_block(blocks, blocks_count, 120, 15, 10, 10, PLATFORM);
		add_new_block(blocks, blocks_count, 150, 20, 40, 5, PLATFORM);
		add_new_block(blocks, blocks_count, 210, 15, 10, 10, FINISH);
		
		add_new_sprite(sprites, sprites_count, 25, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 80, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 65, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 120, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 160, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 175, 10, 3, 2, ENEMY);
	}
	
	if (current_level == 3)
	{
		add_new_block(blocks, blocks_count, 20, 20, 40, 5, PLATFORM);
		add_new_block(blocks, blocks_count, 80, 20, 15, 5, PLATFORM);
		add_new_block(blocks, blocks_count, 120, 15, 15, 10, PLATFORM);
		add_new_block(blocks, blocks_count, 160, 10, 15, 15, FINISH);
		
		add_new_sprite(sprites, sprites_count, 25, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 50, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 80, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 90, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 120, 10, 3, 2, ENEMY);
		add_new_sprite(sprites, sprites_count, 130, 10, 3, 2, ENEMY);
	}
}

void Level::delete_blocks(GameObject*& blocks, int& blocks_count)
{
	delete[] blocks;
	blocks = nullptr;
	blocks_count = 0;
}

void Level::delete_sprites(Sprite*& sprites, int& sprites_count)
{
	delete[] sprites;
	sprites = nullptr;
	sprites_count = 0;
}
float Level::get_level_num() const { return current_level; }

void Level::next_level(
	GameObject& player, 
	GameObject*& blocks, int& blocks_count, 
	Sprite*& sprites, int& sprites_count, 
	int& score
) {
	current_level++;
	if (current_level > max_level)
		current_level = 1;
	
	system("color 2F");
	Sleep(500);
	create_level(player, blocks, blocks_count, sprites, sprites_count, score);
}		

void Level::remove_sprite(int index, Sprite*& sprites, int& sprites_count)
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

void Level::restart_level(
	GameObject& player, 
	GameObject*& blocks, int& blocks_count, 
	Sprite*& sprites, int& sprites_count, 
	int& score
) {
	system("color 4F");
	Sleep(500);
	create_level(player, blocks, blocks_count, sprites, sprites_count, score);
}

void Level::set_level_num(float new_num){ current_level = new_num; }

// --------------------------------------------------------------------------------------
// Player
// --------------------------------------------------------------------------------------
void Player::jump()
{
	if (!is_fly && GetKeyState(VK_SPACE) < 0) 
		 vertical_speed = -1;
}

bool Player::player_collision_model(
	Level& level, 
	Sprite*& sprites, int& sprites_count, 
	int& score
) {
	for (int i = 0; i < sprites_count; i++)
		if (check_collision(sprites[i]))
		{
			if (sprites[i].get_kind() == ENEMY)
			{
				if (is_fly == true
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
			
			if (sprites[i].get_kind() == COIN)
			{
				score += 100;
				level.remove_sprite(i, sprites, sprites_count);
				i--;
				continue;
			}
		}
	return false;
}		

bool Player::vertical_move_object(
	Level& level, 
	GameObject*& blocks, int blocks_count, 
	Sprite*& sprites, int& sprites_count
) {
	is_fly = true;
	vertical_speed += 0.05;
	GameObject::set_object_pos(x, y + vertical_speed);
	for (int i = 0; i < blocks_count; i++)
	{
		if (check_collision(blocks[i]))
		{
			if (vertical_speed > 0) is_fly = false;
								
			if ((blocks[i].get_kind() == FULL_BOX) && (vertical_speed < 0))
			{
				blocks[i].set_kind(BOX);
				level.add_new_sprite(
					sprites, sprites_count, 
					blocks[i].get_x(), blocks[i].get_y() - 3, 3, 2, 
					COIN
				);
				sprites[sprites_count - 1].set_vertical_speed(
					sprites[sprites_count - 1].get_vertical_speed() - 0.7
				);
			}
			
			y -= vertical_speed;
			vertical_speed = 0;

			if (blocks[i].get_kind() == FINISH) return true; 
		}
	}
	return false;
}
