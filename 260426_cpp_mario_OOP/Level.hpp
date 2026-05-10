#pragma once

#include "GameObject.hpp"
#include "Sprite.hpp"

namespace ssY {
	class Level
	{
		private:
			int current_level = 1;
			int max_level = 3;
			
		public:
			void add_new_block(
				GameObject*& blocks, int& blocks_count, 
				float x, float y, 
				float height, float width, 
				char kind
			);
			void add_new_sprite(
				Sprite*& sprites, int& sprites_count, 
				float x, float y, 
				float height, float width, 
				char kind
			);
			
			void create_level(
				GameObject& player, 
				GameObject*& blocks, int& blocks_count, 
				Sprite*& sprites, int& sprites_count, 
				int& score
			);
			
			void delete_blocks(GameObject*& blocks, int& blocks_count);
			void delete_sprites(Sprite*& sprites, int& sprites_count);
			
			float get_level_num() const;
			
			void next_level(
				GameObject& player, 
				GameObject*& blocks, int& blocks_count, 
				Sprite*& sprites, int& sprites_count, 
				int& score
			);
			
			void remove_sprite(int index, Sprite*& sprites, int& sprites_count);
			void restart_level(
				GameObject& player, 
				GameObject*& blocks, int& blocks_count, 
				Sprite*& sprites, int& sprites_count, 
				int& score
			);
			
			void set_level_num(float new_num);
	};
}