#pragma once
#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "entity.hpp"

class Screen {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    //constructor and destructor for screen
    Screen(const char* p_title, int p_w, int p_h);
    ~Screen();
    //functions to run for making the screen, loading it and once game is closed then clearing it as well
    SDL_Texture* loadTexture(const char* filePath);
    void render(int x, int y, SDL_Texture* texture);
    void render(Entity& entity);
    void clear();
    void display();
    SDL_Renderer* getRenderer();

    

};

#endif // SCREEN_HPP
