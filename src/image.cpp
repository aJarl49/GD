//#include <cassert>
//#include <string>
//#include "SDL3/SDL_render.h"
//#include "SDL3_Image/SDL_image.h"
//#include "spriteLibrary.h"
//#include "arena.h"

//using namespace std;

//const char* DIRECTORY = "assets/sprites/";
//const char* FALLBACK = "assets/sprites/fallback.png";

//Sprite* AssetManagement::LoadSprite(Memory::Arena* arena, const char* name, SDL_Renderer* renderer){

//  string path = DIRECTORY;
//  path = path.append(name);

//  SDL_Surface* surface = IMG_Load(path.c_str());

//  if(surface == nullptr){
//    surface = IMG_Load(FALLBACK);
//  }

//  assert(surface!= nullptr);

//  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

//  Sprite* img = (Sprite*)Memory::Allocate(arena, sizeof(Sprite));
//  img->texture = texture;
//  img->height = texture->h;
//  img->width = texture->w;

//  SDL_DestroySurface(surface);

//  return img;
  
//}
