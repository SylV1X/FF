#pragma once

#include "menu.hpp"

namespace ssY
{	
	const MenuItem* show_menu(const MenuItem* current);
	const MenuItem* exit(const MenuItem* current);
	
	const MenuItem* pushkin(const MenuItem* current);
	
	const MenuItem* dubrovsky(const MenuItem* current);
	const MenuItem* onegin(const MenuItem* current);
	const MenuItem* winter_evening(const MenuItem* current);
	const MenuItem* go_back(const MenuItem* current);
}