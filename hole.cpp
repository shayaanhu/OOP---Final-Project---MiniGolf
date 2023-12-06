#include "hole.hpp"
#include "entity.hpp"
#include "vector2f.hpp"
#include <SDL.h>

Hole::Hole(Vector2f pos, SDL_Texture* tex) : Entity(pos, tex) {}