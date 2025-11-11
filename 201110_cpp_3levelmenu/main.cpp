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
	
	ssY::MenuItem study = { "1 - Math!", ssY::show_menu, study_children, study_size };
	ssY::MenuItem exit = { "0 - Sleep(", ssY::exit };
	
	ssY::MenuItem* main_children[] = { &exit, &study};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
	
	ssY::MenuItem main = { nullptr, ssY::show_menu, main_children, main_size };
	
	sum.parent = &study;
	substract.parent = &study;
	multiply.parent = &study;
	divide.parent = &study;
	go_back.parent = &study;
	
	study.parent = &main;
	exit.parent = &main;
	
	const ssY::MenuItem* current = &main;
	do
	{
		current = current->func(current);
	}
	while (true);
	
	return 0;
}