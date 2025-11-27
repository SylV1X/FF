#include <cstdlib>
#include <iostream>

#include "menu_func.hpp"
namespace
{
	const ssY::MenuItem* menu(const ssY::MenuItem* current)
	{
		for (int i = 1; i < current->children_amount; i++)
		{	
			std::cout << current->children[i]->name << std::endl;
		}
		
		std::cout << current->children[0]->name << std::endl;
		std::cout << "Читаем >> ";
		
		int user_input;
		std::cin >> user_input;
		std::cout << std::endl;
		
		return current->children[user_input];
	}
}
const ssY::MenuItem* ssY::exit(const MenuItem* current)
{
	std::exit(0);
}

const ssY::MenuItem* ssY::go_back(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent->parent;
}
const ssY::MenuItem* ssY::pushkin(const MenuItem* current)
{
	std::cout << "Что читаем?" << std::endl;
	return menu(current);
}
const ssY::MenuItem* ssY::show_menu(const MenuItem* current)
{
	std::cout << "Кого читаем? " << std::endl;
	return menu(current);
}

const ssY::MenuItem* ssY::dubrovsky(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent;
}
const ssY::MenuItem* ssY::onegin(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent;
}
const ssY::MenuItem* ssY::winter_evening(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent;
}