#ifndef BALL_HPP
#define BALL_HPP

#include "entity.hpp"
#include "hole.hpp"
#include "tile.hpp"
#include "arrow.hpp"
#include "powermeter.hpp"
#include <vector>

class Ball : public Entity {
private:
    Vector2f velocity;
    float velocity1D;

    Vector2f launchedVelocity;
    float launchedVelocity1D;

    Vector2f initialMousePosition;

    Vector2f target;

    float friction = 0.00075;
    int dirX, dirY = 1;
    int strokes = 0;

    bool canMove = true;
    bool win = false;
    int index;

    Entity powerBar;
    // Entity arrow;
    
public:
    Ball(Vector2f position, SDL_Texture* texture);

    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    void setInitialMousePosition(float x, float y);
    void update(double deltaTime, bool mouseDown, bool mousePressed, Hole h, std::vector<Tile> tiles, Arrow& arrow, std::vector<Powermeter> powerMeter);
    void render(SDL_Renderer* renderer);

    Vector2f& getVelocity();
    Vector2f& getLaunchedVelocity();
    Vector2f& getInitialMousePosition();
    // std::vector<Entity> getPowerMeter();
    // Entity& getArrow();
    int getStrokes();
    bool isWin();
    void setWin(bool w);

    // Add other member functions and variables as needed

};

#endif // BALL_HPP
