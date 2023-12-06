#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Vector2f.hpp"
#include <SDL.h>
#include <SDL_image.h>


class Entity {
private:
    Vector2f position;
    SDL_Texture* texture;
    SDL_Rect currentFrame;
    Vector2f scale = Vector2f(1, 1);
    float angle = 0;

public:
    Entity();
    Entity(Vector2f pos, SDL_Texture* tex);

    void setPosition(float x, float y);
    Vector2f getPosition();
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTexture();
    void clear();
    void setScale(float w, float h);
    Vector2f getScale();
    void setAngle(float ang);
    float getAngle();


    ~Entity(); 

};

#endif // ENTITY_HPP
