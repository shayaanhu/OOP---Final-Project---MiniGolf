#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

// Tiles (obstacles) on the screen with which the ball collides.
// Inherited from Entity.
class Tile : public Entity {
public: 
    Tile(Vector2f p_pos, SDL_Texture* p_tex);

    virtual Vector2f getPosition() override;

};
