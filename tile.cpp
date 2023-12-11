#include "tile.hpp"

Tile::Tile(Vector2f pos, SDL_Texture* tex) : Entity(pos, tex) {}

Vector2f Tile::getPosition() {
    return Vector2f(position.x + 60, position.y + 60);
}
