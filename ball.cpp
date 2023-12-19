#include "ball.hpp"
#include <vector>

// Default constructor.
Ball::Ball() {}

// Parameterized constructor. 
// Sets the ball's position and texture.
// Also creates its powerMeter.
Ball::Ball(Vector2f position, SDL_Texture* texture, SDL_Texture* powermeterFG, SDL_Texture* powermeterBG) : Entity(position, texture) {
    powerMeter.push_back(Entity(Vector2f(0,0), powermeterBG));
    powerMeter.push_back(Entity(Vector2f(0,0), powermeterFG));   
    powerMeter.at(0).setScale(0.2, 0.2);
    powerMeter.at(1).setScale(0.2, 0.2);

}

// Sets the Ball's current velocity.
void Ball::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

// Sets the Ball's current launchedVelocity.
void Ball::setLaunchedVelocity(float x, float y) {
    launchedVelocity.x = x;
    launchedVelocity.y = y;
}

// Sets the current position of the mouse when first clicked.
void Ball::setInitialMousePosition(float x, float y) {
    initialMousePosition.x = x;
    initialMousePosition.y = y;
}

// Returns the ball's current velocity.
Vector2f& Ball::getVelocity() {
    return velocity;
}

// Returns the ball's current launchedVelocity.
Vector2f& Ball::getLaunchedVelocity() {
    return launchedVelocity;
}

// Returns the current position of the mouse once its dragged out.
Vector2f& Ball::getInitialMousePosition() {
    return initialMousePosition;
}

// Sets the ball's win attribute to win.
void Ball::setWin(bool w) {
    win = w;
}

// Returns wether or not the win condition has been met.
bool Ball::getWin() {
    return win;
}

