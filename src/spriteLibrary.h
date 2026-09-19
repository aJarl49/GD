#pragma once

#include "SDL3/SDL_render.h"
#include "entity.h"

const int NOT_SET = -1;

struct Sprite{
  SDL_Texture* texture;
  int width;
  int height;
  int pivot_x;
  int pivot_y;
};

enum class SPRITE_ID{
  Beton,
  Brick,
  Chest,
  Crab,
  Crabbis,
  Crabbo,
  Dropshadow,
  Dry_sand,
  Dry_sand_alt,
  Fallback,
  Grass,
  Parrot,
  Pirate_Idle_Back,
  Pirate_Idle_Front,
  Pirate_Idle_Side,
  Water,
  Wet_sand,
};

struct SpriteDataEntry{
  SPRITE_ID id;
  const char* path;
  int pivot_x = NOT_SET;
  int pivot_y = NOT_SET;
};

Sprite* GetSpriteFromID(ID id, Sprite* spriteBuffer);
Sprite* GetSprite_FromEntityState(Entity* entity, Sprite* spriteBuffer);
namespace AssetManagement{
  void LoadSprite(Sprite* spriteBuffer, SpriteDataEntry entry, SDL_Renderer* renderer);
  void LoadAllSprites(Sprite* spriteBuffer, SDL_Renderer* renderer);
}
