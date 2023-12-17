#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

class Hole : public Entity {
public: 
    Hole();
    Hole(Vector2f pos, SDL_Texture* tex);
    virtual Vector2f getPosition() override;

};
