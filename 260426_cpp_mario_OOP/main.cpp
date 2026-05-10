#include <cstdlib>
#include <windows.h>

#include "GameObject.hpp"
#include "Level.hpp"
#include "Map.hpp"
#include "MovingObject.hpp"
#include "Sprite.hpp"
#include "Section.hpp"

using namespace ssY;

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
