#ifndef BALL_HPP
#define BALL_HPP

#include "entity.hpp"
#include "hole.hpp"
#include "tile.hpp"
#include "rectangle.hpp"
#include "arrow.hpp"
#include "powermeter.hpp"
#include <vector>

// Our ball.
// Inherited from Entity.

class Ball : public Entity {
private:
    Vector2f velocity; // The speed at which the ball moves (x and y speed).
    float velocity1D; // velocity in one direction.

    Vector2f launchedVelocity; // The speed with which the ball is launched by the player.
    float launchedVelocity1D; // launchedVelocity in one direction.

    Vector2f initialMousePosition; // The position the mouse is at when its first clicked. Used for checking how far the mouse travels and modifying the power of the shot based on that.
    Vector2f target; // The position of the hole.

    float friction = 0.00075; // Friction.
    int dirX, dirY = 1; // Direction the ball is travelling (x and y).
    int strokes = 0; // Number of times the ball is hit/launched.

    bool canMove = true; // To check if the ball is allowed to be moved or not.
    bool win = false; // Once the ball is in the hole.

    // (STRONG) COMPOSITION:
    std::vector<Powermeter> powerMeter; // powerMeter to indicate the power with which the ball is launched.
    std::vector<Arrow> pointerArrow; // pointerArrow to indicate the direction the ball will be launched in.
    
public:
    // Constructors:
    Ball();
    Ball(Vector2f position, SDL_Texture* texture, SDL_Texture* pmFG, SDL_Texture* pmBG);

    // Member functions:

    // Setters:
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    void setInitialMousePosition(float x, float y);
    void setWin(bool w);

    // Getters:
    Vector2f& getVelocity();
    Vector2f& getLaunchedVelocity();
    Vector2f& getInitialMousePosition();
    std::vector<Powermeter> getPowerMeter();
    bool getWin();
    int getStrokes();

    void update(double deltaTime, bool mouseDown, bool mousePressed, Hole h, std::vector<Tile> tiles, std::vector<Rectangle> rect, Arrow& arrow);   
    bool isWin();
    
};

#endif
