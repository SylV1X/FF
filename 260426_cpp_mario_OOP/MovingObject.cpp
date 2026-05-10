#include "MovingObject.hpp"

float ssY::MovingObject::get_vertical_speed() const { return vertical_speed; }
float ssY::MovingObject::get_horizontal_speed() const { return horizontal_speed; }
bool ssY::MovingObject::get_is_fly() const { return is_fly; }

void ssY::MovingObject::init_object(
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

void ssY::MovingObject::set_vertical_speed(float new_vertical_speed)
	{ vertical_speed = new_vertical_speed; }