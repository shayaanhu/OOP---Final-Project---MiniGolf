#include "tile.hpp"

Tile::Tile(Vector2f pos, SDL_Texture* tex) : Entity(pos, tex) {}


Rectangle::Rectangle(Vector2f p_pos, Vector2f p_pos2, SDL_Texture* p_tex)
    : tile1(p_pos, p_tex), tile2(p_pos2, p_tex)
{
    
}

void Rectangle::render(Screen& screen) {
    screen.render(tile1);
    screen.render(tile2);
}






