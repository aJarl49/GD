#include "levelRenderer.h"
#include "common.h"
#include "entity.h"
#include "rendering.h"
#include <cstdint>
#include <winscard.h>

void RenderLevel(GameData* gameData, SDL_Renderer* renderer){
  LevelData lvl = gameData->levels[gameData->currentLevel];

  int board_width_px_half = lvl.w * CELL_SIZE_PX /2;
  int board_height_px_half = lvl.h * CELL_SIZE_PX /2;

  for (int x = 0; x<lvl.w; x++){
    for (int y = 0; y<lvl.h; y++){
      //uint8_t cellType = lvl.GetCellID(x,y);
      ID cellType = static_cast<ID>(lvl.GetCellID(x, y));

      Image* sprite = gameData->fallback;
      switch(cellType){
        case ID::BETON :
          sprite = gameData-> beton;
          break;
        case ID::DRY_SAND:
          sprite = gameData->dry_sand;
          break;
        case ID::FALLBACK:
          sprite = gameData-> fallback;
          break;
        case ID::GRASS:
          sprite = gameData->grass;
          break;
        case ID::PLAYER:
          sprite = gameData-> player;
          break;
        case ID::WATER:
          sprite = gameData->water;
          break;
        case ID::WET_SAND:
          sprite = gameData->wet_sand;
          break;
        default:
          sprite = gameData->fallback;
          break;
      }

      float xPos = x * CELL_SIZE_PX;
      float yPos = y * CELL_SIZE_PX;

      xPos += SCREEN_WIDTH / 2.0;
      yPos += SCREEN_HEIGHT / 2.0;

      xPos -= board_width_px_half;
      yPos -= board_height_px_half;

      RenderSprite(sprite, renderer, xPos, yPos);
    }
  }
}


void RenderEntities(GameData* data, SDL_Renderer* renderer){
  LevelData lvlData = data->levels[data->currentLevel];
  for(int i = 0; i < lvlData.entityCount; i++){
    Image* img;
    Entity entity = lvlData.entityBuffer[i];
    switch(entity.id){
      case ID::PLAYER:
        img = data -> player;
        break;
      default:
        img = data -> fallback;
        break;
      
    }

    int xPos = 0;
    int yPos = 0;

    xPos += SCREEN_WIDTH/2.0;
    yPos += SCREEN_HEIGHT/2.0;

    xPos -= data->levels[data->currentLevel].w * CELL_SIZE_PX/2;
    yPos -= data->levels[data->currentLevel].h * CELL_SIZE_PX/2;

    xPos += entity.x * CELL_SIZE_PX;
    yPos += entity.y * CELL_SIZE_PX;

    RenderSprite(img, renderer, xPos, yPos);
  }
}
