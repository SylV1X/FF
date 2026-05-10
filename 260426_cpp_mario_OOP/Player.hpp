#pragma once

#include "Level.hpp"
#include "MovingObject.hpp"
#include "Section.hpp"

namespace ssY {
	class Player: public MovingObject
	{
		public:
			void jump();
			
			bool player_collision_model(
				Level& level, 
				Sprite*& sprites, int& sprites_count, 
				int& score
			);
			
			bool vertical_move_object(
				Level& level, 
				GameObject*& blocks, int blocks_count, 
				Sprite*& sprites, int& sprites_count
			);
	};
}
