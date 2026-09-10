#pragma once
// #include "SDL3/SDL_rect.h"
#include "image.h"
#include "levels.h"
#include "command.h"
#include "imgui/imgui_internal.h"

struct GameData {
  const float* dt;
  uint32_t command_timestamp;
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
  Memory::Arena* arena_commands;
  LevelData* levels;
  int currentLevelIndex;
  int levelCount;
  int currentLevel;
  CommandBuffer* commandBuffer;
  LevelData* GetCurrentLevel(){
    return &levels[currentLevelIndex];
  }
  ImGuiContext* imGui_context;
};
