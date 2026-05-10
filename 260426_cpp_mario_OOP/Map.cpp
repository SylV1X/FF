#include <cmath>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "Map.hpp"

using ssY::Map;

void Map::add_object_on_map(const GameObject& obj)
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
	player.set_x(player.get_x() - dx);
	for (int i = 0; i < blocks_count; i++)
		if (player.check_collision(blocks[i]))
		{
			player.set_x(player.get_x() + dx);
			return;
		}
	player.set_x(player.get_x() + dx);
	for (int i = 0; i < blocks_count; i++)
		blocks[i].set_x(blocks[i].get_x() + dx);
	for (int i = 0; i < sprites_count; i++)
		sprites[i].set_x(sprites[i].get_x() + dx);
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