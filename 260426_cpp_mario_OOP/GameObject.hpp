#pragma once

namespace ssY {
	class GameObject
	{
		protected:
			float x, y;
			float height, width;
			char kind;

		public:		
			GameObject();
			
			bool check_collision(const GameObject& obj);
			
			float get_height() const;
			char get_kind() const;
			float get_width() const;
			float get_x() const;
			float get_y() const;
			
			void init_object(
				float init_x, float init_y, 
				float init_width, float init_height, 
				char init_kind
			);
			
			void set_kind(char new_kind);
			void set_object_pos(float obj_pos_x, float obj_pos_y);
			void set_x(float new_x);
	};
}
