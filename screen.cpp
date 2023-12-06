#include "screen.hpp"

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

Screen::~Screen() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Texture* Screen::loadTexture(const char* filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == nullptr) {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

void Screen::clear() {
	SDL_RenderClear(renderer);
}

void Screen::display() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Screen::getRenderer() {
    return renderer;
}

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






