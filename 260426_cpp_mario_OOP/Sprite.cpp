#include "Sprite.hpp"

using ssY::Sprite;

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
	
	if (obj.get_kind() == 'o')
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
