#include <windows.h>

#include "Level.hpp"

using ssY::Level;

void Level::add_new_block(
	GameObject*& blocks, int& blocks_count, 
	float x, float y, 
	float height, float width, 
	char kind
) {
	GameObject* blocks_update = new GameObject[blocks_count + 1];
	for (int i = 0; i < blocks_count; i++) {
		blocks_update[i] = blocks[i];
	}
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
	for (int i = 0; i < sprites_count; i++) {
		sprites_update[i] = sprites[i];
	}
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
	if (current_level > max_level) {
		current_level = 1;
	}
	
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