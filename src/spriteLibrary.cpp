#include "spriteLibrary.h"
#include "SDL3_Image/SDL_image.h"
#include <cassert>

const char* FALLBACK_PATH = "assets/sprites/fallback.png";

static const SpriteDataEntry all_sprite_data[] = {
  {SPRITE_ID::Fallback, FALLBACK_PATH},
  {SPRITE_ID::Beton, "assets/sprites/beton.png"},
  {SPRITE_ID::Brick, "assets/sprites/brick.png"},
  {SPRITE_ID::Chest, "assets/sprites/chest.png"},
  {SPRITE_ID::Crab, "assets/sprites/crab.png"},
  {SPRITE_ID::Crabbis, "assets/sprites/crabbis.png"},
  {SPRITE_ID::Crabbo, "assets/sprites/crabbo.png"},
  {SPRITE_ID::Dry_sand, "assets/sprites/dry_sand.png"},
  {SPRITE_ID::Grass, "assets/sprites/grass.png"},
  {SPRITE_ID::Parrot, "assets/sprites/parrot.png"},
  {SPRITE_ID::Pirate, "assets/sprites/pirate.png"},
  {SPRITE_ID::Water, "assets/sprites/water.png"},
  {SPRITE_ID::Wet_sand, "assets/sprites/wet_sand.png"}
};

Sprite* GetSpriteFromID(ID id, Sprite* spriteBuffer){
  switch(id){
    case ID::NONE:
      return nullptr;
    case ID::BETON:
      return &spriteBuffer[(int)SPRITE_ID::Beton];
    case ID::BRICK:
      return &spriteBuffer[(int)SPRITE_ID::Brick];
    case ID::CHEST:
      return &spriteBuffer[(int)SPRITE_ID::Chest];
    case ID::CRAB:
      return &spriteBuffer[(int)SPRITE_ID::Crab];
    case ID::CRABBIS:
      return &spriteBuffer[(int)SPRITE_ID::Crabbis];
    case ID::CRABBO:
      return &spriteBuffer[(int)SPRITE_ID::Crabbo];
    case ID::DRY_SAND:
      return &spriteBuffer[(int)SPRITE_ID::Dry_sand];
    case ID::GRASS:
      return &spriteBuffer[(int)SPRITE_ID::Grass];
    case ID::PARROT:
      return &spriteBuffer[(int)SPRITE_ID::Parrot];
    case ID::PIRATE:
      return &spriteBuffer[(int)SPRITE_ID::Pirate];
    case ID::WATER:
      return &spriteBuffer[(int)SPRITE_ID::Water];
    case ID::WET_SAND:
      return &spriteBuffer[(int)SPRITE_ID::Wet_sand];
    default:
        return &spriteBuffer[(int)SPRITE_ID::Fallback];
      break;
  }
}

namespace AssetManagement{
  void LoadAllSprites(Sprite* spriteBuffer, SDL_Renderer* renderer){
    for (SpriteDataEntry entry : all_sprite_data){
      LoadSprite(spriteBuffer, entry, renderer);
    }
  }

  void LoadSprite(Sprite* spriteBuffer, SpriteDataEntry entry, SDL_Renderer* renderer){
    SDL_Surface* surface = IMG_Load(entry.path);
    if (surface == nullptr){
      surface = IMG_Load(FALLBACK_PATH);
    }
    assert(surface!=nullptr);
    SDL_Texture* texture =SDL_CreateTextureFromSurface(renderer, surface);
    Sprite* sprite = &spriteBuffer[(int)entry.id];
    sprite->texture = texture;
    sprite->height = texture->h;
    sprite->width = texture->w;

    SDL_DestroySurface(surface);
  }
}
