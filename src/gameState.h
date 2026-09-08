#pragma once
// #include "SDL3/SDL_rect.h"
#include "image.h"
#include "levels.h"

struct GameData {
  SDL_FRect rect;
  float move_speed;
  bool* keys_previous;
  Image* beton;
  Image* dry_sand;
  Image* player;
  Image* fallback;
  Image* grass;
  Image* water;
  Image* wet_sand;
  Memory::Arena* arena_levels;
  Memory::Arena* arena_entities;
  Memory::Arena* arena_images;
  LevelData* levels;
  int currentLevelIndex;
  int currentLevel;
  LevelData* GetCurrentLevel(){
    return &levels[currentLevelIndex];
  }
};
