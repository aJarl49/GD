#include "spriteLibrary.h"
#include "SDL3_Image/SDL_image.h"
#include <cassert>

const char* FALLBACK_PATH = "assets/sprites/fallback.png";

static const SpriteDataEntry all_sprite_data[] = {
  {SPRITE_ID::Fallback, FALLBACK_PATH, 0,0},
  {SPRITE_ID::Beton, "assets/sprites/beton.png", 8,16},
  {SPRITE_ID::Brick, "assets/sprites/brick.png", 0,0},
  {SPRITE_ID::Chest, "assets/sprites/chest.png", 8,16},
  {SPRITE_ID::Crab, "assets/sprites/crab.png", 8,16},
  {SPRITE_ID::Crabbis, "assets/sprites/crabbis.png", 8,16},
  {SPRITE_ID::Crabbo, "assets/sprites/crabbo.png", 8,16},
  {SPRITE_ID::Dropshadow, "assets/sprites/dropshadow.png", 8,8},
  {SPRITE_ID::Dry_sand, "assets/sprites/dry_sand.png", 0,0},
  {SPRITE_ID::Dry_sand_alt, "assets/sprites/dry_sand_alt.png", 0,0},
  {SPRITE_ID::Grass, "assets/sprites/grass.png", 0,0},
  {SPRITE_ID::Parrot, "assets/sprites/parrot.png", 8,16}, // as deamon in kustliteratur
  {SPRITE_ID::Pirate_Idle_Back, "assets/sprites/pirate_idle_back.png", 12,24}, //pay attention!
  {SPRITE_ID::Pirate_Idle_Front, "assets/sprites/pirate_idle_front.png", 12,24},
  {SPRITE_ID::Pirate_Idle_Side, "assets/sprites/pirate_idle_left.png", 12,24},
  {SPRITE_ID::Water, "assets/sprites/water.png", 0,0},
  {SPRITE_ID::Wet_sand, "assets/sprites/wet_sand.png", 0,0}
};

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

    if(entry.pivot_x == NOT_SET || entry.pivot_y == NOT_SET){
      sprite->pivot_x = sprite->width / 2;
      sprite->pivot_y = sprite->height / 2;
    }
    else{
      sprite->pivot_x = entry.pivot_x;
      sprite->pivot_y = entry.pivot_y;
    }

    SDL_DestroySurface(surface);
  }
}


Sprite* GetSpriteFromID(ID id, Sprite* spriteBuffer){
  Sprite* sprite_to_return = nullptr;
  switch(id){
    case ID::NONE:
      sprite_to_return = nullptr;
      break;
    case ID::BETON:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Beton];
      break;
    case ID::BRICK:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Brick];
      break;
    case ID::CHEST:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Chest];
      break;
    case ID::CRAB:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Crab];
      break;
    case ID::CRABBIS:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Crabbis];
      break;
    case ID::CRABBO:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Crabbo];
      break;
    case ID::DRY_SAND:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Dry_sand];
      break;
    case ID::FALLBACK:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Fallback];
      break;
    case ID::GRASS:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Grass];
      break;
    case ID::PARROT:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Parrot];
      break;
    case ID::PIRATE:
      sprite_to_return = nullptr;
      break;
    case ID::WATER:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Water];
      break;
    case ID::WET_SAND:
      sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Wet_sand];
      break;
    }
    if (sprite_to_return == nullptr || sprite_to_return->texture == nullptr){
        sprite_to_return = &spriteBuffer[(int)SPRITE_ID::Fallback];
    }
  return sprite_to_return;
}

Sprite* GetSprite_FromEntityState(Entity* entity, Sprite* spriteBuffer){
  if(HasBehaviour(entity, Behaviour::IS_PETRIFIED)){
    return &spriteBuffer[(int)SPRITE_ID::Beton];
  }
  switch(entity->id){
    case ID::PIRATE:
      switch(entity->facing){
        case Direction::RIGHT:
        case Direction::LEFT:
          return &spriteBuffer[(int)SPRITE_ID::Pirate_Idle_Side];
          break;
        case Direction::UP:
          return &spriteBuffer[(int)SPRITE_ID::Pirate_Idle_Front];
          break;
        case Direction::DOWN:
          return &spriteBuffer[(int)SPRITE_ID::Pirate_Idle_Back];
          break;
        }
      default:
      return GetSpriteFromID(entity->id, spriteBuffer);
      break;
  }
  return nullptr;
}
