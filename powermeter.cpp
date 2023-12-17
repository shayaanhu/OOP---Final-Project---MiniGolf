#include "powermeter.hpp"
#include "entity.hpp"
#include "vector2f.hpp"
#include <SDL.h>

Powermeter::Powermeter(Vector2f pos, SDL_Texture* fgTex, SDL_Texture* bgTex) : Entity(pos, fgTex), backgroundTex(bgTex) {} 

void Powermeter::setTexture(SDL_Texture* fgTex, SDL_Texture* bgTex) {
    foregroundTex = fgTex;
    backgroundTex = bgTex;
}
