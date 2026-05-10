#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "MovingObject.hpp"

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

#endif