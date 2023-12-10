#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.hpp"
#include "vector2f.hpp"
#include "screen.hpp" 
class Tile : public Entity {
public: 
    Tile(Vector2f p_pos, SDL_Texture* p_tex);
    Tile(){};

};

class Rectangle:public Entity{
    private:
    Tile tile1;
    Tile tile2;
    public:
        Rectangle(Vector2f p_pos, Vector2f p_pos2 , SDL_Texture* p_tex);

        void render(Screen& screen);
};
