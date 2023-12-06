// #include "game.hpp"

// Game::Game() :
//     myScreen("MiniGolf", 1000, 650),
//     ball(Vector2f(0,0), ballTexture),
//     arrow(Vector2f(0,0), arrowTexture),
//     hole(Vector2f(0,0), holeTexture),
//     tiles({}),
//     backgroundTexture(nullptr)
// {
//     loadTextures();
//     loadLevel(0);
// }

// Game::~Game()
// {
//     // Release resources, such as textures
//     SDL_DestroyTexture(ballTexture);
//     SDL_DestroyTexture(arrowTexture);
//     SDL_DestroyTexture(holeTexture);
//     SDL_DestroyTexture(tileLightTexture);
//     SDL_DestroyTexture(backgroundTexture);
// }

// void Game::loadTextures()
// {
//     ballTexture = myScreen.loadTexture("ball.png");
//     arrowTexture = myScreen.loadTexture("point.png");
//     holeTexture = myScreen.loadTexture("hole.png");
//     tileLightTexture = myScreen.loadTexture("tileLight.png");
//     backgroundTexture = myScreen.loadTexture("backTest.png");
// }

// void Game::loadLevel(int level)
// {
//     ball.setScale(0.2, 0.2);
//     hole.setScale(0.175, 0.175);
//     arrow.setPosition(-100, -100);

//     switch (level) {
//         case 0:
//         tiles.push_back(Tile(Vector2f(200, 200), tileLightTexture));
//         tiles.push_back(Tile(Vector2f(200, 100), tileLightTexture));
//         tiles.push_back(Tile(Vector2f(380, 200), tileLightTexture));
//         tiles.push_back(Tile(Vector2f(380, 100), tileLightTexture));
//         hole.setPosition(350, 200);
//         break;

//         case 1:
//         break;

//         case 2:
//         break;
//     }
// }

// void Game::update()
// {
//     lastTick = currentTick;
//     currentTick = SDL_GetPerformanceCounter();
//     deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

//     mousePressed = false;
//     while (SDL_PollEvent(&event)) {
//         switch (event.type) {
//             case SDL_QUIT:
//                 gameRunning = false;
//                 break;
//             case SDL_MOUSEBUTTONDOWN:
//                 if (event.button.button == SDL_BUTTON_LEFT) {
//                     mouseDown = true;
//                     mousePressed = true;
//                 }   
//                 break;
//             case SDL_MOUSEBUTTONUP:
//                 if (event.button.button == SDL_BUTTON_LEFT) {
//                     mouseDown = false;
//                 }
//                 break;
//         }
//     }

//     arrow.setPosition(-100, -100); // Setting the arrow's position outside the screen while not in use.
//     ball.update(deltaTime, mouseDown, mousePressed, hole, tiles, arrow);
// }

// void Game::graphics()
// {
//     myScreen.clear();
//     myScreen.render(0, 0, backgroundTexture);
//     myScreen.render(arrow);
//     myScreen.render(ball);
//     myScreen.render(hole);

//     for (Tile& t : tiles) {
//         myScreen.render(t);
//     }

//     myScreen.display();
// }

// void Game::run()
// {
//     const int targetFPS = 140;
//     const int delayTime = 1000 / targetFPS;

//     loadLevel(0);

//     while (gameRunning)
//     {
//         // std::cout << "RUNNING";
//         update();
//         graphics();
//         SDL_Delay(delayTime);
//     }
// }
