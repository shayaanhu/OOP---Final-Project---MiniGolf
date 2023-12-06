#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

class Arrow : public Entity {
public: 
    Arrow(Vector2f pos, SDL_Texture* tex);
};