// Our most important function.
// Handles everything related to the ball while the game is running.
void Ball::update(double deltaTime, bool mouseDown, bool mousePressed, Hole h, std::vector<Tile> tiles, std::vector<Rectangle> rect, Arrow& arrow) {

    // Keep running these steps to put the ball into the hole once the win condition has been met (ball is sufficiently close to the hole).
    if (win == true) {

        // Getting the current position of the ball to check for collisons:
        Vector2f currentPosition = getPosition();

        // Depending on the ball's current position and the position of the hole, move the ball towards the hole.
        if (currentPosition.x < target.x)
        {
            // std::cout << "A";
            setPosition(currentPosition.x + 1 * deltaTime, currentPosition.y);
        }
        else if (currentPosition.x > target.x)
        {
            // std::cout << "B";
            setPosition(currentPosition.x - 1 * deltaTime, currentPosition.y);
        }
        if (currentPosition.y < target.y)
        {
            // std::cout << "C";
            setPosition(currentPosition.x, currentPosition.y + 1 * deltaTime);
        }
        else if (currentPosition.y > target.y)
        {
            // std::cout << "D";
            setPosition(currentPosition.x, currentPosition.y - 1 * deltaTime);
        }

        // Set the ball's scale to very very small so that it looks like it goes inside the hole.
        Vector2f currentScale = getScale();
        setScale(currentScale.x - 1 * deltaTime, currentScale.y - 1 * deltaTime);

        return;
    }

    
    // std::cout << "BALL POSITIONX: " << getPosition().x << "HOLE POSITIONX:" << h.getPosition().x;
    // std::cout << "BALL POSITIONY: " << getPosition().y << "HOLE POSITIONY:" << h.getPosition().y << std::endl;
    // std::cout << "BALL VELOCITYX" << getVelocity().x << "BALL VELOCITYY" << getVelocity().y << std::endl;

    // Win condition:
    // Ball's velocity must not be too high, otherwise it will go past the hole.
    if (abs(getVelocity().x) < 0.05 and abs(getVelocity().x) < 0.05 and getPosition().x > h.getPosition().x + 20 && getPosition().x < h.getPosition().x + 50 && getPosition().y > h.getPosition().y + 20 && getPosition().y < h.getPosition().y + 40){
        // std::cout << "WON ";

        // Set win and find the hole's current position.
        setWin(true);
        target.x = h.getPosition().x;
        target.y = h.getPosition().y;

    }

    // When the mouse is first clicked.
    if (mousePressed and canMove) {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePosition(mouseX, mouseY);
    }

    // Keep track of the mouse as it is dragged out.
    if (mouseDown and canMove) {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setVelocity((mouseX - getInitialMousePosition().x)/-150, (mouseY - getInitialMousePosition().y)/-150);
        setLaunchedVelocity((mouseX - getInitialMousePosition().x)/-150, (mouseY - getInitialMousePosition().y)/-150);
        velocity1D = SDL_sqrt(SDL_pow(abs(getVelocity().x), 2) + SDL_pow(abs(getVelocity().y), 2));
        launchedVelocity1D = velocity1D;

        // Arrow logic:
        // std::cout << "ARROW";
        arrow.setPosition(getPosition().x + 57.5, getPosition().y + 37.5);
        arrow.setAngle(SDL_atan2(velocity.y, velocity.x)*(180/3.1415) + 90);

        dirX = velocity.x/abs(velocity.x);
        dirY = velocity.y/abs(velocity.y);

        // Power meter logic:
        // powerMeter.at(0).setPosition(400, 100);
        // std::cout << "POWERMETERX" << powerMeter.at(0).getPosition().x << std::endl;
        powerMeter.at(0).setPosition(getPosition().x + 73.5, getPosition().y - 180);
        // std::cout << "AFTER SETPOS POWERMETERX" << powerMeter.at(0).getPosition().x << std::endl;
        powerMeter.at(1).setPosition(getPosition().x + 80, getPosition().y - 174);

        if (velocity1D > 1) {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }

        powerMeter.at(1).setScale(0.2, abs(velocity1D * 0.2));
        
    }

    // While the ball is moving.
    // Collision logic:
    else
    {
        // Incrementing strokes
        strokes++;
        
        // Setting the powerMeter's position outside the screen when not in use
        powerMeter.at(0).setPosition(-100, -100);
        powerMeter.at(1).setPosition(-100, -100);
        canMove = false;

        // Applying friction.
        setPosition(getPosition().x + getVelocity().x*deltaTime, getPosition().y + getVelocity().y*deltaTime);
        if (getVelocity().x > 0.0001 || getVelocity().x < -0.0001 || getVelocity().y > 0.0001 || getVelocity().y < -0.0001)
        {
            if (velocity1D > 0)
            {
                velocity1D -= friction*deltaTime;
            }
            else
            {
                velocity1D = 0;
            }
            velocity.x = (velocity1D/launchedVelocity1D)*abs(launchedVelocity.x)*dirX;
            velocity.y = (velocity1D/launchedVelocity1D)*abs(launchedVelocity.y)*dirY;

        }

        // When the ball is stopped.
        else {
            setVelocity(0,0);
            int mouseX = 0;
	        int mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            setInitialMousePosition(mouseX, mouseY);
            canMove = true;
        }

        // Checking for collision with the outer wall.
        if (getPosition().x + getCurrentFrame().w > 999)
        {
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        else if (getPosition().x < 0)
        {
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        else if (getPosition().y + getCurrentFrame().h > 649)
        {
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1;
        }
        else if (getPosition().y < 0)
        {
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1;
        }

        // std::cout << "BALL POSITIONX: " << getPosition().x << "TILE POSITIONX:" << t.getPosition().x;
        // std::cout << "BALL POSITIONY: " << getPosition().y << "TILE POSITIONY:" << t.getPosition().y << std::endl;

        // Collision logic with tiles (obstacles):
        for (Tile& t : tiles) {
            if (getPosition().x > t.getPosition().x + 60 and (getPosition().x < t.getPosition().x + 70 or getPosition().x < t.getPosition().x + 140) and getPosition().y > t.getPosition().y + 50 and (getPosition().y < t.getPosition().y + 70 or getPosition().y < t.getPosition().y + 130))
            {
                // std::cout << "COLLIDING" << std::endl;
                setVelocity(getVelocity().x*-1, getVelocity().y);
                dirX *= -1;

                setVelocity(getVelocity().x, getVelocity().y*-1);
                dirY *= -1;
            }
        }

        // Collision logic with rectangles and the tiles inside of them:
        for (Rectangle& r : rect) {

            for (Tile& t : r.getTiles()) {

            // std::cout << "BALL POSITIONX: " << getPosition().x << "TILE POSITIONX:" << t.getPosition().x;
            // std::cout << "BALL POSITIONY: " << getPosition().y << "TILE POSITIONY:" << t.getPosition().y << std::endl;

            if (getPosition().x > t.getPosition().x + 60 and (getPosition().x < t.getPosition().x + 70 or getPosition().x < t.getPosition().x + 130) and getPosition().y > t.getPosition().y + 50 and (getPosition().y < t.getPosition().y + 70 or getPosition().y < t.getPosition().y + 100))
            {
                // std::cout << "COLLIDING" << std::endl;
                
                setVelocity(getVelocity().x*-1, getVelocity().y);
                dirX *= -1;

                setVelocity(getVelocity().x, getVelocity().y*-1);
                dirY *= -1;
            }
        }

        }

    }

}

std::vector<Entity> Ball::getPowerMeter() {
    return powerMeter;
}

int Ball::getStrokes() {
    return strokes;
}

bool Ball::isWin() {
    return win;
}
