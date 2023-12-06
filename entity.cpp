#include "entity.hpp"

// Implementation of member functions
Entity::Entity() {
    position = Vector2f(0,0);
    texture = 0;
}

Entity::Entity(Vector2f pos, SDL_Texture* tex) {
    position = pos;
    texture = tex;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(texture, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

void Entity::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

void Entity::setAngle(float ang) {
    angle = ang;
}

Vector2f Entity::getPosition() {
	return position;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}

SDL_Texture* Entity::getTexture() {
    return texture;
}

void Entity::setScale(float w, float h) {
	scale.x = w;
	scale.y = h;
}

Vector2f Entity::getScale() {
    return scale;
}

float Entity::getAngle() {
    return angle;
}

Entity::~Entity() {
    // Destructor implementation
    // WIll be adding any cleanup code needed when an Entity is destroyed
}