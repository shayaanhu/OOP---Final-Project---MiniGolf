#include "vector2f.hpp"
#include "screen.hpp"
#include "ball.hpp"
#include "hole.hpp"
#include "tile.hpp"
#include "arrow.hpp"
#include "powermeter.hpp"
#include "entity.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;
SDL_Event event;
bool gameRunning = true;
int state = 0; //0 = title screen, 1 = game, 2 = end screen
bool mouseDown = false;
bool mousePressed = false;

// Creating the game screen.
Screen myScreen("MiniGolf", 1000, 650);

// Loading all the textures and creating the game objects.
SDL_Texture* ballTexture = myScreen.loadTexture("ball.png");
SDL_Texture* powerMeterFG = myScreen.loadTexture("powermeterFG.png");
SDL_Texture* powerMeterBG = myScreen.loadTexture("powermeterBG.png");
Ball ball = Ball(Vector2f(0, 0), ballTexture, powerMeterFG, powerMeterBG);

SDL_Texture* arrowTexture = myScreen.loadTexture("point.png");
Arrow arrow = Arrow(Vector2f(0,0), arrowTexture);

SDL_Texture* holeTexture = myScreen.loadTexture("hole.png");
Hole hole = Hole(Vector2f(0, 0), holeTexture);

SDL_Texture* tileLightTexture = myScreen.loadTexture("tileLight.png");
std::vector<Tile> tiles = {};

SDL_Texture* backgroundTexture = myScreen.loadTexture("backTest.png");

void loadLevel(int level) {

    ball.setScale(0.2, 0.2);
    hole.setScale(0.175, 0.175);
    arrow.setPosition(-100, -100);
    // powerMeter.push_back(Powermeter(Vector2f(0,0), powerMeterFG));
    // powerMeter.push_back(Powermeter(Vector2f(0,0), powerMeterBG));
    // powerMeter.at(0).setPosition(400, 100);
    // powerMeter.at(1).setPosition(200, 200);

    switch (level) {
        case 0:
        tiles.push_back(Tile(Vector2f(200, 200), tileLightTexture));
        // tiles.push_back(Tile(Vector2f(144, 200), tileLightTexture));
        tiles.push_back(Tile(Vector2f(200, 100), tileLightTexture));
        tiles.push_back(Tile(Vector2f(380, 200), tileLightTexture));
        tiles.push_back(Tile(Vector2f(380, 100), tileLightTexture));
        hole.setPosition(350, 200);
        break;

        case 1:
        break;

        case 2:
        break;
    }
}

void update() {
    lastTick = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

    mousePressed = false;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = true;
                    mousePressed = true;
                }   
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                }
                break;
        }
    }

    arrow.setPosition(-100, -100); // Setting the arrow's position outside the screen while not in use.
    ball.update(deltaTime, mouseDown, mousePressed, hole, tiles, arrow);
}

void graphics() {
    myScreen.clear();
    myScreen.render(0, 0, backgroundTexture);
    myScreen.render(arrow);
    myScreen.render(ball);
    myScreen.render(hole);

    for (Tile& t : tiles) {
        myScreen.render(t);
    }

    for (Entity& e : ball.getPowerMeter()) {
        myScreen.render(e);
    }

    // render powermeter

    myScreen.display();

}

int main(int argc, char* argv[]) {

    // Locking the FPS to roughly 120 (saves GPU power).
	const int targetFPS = 140;
    const int delayTime = 1000 / targetFPS;
	loadLevel(0);

    while (gameRunning) {
    	update();
        graphics();
		SDL_Delay(delayTime);
    }
    
    return 0;
}


// #include "game.hpp"

// int main(int argc, char* argv[])
// {
//     Game game;
//     game.run();

//     return 0;
// }

