#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Vector2f.hpp"
#include <SDL.h>
#include <SDL_image.h>

class Entity {
protected:
    Vector2f position;
    SDL_Texture* texture;
    SDL_Rect currentFrame;
    Vector2f scale = Vector2f(1, 1);
    float angle = 0;

public:
    // Constructors:
    Entity();
    Entity(Vector2f pos, SDL_Texture* tex);

    // Member functions:
    void setPosition(float x, float y);
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTexture();
    void setScale(float w, float h);
    Vector2f getScale();
    void setAngle(float ang);
    float getAngle();

    // Polymorphism:
    // Every entity has different dimensions, hence we need to override getPosition to account for that.
    virtual Vector2f getPosition();

    // Virtual destructor:
    virtual ~Entity(); 

};

#endif
