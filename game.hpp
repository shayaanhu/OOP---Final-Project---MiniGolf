// #pragma once

// #include "vector2f.hpp"
// #include "screen.hpp"
// #include "ball.hpp"
// #include "hole.hpp"
// #include "tile.hpp"
// #include "arrow.hpp"
// #include <SDL.h>
// #include <vector>

// class Game
// {
// public:
//     Game();
//     ~Game();

//     void run();

// private:
//     void loadTextures();
//     void loadLevel(int level);
//     void update();
//     void graphics();

//     Uint64 currentTick;
//     Uint64 lastTick;
//     double deltaTime;
//     SDL_Event event;
//     bool gameRunning;
//     int state; // 0 = title screen, 1 = game, 2 = end screen
//     bool mouseDown;
//     bool mousePressed;

//     // Creating the game screen.
//     Screen myScreen;

//     // For loading all the textures and creating the game objects.
//     // SDL_Texture* ballTexture;
//     // Ball ball;

//     // SDL_Texture* arrowTexture;
//     // Arrow arrow;

//     // SDL_Texture* holeTexture;
//     // Hole hole;

//     // SDL_Texture* tileLightTexture;
//     // std::vector<Tile> tiles;

//     // SDL_Texture* backgroundTexture;
// };
