#pragma once
//#include "spriteLibrary"
#include <cassert>
#include <cstdint>

struct CommandBuffer;
struct LevelData;

enum Behaviour : uint32_t {
  NONE = 0,
  CAN_MOVE = 1 << 0,
  IS_PLAYER = 1 << 1,
  RESPOND_TO_INPUT = 1 << 2,
  IS_PETRIFIED = 1 << 3,
  CAN_ROTATE = 1 << 4,
  UNPUSHABLE = 1 << 5,
  JUMPS = 1 << 6,
  IS_PUSHING = 1 << 7,
};

// adjusted to my tileset
enum class ID : uint8_t{
  NONE = 0,
  BETON = 1,
  BRICK = 2,
  CHEST = 3,
  CRAB = 4,
  CRABBIS = 5,
  CRABBO = 6,
  DRY_SAND = 7,
  FALLBACK =8,
  GRASS = 9,
  PARROT = 10,
  PIRATE = 11,
  WATER = 12,
  WET_SAND = 13
};

enum class Direction{
  RIGHT,
  LEFT,
  UP,
  DOWN
};

inline Direction DirectionFromXY(int xDir, int yDir){
  assert(xDir * yDir == 0);
  if(xDir == 1){return Direction::RIGHT;}
  if(xDir == -1){return Direction::LEFT;}
  if(yDir == 1){return Direction::UP;}
  else {return Direction::DOWN;}
}

struct Entity{
  //uint8_t id;
  ID id;
  Direction facing;
  int strength;
  int x;
  int y;
  int x_prev;
  int y_prev;
  float progress_01;
  Behaviour behaviour;
};

struct Position{
  int x;
  int y;
};

bool IsMoving(Entity* e);
bool HasBehaviour(Entity* entity, Behaviour flags);
void InitializeBaseBehaviour(Entity* entity);
void SetBehaviour(Entity* entity, Behaviour flags);
void AddBehaviour(Entity* entity, Behaviour flags);
void RemoveBehaviour(Entity* entity, Behaviour flags);
void PostMove(Entity* entity, LevelData* level, CommandBuffer* commandBuffer);
void PostRotation(Entity* entity, LevelData* level, CommandBuffer* commandBuffer, Direction from, Direction to);
void PreRotation(Entity* entity, LevelData* level, CommandBuffer* commandBuffer, Direction from, Direction to);
