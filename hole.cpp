#include "hole.hpp"
#include "entity.hpp"
#include "vector2f.hpp"
#include <SDL.h>

Hole::Hole() {}

Hole::Hole(Vector2f pos, SDL_Texture* tex) : Entity(pos, tex) {}
Vector2f Hole::getPosition() {
    return Vector2f(position.x + 20, position.y + 20);
}
