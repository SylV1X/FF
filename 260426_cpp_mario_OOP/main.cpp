#include <cstdlib>
#include <windows.h>

#include "GameObject.hpp"
#include "Map.hpp"
#include "MovingObject.hpp"
#include "Sprite.hpp"
#include "Section.hpp"

using namespace ssY;

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
