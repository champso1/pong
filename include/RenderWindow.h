#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Ball.h"
#include "Paddle.h"

class RenderWindow {
public:
    RenderWindow(const char* p_title, const int& p_w, const int& p_h);
    void cleanUp();
    void clear();
    void display();

    SDL_Texture* loadTexture(const char* p_filePath);
    void render(Ball& ball);
    void render(Paddle& paddle);
    void reset(Paddle& left_paddle, Paddle& right_paddle, Ball& ball);

    void handleInput(SDL_Event& event, Paddle& left_paddle, Paddle& right_paddle, Ball&ball, bool& running);
    void checkCollision(Paddle& left_paddle, Paddle& right_paddle, Ball& ball);
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
};