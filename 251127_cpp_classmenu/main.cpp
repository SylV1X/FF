#include <iostream>

#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_func.hpp"

int main()
{
	const ssY::MenuItem* current = &ssY::MAIN;
	do
	{
		current = current->func(current);
	}
	while (true);
	
	return 0;
}