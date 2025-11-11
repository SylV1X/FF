#include <cstdlib>
#include <iostream>

#include "menu_functions.hpp"

const ssY::MenuItem* ssY::show_menu(const MenuItem* current)
{
	std::cout << "Hello!" << std::endl;
	for (int i = 1; i < current->children_count; i++)
	{	
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Study_app >> ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}

const ssY::MenuItem* ssY::exit(const MenuItem* current)
{
	std::exit(0);
}

const ssY::MenuItem* ssY::sum(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ssY::MenuItem* ssY::substract(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ssY::MenuItem* ssY::multiply(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ssY::MenuItem* ssY::divide(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ssY::MenuItem* ssY::go_back(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent->parent;
}
