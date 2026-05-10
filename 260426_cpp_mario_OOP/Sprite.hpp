#pragma once

#include "MovingObject.hpp"
#include "Section.hpp"

namespace ssY {
	class Sprite: public MovingObject
	{
		public:
			void horizontal_move_object(
				Sprite& obj, 
				GameObject*& blocks, int blocks_count
			);	
			bool vertical_move_object(GameObject*& blocks, int blocks_count);
	};
}
