#pragma once

#include "GameObject.hpp"
#include "Sprite.hpp"

namespace ssY {
	class Map
	{
		private:
			static const int MAP_HEIGHT = 28;
			static const int MAP_WIDTH = 80;
			char map[MAP_HEIGHT][MAP_WIDTH + 1];
			
		public:
			void add_object_on_map(const GameObject& obj);
			
			void clear_map();
			
			float get_MAP_HEIGHT() const;
			
			bool object_within_map(int x, int y);
			
			void scroll_map(
				float dx, 
				GameObject& player, GameObject*& blocks, 
				int blocks_count, Sprite*& sprites, int& sprites_count
			);
			void show_map();
			void show_score(int score);
	};
}
