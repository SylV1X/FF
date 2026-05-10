#pragma once

#include "GameObject.hpp"

namespace ssY {
	class MovingObject: public GameObject
	{
		protected:
			bool is_fly;
			float horizontal_speed;
			float vertical_speed;

		public:
			bool get_is_fly() const;
			float get_horizontal_speed() const;
			float get_vertical_speed() const;
			
			void init_object(
				float init_x, float init_y, 
				float init_width, float init_height, 
				char init_kind
			);
		
			void set_vertical_speed(float new_vertical_speed);
	};
}
