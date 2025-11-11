#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const ssY::MenuItem ssY::SUM =
{
	"1 - Summa!", ssY::sum, &ssY::STUDY
};
const ssY::MenuItem ssY::SUBSTRACT =
{
	"2 - Substract!", ssY::substract, &ssY::STUDY
};
const ssY::MenuItem ssY::MULTIPLY =
{
	"3 - Multiply!", ssY::multiply, &ssY::STUDY
};
const ssY::MenuItem ssY::DIVIDE =
{
	"4 - Divide!", ssY::divide, &ssY::STUDY
};
const ssY::MenuItem ssY::GO_BACK =
{
	"0 - Main menu", ssY::go_back, &ssY::STUDY
};

namespace
{
	const ssY::MenuItem* const study_children[] = 
	{
		&ssY::GO_BACK,
		&ssY::SUM,
		&ssY::SUBSTRACT,
		&ssY::MULTIPLY,
		&ssY::DIVIDE
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const ssY::MenuItem ssY::STUDY =
{
	"1 - Math!", ssY::show_menu, &ssY::MAIN, study_children, study_size
};
const ssY::MenuItem ssY::EXIT =
{
	"2 - Sleep(", ssY::exit, &ssY::MAIN
};

namespace
{
	const ssY::MenuItem* const main_children[] =
	{
		&ssY::EXIT,
		&ssY::STUDY
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const ssY::MenuItem ssY::MAIN =
{
	nullptr, ssY::show_menu, nullptr, main_children, main_size
};