#include "rectangle.hpp"

Rectangle::Rectangle(Vector2f p_pos, Vector2f p_pos2, SDL_Texture* p_tex)
    : tile1(p_pos, p_tex), tile2(p_pos2, p_tex) {}

void Rectangle::render(Screen& screen) {
    screen.render(tile1);
    screen.render(tile2);
}

std::vector<Vector2f> Rectangle::getPositions() {
    std::vector<Vector2f> positions;
    positions.push_back(tile1.getPosition());
    positions.push_back(tile2.getPosition());
    
    return positions;
}

std::vector<Tile> Rectangle::getTiles() {
    std::vector<Tile> tiles;
    tiles.push_back(tile1);
    tiles.push_back(tile2);
    
    return tiles;
}
