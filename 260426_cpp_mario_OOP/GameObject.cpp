#include "GameObject.hpp"

#include <cmath>

using ssY::GameObject;

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