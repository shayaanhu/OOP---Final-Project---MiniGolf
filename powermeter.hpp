#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

// The powerMeter for the ball. 
// Indicates how much power the ball is launched with.
// Inherited from Entity.
class Powermeter : public Entity {
private:
    SDL_Texture* foregroundTex;
    SDL_Texture* backgroundTex;

public: 
    Powermeter(Vector2f pos, SDL_Texture* fgTex, SDL_Texture* bgTex);

    void setTexture(SDL_Texture* fgTex, SDL_Texture* bgTex);

};
