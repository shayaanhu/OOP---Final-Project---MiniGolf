#include "vector2f.hpp"
#include "screen.hpp"
#include "ball.hpp"
#include "hole.hpp"
#include "tile.hpp"
#include "rectangle.hpp"
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
int level = 0;
bool mouseDown = false;
bool mousePressed = false;

// Creating the game screen.
Screen myScreen("MiniGolf", 1000, 650);

// Loading all the textures and creating the game objects.
SDL_Texture* ballTexture = myScreen.loadTexture("assets/ball.png");
SDL_Texture* powerMeterFG = myScreen.loadTexture("assets/powermeterFG.png");
SDL_Texture* powerMeterBG = myScreen.loadTexture("assets/powermeterBG.png");
Ball ball = Ball(Vector2f(0, 0), ballTexture, powerMeterFG, powerMeterBG);

SDL_Texture* arrowTexture = myScreen.loadTexture("assets/arrow.png");
Arrow arrow = Arrow(Vector2f(0,0), arrowTexture);

SDL_Texture* holeTexture = myScreen.loadTexture("assets/hole.png");
Hole hole = Hole(Vector2f(0, 0), holeTexture);

SDL_Texture* tileLightTexture = myScreen.loadTexture("assets/tileLight.png");
std::vector<Tile> tiles = {};
std::vector<Rectangle> rect = {};

SDL_Texture* startScreenTexture = myScreen.loadTexture("assets/start.png");
SDL_Texture* backgroundTexture = myScreen.loadTexture("assets/background.png");
SDL_Texture* endScreenTexture = myScreen.loadTexture("assets/end.png");

// Music:
Mix_Music* backgroundMusic = nullptr;

TTF_Font* loadFont(const std::string& fontPath, int fontSize) 
{
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
    }
    return font;
}

// Fonts
TTF_Font* font = loadFont("assets/font.ttf", 50);
SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};

void loadLevel(int level) {

    ball.setScale(0.2, 0.2);
    hole.setScale(0.175, 0.175);
    arrow.setPosition(-100, -100);

    switch (level) {
        case 0:
        ball.setWin(false);
        tiles.push_back(Tile(Vector2f(125, 150), tileLightTexture));
        tiles.push_back(Tile(Vector2f(125, 50), tileLightTexture));
        tiles.push_back(Tile(Vector2f(325, 150), tileLightTexture));
        tiles.push_back(Tile(Vector2f(325, 50), tileLightTexture));
        hole.setPosition(330, 180);
        break;

        case 1:
        ball.setWin(false);
        rect.push_back(Rectangle(Vector2f(600, -70), Vector2f(600, -20), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(600, 80), Vector2f(600, 130), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(600, 230), Vector2f(600, 280), tileLightTexture));
        hole.setPosition(800, 200);
        break;

        case 2:
        ball.setWin(false);
        rect.push_back(Rectangle(Vector2f(0, -70), Vector2f(0, -20), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(0, 80), Vector2f(0, 130), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(0, 230), Vector2f(0, 280), tileLightTexture));
        hole.setPosition(0, 200);
        break;

        case 3:
        ball.setWin(false);
        tiles.push_back(Tile(Vector2f(225, -25), tileLightTexture));
        tiles.push_back(Tile(Vector2f(225, 200), tileLightTexture));
        hole.setPosition(330, 180);
        break;

        case 4:
        ball.setWin(false);
        state = 2;
        break;
    }
}

void loadMusic() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl; }

    backgroundMusic = Mix_LoadMUS("assets/music.mp3"); // Replace with the actual path to your music file
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
                    if (state == 0) state = 1;
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

    if (state == 1) ball.update(deltaTime, mouseDown, mousePressed, hole, tiles, rect, arrow);

    // When ball is in the hole, proceed to the next level.
    // std::cout << ball.getScale().x << " " << ball.getScale().y;
    if (ball.getWin() == true and ball.getScale().x < - 5 or ball.getScale().y < - 5) {
        level++;
        loadLevel(level);
    }

}

void graphics() {
    myScreen.clear();

    if (state == 0) myScreen.render(0, 0, startScreenTexture);

    else if (state == 2) {
        myScreen.render(0, 0, endScreenTexture);
        // myScreen.renderCenter(0, 3 - 32, "YOU COMPLETED THE COURSE!", font, black);
    }

    else if (state == 1) { 
        myScreen.render(0, 0, backgroundTexture);
        myScreen.render(arrow);
        myScreen.render(ball);
        myScreen.render(hole);

        for (Tile& t : tiles) {
            myScreen.render(t);
        }

        for (Rectangle& r : rect) {
            r.render(myScreen);
        }

        for (Entity& e : ball.getPowerMeter()) {
            myScreen.render(e);
        }
    }

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







