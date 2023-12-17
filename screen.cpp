#include "screen.hpp"

// Constructor for the Screen class, initializes SDL window and renderer.
Screen::Screen(const char* p_title, int p_w, int p_h) : window(nullptr), renderer(nullptr) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

// Destructor for the Screen class, cleans up SDL window and renderer.
Screen::~Screen() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

// Load a texture from a file path and return the SDL_Texture pointer.
SDL_Texture* Screen::loadTexture(const char* filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == nullptr) {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

// Clear the renderer, preparing for the next frame.
void Screen::clear() {
	SDL_RenderClear(renderer);
}

// Present the renderer, displaying the rendered frame.
void Screen::display() {
    SDL_RenderPresent(renderer);
}

// Get the SDL_Renderer associated with the Screen.
SDL_Renderer* Screen::getRenderer() {
    return renderer;
}

// Render an Entity on the screen, handling position, scale, rotation, and flipping.
void Screen::render(Entity& p_entity) {
	SDL_Rect src; 
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPosition().x + (p_entity.getCurrentFrame().w - p_entity.getCurrentFrame().w*p_entity.getScale().x)/2;
	dst.y = p_entity.getPosition().y + (p_entity.getCurrentFrame().h - p_entity.getCurrentFrame().h*p_entity.getScale().y)/2;
	dst.w = p_entity.getCurrentFrame().w*p_entity.getScale().x;
	dst.h = p_entity.getCurrentFrame().h*p_entity.getScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}

// Render an SDL_Texture at a specific position on the screen.
void Screen::render(int x, int y, SDL_Texture* p_tex) {
	SDL_Rect src; 
	src.x = 0;
	src. y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

// Render centered text on the screen using the given TTF_Font and SDL_Color.
void Screen::renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h; 

		SDL_Rect dst;
		dst.x = 640/2 - src.w/2 + p_x;
		dst.y = 480/2 - src.h/2 + p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
}





