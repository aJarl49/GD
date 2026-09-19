#include "levelRenderer.h"
#include "common.h"
#include "entity.h"
#include "game.h"
#include "rendering.h"
#include "spriteLibrary.h"
#include <cstdint>
#include <winscard.h>
#include <cmath>
#include <algorithm>
#include "SDL3/SDL_render.h"
#include "levels.h" 

void RenderLevel(GameData* gameData, SDL_Renderer* renderer){
 // SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_PIXELART);
  LevelData lvl = gameData->levels[gameData->currentLevel];

  int board_width_px_half = lvl.w * CELL_SIZE_PX /2;
  int board_height_px_half = lvl.h * CELL_SIZE_PX /2;

  for (int x = 0; x<lvl.w; x++){
    for (int y = 0; y<lvl.h; y++){
      //uint8_t cellType = GetCellID(lvl, x,y);
      ID cellType = static_cast<ID>(GetCellID(&lvl, x, y)); //might cause problems *&*
    

      //Sprite* sprite = GetSpriteFromID((ID)cellType, gameData->spriteBuffer);
      Sprite* sprite; //upcomibg if statement is creating chess pattern on the sand in the level

      if(ID(cellType) == ID::DRY_SAND){
        sprite = &gameData->spriteBuffer[(x+y) % 2 == 0 ? (int)SPRITE_ID::Dry_sand : (int)SPRITE_ID::Dry_sand_alt];
      }
      else{
        sprite = GetSpriteFromID((ID)cellType, gameData->spriteBuffer);
      }
      
      RenderSprite_Grid(sprite, &lvl, renderer, &gameData->camera, x, y);
    }
  }
}

bool IsEntityBelowOtherEntity(Entity* a, Entity* b){
  return a->y < b->y;
}

void RenderEntities(GameData* data, SDL_Renderer* renderer){
  LevelData* lvl = &data->levels[data->currentLevelIndex];

  Entity** SortedEntities = ALLOC_ARRAY(data->arena_scratch, Entity*, lvl->entityCount);
  for (int i = 0; i < lvl->entityCount; i++){ 
    SortedEntities [i] = &lvl->entityBuffer[i];
    }
    std::sort(SortedEntities, SortedEntities + lvl->entityCount, IsEntityBelowOtherEntity);

    for (int i = 0; i < lvl->entityCount; i++){
      Entity* entity = SortedEntities[i];
      if(entity->id == ID::NONE){
        continue;
      }

      Sprite* sprite = GetSprite_FromEntityState(entity, data->spriteBuffer);
    
      if(HasBehaviour(entity, Behaviour::IS_PETRIFIED)){
        sprite = GetSpriteFromID(ID::BETON, data->spriteBuffer);
      }
  
      float x_animated = std::lerp(entity->x_prev, entity->x, entity->progress_01);
      float y_animated = std::lerp(entity->y_prev, entity->y, entity->progress_01);

      float dropshadow_y = y_animated;

      if(HasBehaviour(entity, Behaviour::JUMPS) && !HasBehaviour(entity, Behaviour::IS_PUSHING)){
        y_animated -= 0.5 * sinf(entity->progress_01 * 3.14);
      }

    Sprite* dropshadow = &data->spriteBuffer[(int)SPRITE_ID::Dropshadow];

    RenderEntity_OnTile(dropshadow, lvl, renderer, &data->camera, x_animated, dropshadow_y, 1, 0.4, false);
    RenderEntity_OnTile(sprite, lvl, renderer, &data->camera, x_animated, y_animated, 1, 1, entity->facing == Direction::RIGHT);
  }
}
