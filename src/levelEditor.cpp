#include "levelEditor.h"
#include "imgui/imgui.h"
#include "rendering.h"

namespace EDITOR{
  void DrawObjectPanel(Editor* editor, Sprite* spriteBuffer){
    ImGui::Begin("objects");
    ImVec2 size = {32, 32};

    if (ImGui::ImageButton("Beton", (ImTextureID)GetSpriteFromID(ID::BETON, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::BETON;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Brick", (ImTextureID)GetSpriteFromID(ID::BRICK, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::BRICK;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Chest", (ImTextureID)GetSpriteFromID(ID::CHEST, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::CHEST;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Crab", (ImTextureID)GetSpriteFromID(ID::CRAB, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::CRAB;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Crabbis", (ImTextureID)GetSpriteFromID(ID::CRABBIS, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::CRABBIS;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Crabbo", (ImTextureID)GetSpriteFromID(ID::CRABBO, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::CRABBO;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Dry_sand", (ImTextureID)GetSpriteFromID(ID::DRY_SAND, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::DRY_SAND;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Fallback", (ImTextureID)GetSpriteFromID(ID::FALLBACK, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::FALLBACK;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Grass", (ImTextureID)GetSpriteFromID(ID::GRASS, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::GRASS;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Parrot", (ImTextureID)GetSpriteFromID(ID::PARROT, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::PARROT;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Pirate", (ImTextureID)GetSpriteFromID(ID::PIRATE, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::PIRATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Water", (ImTextureID)GetSpriteFromID(ID::WATER, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::WATER;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Wet_sand", (ImTextureID)GetSpriteFromID(ID::WET_SAND, spriteBuffer)->texture, size)){
      editor->object_to_place_id = ID::WET_SAND;
    }
    ImGui::End();
  }

  void PlaceObject(const int x, const int y, Editor* editor, LevelData* level){
    if(editor->object_to_place_id == ID::NONE) return;
    if(editor->object_to_place_id == ID::BETON || editor->object_to_place_id == ID::BRICK || editor->object_to_place_id == ID::DRY_SAND || editor->object_to_place_id == ID::GRASS || editor->object_to_place_id == ID::WATER || editor->object_to_place_id == ID::WET_SAND){
      level->cells[y * level->w + x] = (int)editor->object_to_place_id;
    }
    else{
      AddEntity(editor->object_to_place_id, x, y, level);
    }
  }

  void DrawPreview(Editor* editor, Input* input, SDL_Renderer* renderer, LevelData* level, Camera* camera, Sprite* spriteBuffer){
    int x;
    int y;
    camera::WorldToGrid(input->mouse_x, input->mouse_y, &x, &y, level);
    Sprite* preview = GetSpriteFromID(editor->object_to_place_id, spriteBuffer);
    if(preview != nullptr){
      RenderSprite_Grid(preview, level, renderer, camera, x, y, 1, 0.5);
    }
  }

  void Update(Editor* editor, Input* input, LevelData* level){
    if(MousePressed(input, MouseButtons::LEFT)){
      if(camera::GetIsPointInsideGrid(input->mouse_x, input->mouse_y, level)){
        int x;
        int y;
        camera::WorldToGrid(input->mouse_x, input->mouse_y, &x, &y, level);
        PlaceObject(x, y, editor, level);
      } 
    }
    else if (MousePressed(input, MouseButtons::RIGHT)){
      if(camera::GetIsPointInsideGrid(input->mouse_x, input->mouse_y, level)){
        int x;
        int y;
        camera::WorldToGrid(input->mouse_x, input->mouse_y, &x, &y, level);
        RemoveEntity(x, y, level);
      }
    }
  }
}
