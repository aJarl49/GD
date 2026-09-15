#pragma once
//#include "spriteLibrary"
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
  BRICK = 2,
  CHEST = 3,
  CRAB = 4,
  CRABBIS = 5,
  CRABBO = 6,
  DRY_SAND = 7,
  FALLBACK = 8,
  GRASS = 9,
  PARROT = 10,
  PIRATE = 11,
  WATER = 12,
  WET_SAND = 13
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
      case ID::PIRATE:
        SetBehaviour((Behaviour)(CAN_MOVE | IS_PLAYER | RESPOND_TO_INPUT));
        break;
      case ID::BETON:
        SetBehaviour((Behaviour)CAN_MOVE);
        break;
      case ID::CHEST:
        SetBehaviour((Behaviour)CAN_MOVE);
        break;
      case ID::CRAB:
        SetBehaviour((Behaviour)CAN_MOVE);
        break;
      case ID::CRABBIS:
        SetBehaviour((Behaviour)CAN_MOVE);
        break;
      case ID::CRABBO:
        SetBehaviour((Behaviour)CAN_MOVE);
        break;
      case ID::PARROT:
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
