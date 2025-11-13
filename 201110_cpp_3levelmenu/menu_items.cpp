#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const ssY::MenuItem ssY::GO_BACK =
{
	"0 - Вернуться к выбору предметов...", ssY::go_back, &ssY::ALGEBRA
};
const ssY::MenuItem ssY::GO_BACK_TO_MENU =
{
	"0 - Вернуться в главное меню...", ssY::go_back, &ssY::STUDY
};

const ssY::MenuItem ssY::SUM =
{
	"1 - Хочу научиться складывать!", ssY::sum, &ssY::ALGEBRA
};
const ssY::MenuItem ssY::SUBSTRACT =
{
	"2 - Хочу научиться вычитать!", ssY::substract, &ssY::ALGEBRA
};
const ssY::MenuItem ssY::MULTIPLY =
{
	"3 - Хочу научиться умножать!", ssY::multiply, &ssY::ALGEBRA
};
const ssY::MenuItem ssY::DIVIDE =
{
	"4 - Хочу научиться делить!", ssY::divide, &ssY::ALGEBRA
};

namespace
{
	const ssY::MenuItem* const algebra_children[] = 
	{
		&ssY::GO_BACK,
		&ssY::SUM,
		&ssY::SUBSTRACT,
		&ssY::MULTIPLY,
		&ssY::DIVIDE
	};
	const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
}

const ssY::MenuItem ssY::DIFF_EQ =
{
	"1 - Хочу изучить дифференциальное исчисление!", ssY::diff_eq, &ssY::MATH_ANALYSIS
};
const ssY::MenuItem ssY::INTEGRAL =
{
	"2 - Хочу изучить интегральное исчисление!", ssY::integral, &ssY::MATH_ANALYSIS
};

namespace
{
	const ssY::MenuItem* const math_analysis_children[] = 
	{
		&ssY::GO_BACK,
		&ssY::DIFF_EQ,
		&ssY::INTEGRAL
	};
	const int math_analysis_size = sizeof(math_analysis_children) / sizeof(math_analysis_children[0]);
}

const ssY::MenuItem ssY::ALGEBRA =
{
	"1 - Хочу изучать алгебру!", ssY::show_menu, &ssY::STUDY, algebra_children, algebra_size
};
const ssY::MenuItem ssY::MATH_ANALYSIS =
{
	"2 - Хочу изучать математический анализ!", ssY::show_menu, &ssY::STUDY, math_analysis_children, math_analysis_size
};

namespace
{
	const ssY::MenuItem* const study_children[] =
	{
		&ssY::GO_BACK_TO_MENU,
		&ssY::ALGEBRA,
		&ssY::MATH_ANALYSIS
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const ssY::MenuItem ssY::STUDY =
{
	"1 - Хочу учиться математике!", ssY::show_menu, &ssY::MAIN, study_children, study_size
};
const ssY::MenuItem ssY::EXIT =
{
	"0 - Я лучше пойду полежу...", ssY::exit, &ssY::MAIN
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