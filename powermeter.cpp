#include "powermeter.hpp"
#include "entity.hpp"
#include "vector2f.hpp"
#include <SDL.h>

Powermeter::Powermeter(Vector2f pos, SDL_Texture* tex) : Entity(pos, tex) {}