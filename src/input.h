#pragma once
#include "SDL3/SDL_keyboard.h"

struct Input{
  const bool* keys_current;
  const bool* keys_previous;
  float* keys_held_time;
};

bool KeyPressed(const Input* input, SDL_Scancode key);
bool KeyHeld(const Input* input, SDL_Scancode key);
bool KeyReleased(const Input* input, SDL_Scancode key);
void ResetKeyHeldTime(Input* input, SDL_Scancode key);
bool KeyHeld_ForTime(const Input* input, SDL_Scancode key, float min_lenght);
void UpdateKeys(Input* input, float dt);
void ResetAll(Input*);
