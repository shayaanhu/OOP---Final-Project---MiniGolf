#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"

class Powermeter : public Entity {
private:
    SDL_Texture* foregroundTex;
    SDL_Texture* backgroundTex;

public: 
    Powermeter(Vector2f pos, SDL_Texture* tex);
    Powermeter(Vector2f pos, SDL_Texture* fgTex, SDL_Texture* bgTex);
    void setTexture(SDL_Texture* fgTex, SDL_Texture* bgTex);

};
