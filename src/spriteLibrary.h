#pragma once

#include "SDL3/SDL_render.h"
#include "entity.h"

struct Sprite{
  SDL_Texture* texture;
  int width;
  int height;
};

enum class SPRITE_ID{
  Beton,
  Brick,
  Chest,
  Crab,
  Crabbis,
  Crabbo,
  Dry_sand,
  Fallback,
  Grass,
  Parrot,
  Pirate,
  Water,
  Wet_sand,
};

struct SpriteDataEntry{
  SPRITE_ID id;
  const char* path;
};

Sprite* GetSpriteFromID(ID id, Sprite* spriteBuffer);
namespace AssetManagement{
  void LoadSprite(Sprite* spriteBuffer, SpriteDataEntry entry, SDL_Renderer* renderer);
  void LoadAllSprites(Sprite* spriteBuffer, SDL_Renderer* renderer);
}
