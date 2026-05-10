#include <windows.h>

#include "Player.hpp"

using ssY::Player;

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