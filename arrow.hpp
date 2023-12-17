#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

// This is the arrow that points in the direction that the ball will be launched.
// Inherited from Entity.

class Arrow : public Entity {
public: 
    Arrow();
    Arrow(Vector2f pos, SDL_Texture* tex);
};
