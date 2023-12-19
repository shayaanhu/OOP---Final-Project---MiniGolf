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

// Our ball and its powerMeter.
SDL_Texture* ballTexture = myScreen.loadTexture("assets/ball.png");
SDL_Texture* powerMeterFG = myScreen.loadTexture("assets/powermeterFG.png");
SDL_Texture* powerMeterBG = myScreen.loadTexture("assets/powermeterBG.png");
Ball ball = Ball(Vector2f(0, 0), ballTexture, powerMeterFG, powerMeterBG);

// Arrow which points in the direction the ball will be launched in.
SDL_Texture* arrowTexture = myScreen.loadTexture("assets/arrow.png");
Arrow arrow = Arrow(Vector2f(0,0), arrowTexture);

// The hole which the player has to put the ball in.
SDL_Texture* holeTexture = myScreen.loadTexture("assets/hole.png");
Hole hole = Hole(Vector2f(0, 0), holeTexture);

// Tiles (obstacles) that the ball collides with.
SDL_Texture* tileLightTexture = myScreen.loadTexture("assets/tileLight.png");
std::vector<Tile> tiles = {};
std::vector<Rectangle> rect = {};

// Screens.
SDL_Texture* startScreenTexture = myScreen.loadTexture("assets/start.png");
SDL_Texture* backgroundTexture = myScreen.loadTexture("assets/background.png");
SDL_Texture* endScreenTexture = myScreen.loadTexture("assets/end.png");

// Music:
Mix_Music* backgroundMusic = nullptr;

// Function to load font (we were unable to load fonts because of "Library failed to initialize" error.)
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

// Function which loads levels.
void loadLevel(int level) {

    // Setting the scales as the pngs were too big.
    ball.setScale(0.2, 0.2);
    hole.setScale(0.175, 0.175);

    // Setting the arrow's position outside the screen as its not in use.
    arrow.setPosition(-100, -100);

    // Pushing back tiles/rectangles to create obstacles.
    // Setting the position for the hole based on the level.
    // Setting the win to false each time a new level is loaded.
    switch (level) {
        case 0:
        tiles.push_back(Tile(Vector2f(125, 150), tileLightTexture));
        tiles.push_back(Tile(Vector2f(125, 50), tileLightTexture));
        tiles.push_back(Tile(Vector2f(325, 150), tileLightTexture));
        tiles.push_back(Tile(Vector2f(325, 50), tileLightTexture));
        hole.setPosition(330, 180);
        ball.setWin(false);
        break;

        case 1:
        rect.push_back(Rectangle(Vector2f(600, -70), Vector2f(600, -20), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(600, 80), Vector2f(600, 130), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(600, 230), Vector2f(600, 280), tileLightTexture));
        hole.setPosition(800, 200);
        ball.setWin(false);
        break;

        case 2:
        rect.push_back(Rectangle(Vector2f(0, -70), Vector2f(0, -20), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(0, 80), Vector2f(0, 130), tileLightTexture));
        rect.push_back(Rectangle(Vector2f(0, 230), Vector2f(0, 280), tileLightTexture));
        hole.setPosition(0, 200);
        ball.setWin(false);
        break;

        case 3:
        tiles.push_back(Tile(Vector2f(225, -25), tileLightTexture));
        tiles.push_back(Tile(Vector2f(225, 200), tileLightTexture));
        hole.setPosition(330, 180);
        ball.setWin(false);
        break;

        // Final state, when the player completes the course.
        case 4:
        ball.setWin(false);
        state = 2;
        break;
    }
}

// Function to load music.
void loadMusic() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl; }

    backgroundMusic = Mix_LoadMUS("assets/music.mp3"); // Replace with the actual path to your music file
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
    }

}

// Function to clean up resources once the game is closed.
void cleanup() {
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
    }
    IMG_Quit(); // Clean up SDL_image
    Mix_CloseAudio(); // Clean up SDL_mixer
    SDL_Quit(); // SDL_Quit should be here
}

// Function to play the background music.
void playMusic() {
    Mix_PlayMusic(backgroundMusic, -1); // -1 means loop indefinitely
}

// The main update function that constantly runs.
// Checks states and wether or not the close button is pressed.
// Increments levels based on the ball's scale.
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

// Our function to render everything.
void graphics() {
    myScreen.clear();

    // Start screen.
    if (state == 0) myScreen.render(0, 0, startScreenTexture);

    // End screen.
    else if (state == 2) {
        myScreen.render(0, 0, endScreenTexture);
        // myScreen.renderCenter(0, 3 - 32, "YOU COMPLETED THE COURSE!", font, black);
    }

    // Game running state.
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
