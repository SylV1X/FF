#include "menu_items.hpp"
#include "menu_func.hpp"

#include <cstddef>

const ssY::MenuItem ssY::GO_BACK =
{
	"0 - Выйти в предыдущее меню", ssY::go_back, &ssY::PUSHKIN
};
const ssY::MenuItem ssY::DUBROVSKY =
{
	"1 - Дубровский", ssY::dubrovsky, &ssY::PUSHKIN
};
const ssY::MenuItem ssY::ONEGIN =
{
	"2 - Евгений Онегин", ssY::onegin, &ssY::PUSHKIN
};
const ssY::MenuItem ssY::WINTER_EVENING =
{
	"3 - Зимний вечер", ssY::winter_evening, &ssY::PUSHKIN
};

namespace
{
	const ssY::MenuItem* const pushkin_children[] =
	{
		&ssY::GO_BACK,
		&ssY::DUBROVSKY,
		&ssY::ONEGIN,
		&ssY::WINTER_EVENING
	};
	const int pushkin_children_amount = sizeof(pushkin_children) / sizeof(pushkin_children[0]);
}

const ssY::MenuItem ssY::GO_BACK_TO_MENU =
{
	"0 - Выйти в главное меню", ssY::go_back, &ssY::READ
};
const ssY::MenuItem ssY::PUSHKIN =
{
	"1 - Читать Пушкина", ssY::pushkin, &ssY::READ, pushkin_children, pushkin_children_amount
};
const ssY::MenuItem ssY::LERMONTOV =
{
	"2 - Читать Лермонтова", ssY::go_back, &ssY::READ
};
const ssY::MenuItem ssY::KRYLOV =
{
	"3 - Читать Крылова", ssY::go_back, &ssY::READ
};

namespace
{
	const ssY::MenuItem* const read_children[] =
	{
		&ssY::GO_BACK_TO_MENU,
		&ssY::PUSHKIN,
		&ssY::LERMONTOV,
		&ssY::KRYLOV
	};
	const int read_children_amount = sizeof(read_children) / sizeof(read_children[0]);
}

const ssY::MenuItem ssY::READ =
{
	"1 - Русские писатели", ssY::show_menu, &ssY::MAIN, read_children, read_children_amount
};
const ssY::MenuItem ssY::EXIT =
{
	"0 - Завершить чтение", ssY::exit, &ssY::MAIN
};

namespace
{
	const ssY::MenuItem* const main_children[] =
	{
		&ssY::EXIT,
		&ssY::READ
	};
	const int main_children_amount = sizeof(main_children) / sizeof(main_children[0]);
}
const ssY::MenuItem ssY::MAIN =
{
	nullptr, ssY::show_menu, nullptr, main_children, main_children_amount
};
