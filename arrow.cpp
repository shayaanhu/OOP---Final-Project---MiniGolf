
#include "arrow.hpp"
#include "entity.hpp"
#include "vector2f.hpp"
#include <SDL.h>

Arrow::Arrow() {}

Arrow::Arrow(Vector2f pos, SDL_Texture* tex) : Entity(pos, tex) {}
