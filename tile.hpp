#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

class Tile : public Entity {
public: 
    Tile(Vector2f p_pos, SDL_Texture* p_tex);

    virtual Vector2f getPosition() override;

};
