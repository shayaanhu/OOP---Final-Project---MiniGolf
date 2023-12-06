#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

class Powermeter : public Entity {
public: 
    Powermeter(Vector2f pos, SDL_Texture* tex);
};