#include "game.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "entity.h"
#include "levelRenderer.h"
#include "levels.h"

extern "C"{
	void Initialize(GameData* data, SDL_Renderer* renderer){
		data->beton = AssetManagement::LoadSprite(data->arena_images, renderer, "beton.png");
		data->dry_sand = AssetManagement::LoadSprite(data->arena_images, renderer, "dry_sand.png");
		data->fallback = AssetManagement::LoadSprite(data->arena_images, renderer, "fallback.png");
		data->grass = AssetManagement::LoadSprite(data->arena_images, renderer, "grass.png");
		data->player = AssetManagement::LoadSprite(data->arena_images, renderer, "player.png");
		data->water = AssetManagement::LoadSprite(data->arena_images, renderer, "water.png");
		data->wet_sand = AssetManagement::LoadSprite(data->arena_images, renderer, "wet_sand.png");
		
		data -> currentLevelIndex = 0;
		CreateLevel(data->arena_levels, &data->levels[0], "assets/levels/island_1.tmj");
		CreateEntities(&data->levels[data->currentLevelIndex], data->arena_entities);
	}

	bool HandleEvents(GameData* data, SDL_Event event){
		if(event.type != SDL_EVENT_KEY_DOWN){
			return true;
		}
		if(event.key.key == SDLK_ESCAPE){
			return false;
		}
		return true;
	}
	
	void Update(GameData* data, float dt){

		const bool* keys = SDL_GetKeyboardState(nullptr);

		for(int i = 0; i < data->GetCurrentLevel()->entityCount; i++){
			Entity* entity = &data->GetCurrentLevel()->entityBuffer[i];

			if(entity->HasBehaviour((Behaviour)(Behaviour::RESPOND_TO_INPUT | Behaviour::CAN_MOVE))){
				int xChange = 0;
				int yChange = 0;
				if(KeyPressed(SDL_SCANCODE_RIGHT, keys, data->keys_previous)){
					xChange = 1;
				}
				else if(KeyPressed(SDL_SCANCODE_LEFT, keys, data->keys_previous)){
					xChange = -1;
				}
				else if(KeyPressed(SDL_SCANCODE_UP, keys, data->keys_previous)){
					yChange = -1;
				}
				else if(KeyPressed(SDL_SCANCODE_DOWN, keys, data->keys_previous)){
					yChange = 1;
				}
				if(xChange !=0 || yChange != 0){
					TryMove(entity, data->GetCurrentLevel(), xChange, yChange);
				}
			}
		}


		memcpy((void*)data->keys_previous, keys, SDL_SCANCODE_COUNT * sizeof(bool));

	}

	void Draw(GameData* data, SDL_Renderer* renderer){
		SDL_SetRenderDrawColor(renderer, 150, 70, 20, 255);
		SDL_RenderClear(renderer);

		RenderLevel(data, renderer);
		RenderEntities(data, renderer);

		SDL_RenderPresent(renderer);
		}

	void OnQuit(SDL_Renderer* renderer){
		SDL_DestroyRenderer(renderer);
	}
}

bool KeyPressed(SDL_Scancode key, const bool* current, const bool* previous){
	if(previous == nullptr){
		return current[key];
	}
	return current[key] && !previous[key];
}

bool KeyHeld(SDL_Scancode key, const bool* current, const bool* previous){
	if(previous == nullptr){
		return false;
	}
	return current[key] && previous[key];
}

bool KeyReleased(SDL_Scancode key, const bool* current, const bool* previous){
	if(previous == nullptr){
		return false;
	}
	return !current[key] && previous[key];
}

bool TryMove(Entity* mover, LevelData* level, int xDir, int yDir){
	if(mover->HasBehaviour(CAN_MOVE) == false){
		return false;
	}
	int test_x = mover->x + xDir;
	int test_y = mover->y + yDir;
	Entity* stepInto_entity = level->GetEntity(test_x, test_y);
	ID stepInto_tile_id = (ID)level->GetCellID(test_x, test_y);
	if(stepInto_entity == nullptr){
		if(stepInto_tile_id == ID::DRY_SAND){
			mover->x = test_x;
			mover->y = test_y;
			return true;
		}
		return false;
	}

	if (stepInto_entity->HasBehaviour(CAN_MOVE)){
		if (TryMove(stepInto_entity, level, xDir, yDir)){
			mover->x = test_x;
			mover->y = test_y;
			return true;
		}
	}
	return false;
}
