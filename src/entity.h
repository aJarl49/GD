#pragma once
#include <cassert>
#include <cstdint>

enum Behaviour : uint32_t {
  NONE = 0,
  CAN_MOVE = 1 << 0,
  IS_PLAYER = 1 << 1,
  RESPOND_TO_INPUT = 1 << 2
};

// adjusted to my tileset
enum class ID : uint8_t{
  NONE = 0,
  BETON = 1,
  DRY_SAND = 2,
  FALLBACK = 4,
  GRASS = 5,
  PLAYER = 6,
  WATER = 7,
  WET_SAND = 8
};

struct Entity{
  //uint8_t id;
  ID id;
  int x;
  int y;
  int x_prev;
  int y_prev;
  float progress_01;
  Behaviour behaviour;

  bool HasBehaviour(Behaviour flags){
    return (behaviour & flags) == flags;
  }

  void SetBehaviour(Behaviour flags){
    behaviour = flags;
  }

  void AddBehaviour(Behaviour flags){
    behaviour = (Behaviour)(behaviour | flags);
  }

  void RemoveBehaviour(Behaviour flags){
    behaviour = (Behaviour)(behaviour & ~flags);
  }

  void InitializeBaseBehaviour(){
    assert(id != ID::NONE);
    switch (id) {
      default:
        SetBehaviour(NONE);
        break;
      case ID::PLAYER:
        SetBehaviour((Behaviour)(CAN_MOVE | IS_PLAYER | RESPOND_TO_INPUT));
        break;
      case ID::BETON:
        SetBehaviour((Behaviour)CAN_MOVE);
        break;
    }
  }
};

struct Position{
  int x;
  int y;
};

bool IsMoving(Entity* e);
