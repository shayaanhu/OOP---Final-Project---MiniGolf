#pragma once
#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "entity.hpp"

// Our game Screen.
// All of the SDL related work is done here.

class Screen {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Screen(const char* p_title, int p_w, int p_h);
    ~Screen();

    SDL_Texture* loadTexture(const char* filePath);
    void render(int x, int y, SDL_Texture* texture);
    void render(Entity& entity);
    void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor); // For Fonts
    void clear();
    void display();
    SDL_Renderer* getRenderer();

    

};

#endif // SCREEN_HPP
