#include "ball.hpp"
#include <vector>

Ball::Ball(Vector2f position, SDL_Texture* texture) : Entity(position, texture) {}

void Ball::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

void Ball::setLaunchedVelocity(float x, float y) {
    launchedVelocity.x = x;
    launchedVelocity.y = y;
}

void Ball::setInitialMousePosition(float x, float y) {
    initialMousePosition.x = x;
    initialMousePosition.y = y;
}

Vector2f& Ball::getVelocity() {
    return velocity;
}

Vector2f& Ball::getLaunchedVelocity() {
    return launchedVelocity;
}

Vector2f& Ball::getInitialMousePosition() {
    return initialMousePosition;
}

// void Ball::render(SDL_Renderer* renderer) {
//     SDL_Rect destRect = { static_cast<int>(getPosition().x), static_cast<int>(getPosition().y), getCurrentFrame().w * getScale().x, getCurrentFrame().h * getScale().y};
//     SDL_RenderCopy(renderer, getTexture(), nullptr, &destRect);
// }

void Ball::setWin(bool w) {
    win = w;
}

void Ball::update(double deltaTime, bool mouseDown, bool mousePressed, Hole h, std::vector<Tile> tiles, Arrow& arrow, std::vector<Powermeter> powerMeter) {

    
    // Keep running these steps to put the ball into the hole
    if (win == true) {

        // Getting the current position of the ball to check for collisons:
        Vector2f currentPosition = getPosition();

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

        Vector2f currentScale = getScale();
        setScale(currentScale.x - 1 * deltaTime, currentScale.y - 1 * deltaTime);

        return;
    }

    // Win condition:
    // std::cout << "BALL POSITIONX: " << getPosition().x << "HOLE POSITIONX:" << h.getPosition().x;
    // std::cout << "BALL POSITIONY: " << getPosition().y << "HOLE POSITIONY:" << h.getPosition().y << std::endl;
    
    if (getPosition().x + 2 > h.getPosition().x && getPosition().x < h.getPosition().x + 40 && getPosition().y + 2 > h.getPosition().y && getPosition().y < h.getPosition().y + 40){
        // std::cout << "WON ";
        setWin(true);
        target.x = h.getPosition().x;
        target.y = h.getPosition().y;

    }

    if (mousePressed and canMove) {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePosition(mouseX, mouseY);
    }

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
        std::cout << "POWERMETERX" << powerMeter.at(0).getPosition().x << std::endl;
        powerMeter.at(0).setPosition(getPosition().x + 100, getPosition().y);
        std::cout << "AFTER SETPOS POWERMETERX" << powerMeter.at(0).getPosition().x << std::endl;
        powerMeter.at(1).setPosition(getPosition().x + 100, getPosition().y - 32 + 4 + 32 - 32*powerMeter.at(1).getScale().y);

        if (velocity1D > 1) {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }

        powerMeter.at(1).setScale(1, velocity1D/1);
    }

    // While the ball is moving.
    // Collision logic:
    else
    {
        canMove = false;
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

        else {
            setVelocity(0,0);
            int mouseX = 0;
	        int mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            setInitialMousePosition(mouseX, mouseY);
            canMove = true;
        }

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

        // Collision logic with tiles (obstacles):
        // std::cout << "BALL POSITIONX: " << getPosition().x << "TILE POSITIONX:" << t.getPosition().x;
        // std::cout << "BALL POSITIONY: " << getPosition().y << "TILE POSITIONY:" << t.getPosition().y << std::endl;
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

    }

}

// std::vector<Entity> Ball::getPowerMeter() {
//     return powerMeter;
// }

int Ball::getStrokes() {
    return strokes;
}

bool Ball::isWin() {
    return win;
}

// Entity& Ball::getArrow() {
//     return arrow;
// }




