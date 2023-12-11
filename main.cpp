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
#include <SDL_mixer.h>

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
std::vector<Rectangle> rect = {};

SDL_Texture* backgroundTexture = myScreen.loadTexture("backTest.png");
Mix_Music* backgroundMusic = nullptr;

void loadLevel(int level) {

    ball.setScale(0.2, 0.2);
    hole.setScale(0.175, 0.175);
    arrow.setPosition(-100, -100);
    powerMeter.push_back(Entity(Vector2f(0,0), powerMeterBG));
    powerMeter.push_back(Entity(Vector2f(0,0), powerMeterFG));

    switch (level) {
        case 0:
        tiles.push_back(Tile(Vector2f(350, 100), tileLightTexture));
        tiles.push_back(Tile(Vector2f(230, 100), tileLightTexture));
        tiles.push_back(Tile(Vector2f(350, 200), tileLightTexture));
        tiles.push_back(Tile(Vector2f(230, 200), tileLightTexture));
        hole.setPosition(350, 200);

        tiles.push_back(Tile(Vector2f(550, 40), tileLightTexture));
        tiles.push_back(Tile(Vector2f(570, 200), tileLightTexture));

        

        
        break;

        // case 1:
        tiles.push_back(Tile(Vector2f(550, 40), tileLightTexture));
        tiles.push_back(Tile(Vector2f(570, 200), tileLightTexture));
        tiles.push_back(Tile(Vector2f(600, 120), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(480, 100), Vector2f(480, 150), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(660, 100), Vector2f(660, 150), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(635, 40), Vector2f(685, 40), tileLightTexture));
        hole.setPosition(600, 180);
        

        
        break;

        case 2:
        tiles.push_back(Tile(Vector2f(165, 375), tileLightTexture));
        tiles.push_back(Tile(Vector2f(590, 375), tileLightTexture));
        tiles.push_back(Tile(Vector2f(510, 390), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(100, 340), Vector2f(100, 390), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(35, 220), Vector2f(35, 270), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(120, 200), Vector2f(120, 250), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(300, 250), Vector2f(350, 250), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(420, 200), Vector2f(470, 200), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(535, 250), Vector2f(585, 250), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(180, 200), Vector2f(230, 200), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(650, 310), Vector2f(650, 360), tileLightTexture));
        hole.setPosition(400, 470);
        break;
    }
}
void loadMusic() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
    // cleanup();
    // return -1;
    }

    backgroundMusic = Mix_LoadMUS("C:\\Users\\coolm\\Desktop\\Project\\Project\\back.mp3"); // Replace with the actual path to your music file
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
    }
}
void cleanup() {
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
    }
    IMG_Quit(); // Clean up SDL_image
    Mix_CloseAudio(); // Clean up SDL_mixer
    SDL_Quit(); // SDL_Quit should be here
}
void playMusic() {
    Mix_PlayMusic(backgroundMusic, -1); // -1 means loop indefinitely
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
	loadMusic();
	playMusic();
    
	while (gameRunning) {
    		update();
        	graphics();
		SDL_Delay(delayTime);
    	}
	cleanup();
    
    return 0;
}


// #include "game.hpp"

// int main(int argc, char* argv[])
// {
//     Game game;
//     game.run();

//     return 0;
// }

