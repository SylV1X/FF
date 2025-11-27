#pragma once

namespace ssY
{
	struct MenuItem
	{
		const char* const name;
		const MenuItem* (*func)(const MenuItem* current);
		
		const MenuItem* parent;
		
		const MenuItem* const *children;
		const int children_amount;
	};
}