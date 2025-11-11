#pragma once

namespace ssY
{
	struct MenuItem
	{
		const char* const title;
		void (*func)();
	};
}