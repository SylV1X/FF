#include <windows.h>

#include "GameObject.hpp"
#include "Level.hpp"
#include "Map.hpp"
#include "MovingObject.hpp"
#include "Player.hpp"
#include "Section.hpp"
#include "Sprite.hpp"

int main()
{
	ssY::GameObject* blocks = nullptr;
	ssY::Sprite* sprites = nullptr;
	ssY::Player player;
	ssY::Level level;
	
	ssY::Map map;
	
	int sprites_count = 0;
	int blocks_count = 0;	

	int score = 0;
	
	level.create_level(player, blocks, blocks_count, sprites, sprites_count, score);

	do
	{
		player.jump();
		
		if (GetKeyState('A') < 0) {
			map.scroll_map(1, player, blocks, blocks_count, sprites, sprites_count);
		}
		
		if (GetKeyState('D') < 0) {
			map.scroll_map(-1, player, blocks, blocks_count, sprites, sprites_count);
		}
		
		if (player.vertical_move_object(
				level, 
				blocks, blocks_count, 
				sprites, sprites_count)
			) {
			level.next_level(
					player, 
					blocks, blocks_count, 
					sprites, sprites_count, 
					score
				);
			}
	
		for (int i = 0; i < sprites_count; i++)
		{
			sprites[i].horizontal_move_object(sprites[i], blocks, blocks_count);
			sprites[i].vertical_move_object(blocks, blocks_count);
		}

		if (player.get_y() > map.get_map_height()) { 
			level.restart_level(
					player, 
					blocks, blocks_count, 
					sprites, sprites_count, 
					score
				);
		}
		
		if (player.player_collision_model(level, sprites, sprites_count, score)) {
			level.restart_level(
					player, 
					blocks, blocks_count, 
					sprites, sprites_count, 
					score
				);
		}
		
		map.clear_map();
		
		for (int i = 0; i < blocks_count; i++) {
			map.add_object_on_map(blocks[i]);
		}
		for (int i = 0; i < sprites_count; i++) {
			map.add_object_on_map(sprites[i]);
		}
		
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
