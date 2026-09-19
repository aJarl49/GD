#include "entity.h"
#include "levels.h"
#include "command.h"

bool IsMoving(Entity* e){
  return e->x != e->x_prev || e->y != e->y_prev ;
}

bool HasBehaviour(Entity* entity, Behaviour flags){
return (entity->behaviour & flags) == flags;
}

void SetBehaviour(Entity* entity, Behaviour flags){
entity->behaviour = flags;
}

void AddBehaviour(Entity* entity, Behaviour flags){
entity->behaviour = (Behaviour)(entity->behaviour | flags);
}

void RemoveBehaviour(Entity* entity, Behaviour flags){
entity->behaviour = (Behaviour)(entity->behaviour & ~flags);
}

void InitializeBaseBehaviour(Entity* entity){
assert(entity->id != ID::NONE);
switch (entity->id) {
  default:
    SetBehaviour(entity, NONE);
	  break;
  case ID::PIRATE:
	  SetBehaviour(entity, (Behaviour)(CAN_ROTATE | CAN_MOVE | IS_PLAYER | RESPOND_TO_INPUT));
    AddBehaviour(entity, Behaviour::JUMPS);
    entity->strength = 10;
	  break;
  case ID::BETON:
 	  SetBehaviour(entity, (Behaviour)CAN_MOVE);
	  break;
  case ID::CHEST:
	  SetBehaviour(entity, (Behaviour)CAN_MOVE);
	  break;
  case ID::CRAB:
	  SetBehaviour(entity, (Behaviour)CAN_MOVE);
    entity->strength = 5;
	  break;
  case ID::CRABBIS:
	  SetBehaviour(entity, (Behaviour)CAN_MOVE);
    entity->strength = 5;
	  break;
  case ID::
  CRABBO:
	  SetBehaviour(entity, (Behaviour)CAN_MOVE);
    entity->strength = 5;
	  break;
  case ID::PARROT:
	  SetBehaviour(entity, (Behaviour)CAN_MOVE);
    entity->strength = 5;
	  break;
  }
}

void PostMove(Entity* entity, LevelData* level, CommandBuffer* commandBuffer){
  if(entity->id == ID::CRABBO){
    Entity* entity_looked_at = RaycastFirstEntity(entity->x, entity->y, entity->facing, level);
    if(entity_looked_at != nullptr){
      if(!HasBehaviour(entity_looked_at, Behaviour::IS_PETRIFIED)){
        ModifyBehaviourCommand modify(entity_looked_at, Behaviour::IS_PETRIFIED, ModifyBehaviourCommand::ADD);
        Push(commandBuffer, modify, level);
      }
    }
  }
}

void PostRotation(Entity* entity, LevelData* level, CommandBuffer* commandBuffer, Direction from, Direction to){
  if(from==to){
    return;
  }
  if(entity->id == ID::CRABBO){
  Entity* entity_looked_at = RaycastFirstEntity(entity->x, entity->y, to, level);
    if(entity_looked_at != nullptr){
      if(!HasBehaviour(entity_looked_at, Behaviour::IS_PETRIFIED)){
        ModifyBehaviourCommand modify(entity_looked_at, Behaviour::IS_PETRIFIED,ModifyBehaviourCommand::ADD);
        Push(commandBuffer, modify, level);
      }
    }
  }
}

void PreRotation(Entity* entity, LevelData* level, CommandBuffer* commandBuffer, Direction from, Direction to){
  if(from == to){
    return;
  }
  if(entity->id == ID::CRABBO){
    Entity* entity_previously_looked_at = RaycastFirstEntity(entity->x, entity->y, from, level);
    if(entity_previously_looked_at != nullptr){
      if(HasBehaviour(entity_previously_looked_at, Behaviour::IS_PETRIFIED)){
        ModifyBehaviourCommand modify(entity_previously_looked_at, Behaviour::IS_PETRIFIED, ModifyBehaviourCommand::REMOVE);
        Push(commandBuffer, modify, level);
      }
    }
  }
}
