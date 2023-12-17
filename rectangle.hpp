#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"
#include "tile.hpp"
#include "screen.hpp"
#include <vector>

//making the rectangle class that handles the tiles in the game
// we have used AGGREGATION concept here as tiles can exist on their own
class Rectangle: public Entity{
    private:
    Tile tile1;
    Tile tile2;
    
    public:
        Rectangle(Vector2f p_pos, Vector2f p_pos2 , SDL_Texture* p_tex);
        void render(Screen& screen);
        std::vector<Vector2f> getPositions();
        std::vector<Tile> getTiles();
};

