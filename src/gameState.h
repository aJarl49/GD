#pragma once
// #include "SDL3/SDL_rect.h"
#include "image.h"
#include "levels.h"
#include "command.h"
#include "input.h"
#include "camera.h"
#include "imgui/imgui_internal.h"
#include "spriteLibrary.h"

struct GameData {
  const float* dt;
  uint32_t command_timestamp;
  SDL_FRect rect;
  float move_speed;
  Input input;
  Camera camera;
  Sprite* spriteBuffer;
  Memory::Arena* arena_levels;
  Memory::Arena* arena_entities;
  Memory::Arena* arena_images;
  Memory::Arena* arena_commands;
  Memory::Arena* arena_input;
  LevelData* levels;
  int currentLevelIndex;
  int levelCount;
  int currentLevel;
  CommandBuffer* commandBuffer;
  LevelData* GetCurrentLevel(){
    return &levels[currentLevelIndex];
  }
  ImGuiContext* imGui_context;
  Position* input_buffer;
  int input_buffer_capacity;
  int input_buffer_write_count;
  int input_buffer_read_count;
};
