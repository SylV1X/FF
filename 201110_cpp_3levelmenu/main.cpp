#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_functions.hpp"

int main()
{
	std::setlocale(LC_ALL, "");
	
	ssY::MenuItem sum = { "1 - Summa", ssY::sum };
	ssY::MenuItem substract = { "2 - Substaction", ssY::substract };
	ssY::MenuItem multiply = { "3 - Multiply", ssY::multiply };
	ssY::MenuItem divide = { "4 - Divide", ssY::divide };
	ssY::MenuItem go_back = { "0 - Back", ssY::go_back };
	
	ssY::MenuItem* study_children[] = {
		&go_back,
		&sum,
		&substract,
		&multiply,
		&divide,
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
	
	ssY::MenuItem study = { "1 - Math!", ssY::study };
	ssY::MenuItem exit = { "0 - Sleep(", ssY::exit };
	
	ssY::MenuItem* main_children[] = { &exit, &study};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
	
	int user_input;
	do
	{
		std::cout << "Hello!" << std::endl;
		for (int i = 1; i < main_size; i++)
		{	
			std::cout << main_children[i]->title << std::endl;
		}
		std::cout << main_children[0]->title << std::endl;
		std::cout << "Study_app >> " << std::endl;
		
		std::cin >> user_input;
		main_children[user_input]->func();
		
		std::cout << std::endl;
	}
	while (true);
	
	return 0;
}