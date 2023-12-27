#include "RenderWindow.h"

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Ball.h"
#include "Paddle.h"

const float VELOCITY = 7.5f;
const int WIDTH = 800;
const int HEIGHT = 600;

RenderWindow::RenderWindow(const char* p_title, const int& p_w, const int& p_h)
    : window(NULL), renderer(NULL) {

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL)
        std::cout << "Window init failed: " << SDL_GetError() << std::endl;


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


}   

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
        std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::render(Ball& ball) {
    SDL_Rect src;
	src.x = 0;
	src.y = 0;
    SDL_QueryTexture(ball.getTex(), NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = ball.getPos().x;
	dst.y = ball.getPos().y;
	dst.w = 15;
	dst.h = 15;
    ball.setCurrentFrame(dst);

    ball.update();

	//SDL_SetTextureBlendMode(ball.getTex(), SDL_BLENDMODE_NONE);
    SDL_RenderCopy(renderer, ball.getTex(), &src, &dst);
}   

void RenderWindow::render(Paddle& paddle) {
    SDL_Rect src;
	src.x = 0;
	src.y = 0;
    SDL_QueryTexture(paddle.getTex(), NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = paddle.getPos().x;
    dst.y = paddle.getPos().y;
    dst.w = src.w * 1.5;
    dst.h = src.h * 2;
    paddle.setCurrentFrame(dst);

    paddle.update();

    SDL_RenderCopy(renderer, paddle.getTex(), &src, &dst);
}

void RenderWindow::reset(Paddle& left_paddle, Paddle& right_paddle, Ball& ball) {
    srand(time(NULL));
    ball.setPos(Vector2f(WIDTH/2, HEIGHT/2));
    ball.setVel(Vector2f(5.0f, rand()%3+3));

    left_paddle.setPos(Vector2f(10, WIDTH/2-50));
    right_paddle.setPos(Vector2f(WIDTH-25, WIDTH/2-50));
}


void RenderWindow::handleInput(SDL_Event& event, Paddle& left_paddle, Paddle& right_paddle, Ball& ball, bool& running) {
    switch (event.type) {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_s:
                left_paddle.setVelY(VELOCITY);
                break;
            case SDLK_w:
                left_paddle.setVelY(-VELOCITY);
                break;
            case SDLK_UP:
                right_paddle.setVelY(-VELOCITY);
                break;
            case SDLK_DOWN:
                right_paddle.setVelY(VELOCITY);
                break;
            case SDLK_r:
                reset(left_paddle, right_paddle, ball);
                break;
            default:
                break;
        }
        break;
    case SDL_KEYUP:
        switch (event.key.keysym.sym) {
            case SDLK_s:
                left_paddle.setVelY(0);
                break;
            case SDLK_w:
                left_paddle.setVelY(0);
                break;
            case SDLK_UP:
                right_paddle.setVelY(0);
                break;
            case SDLK_DOWN:
                right_paddle.setVelY(0);
                break;
            default:
                break;
        }
        break;
    default:
        break;
    }

}

void RenderWindow::checkCollision(Paddle& left_paddle, Paddle& right_paddle, Ball& ball) {
    
    //x
    if (ball.getPos().x + ball.getCurrentFrame().w >= right_paddle.getPos().x &&
        ball.getPos().y >= right_paddle.getPos().y &&
        ball.getPos().y <= right_paddle.getPos().y + right_paddle.getCurrentFrame().h)
            ball.setVel(Vector2f(-ball.getVel().x, ball.getVel().y));
    if (ball.getPos().x <= left_paddle.getPos().x + left_paddle.getCurrentFrame().w &&
        ball.getPos().y >= left_paddle.getPos().y &&
        ball.getPos().y <= left_paddle.getPos().y + left_paddle.getCurrentFrame().h)
            ball.setVel(Vector2f(-ball.getVel().x, ball.getVel().y));

    //y
    if (ball.getPos().x + ball.getCurrentFrame().w/2 + ball.getVel().x >= left_paddle.getPos().x &&
        ball.getPos().x + ball.getCurrentFrame().w/2 + ball.getVel().x <= left_paddle.getPos().x + left_paddle.getCurrentFrame().w &&
        (ball.getPos().y + ball.getCurrentFrame().h + ball.getVel().y >= left_paddle.getPos().y ||
        ball.getPos().y + ball.getVel().y <= left_paddle.getPos().y + left_paddle.getCurrentFrame().h))
            ball.setVel(Vector2f(ball.getVel().x, -ball.getVel().y));
    if (ball.getPos().x + ball.getCurrentFrame().w/2 + ball.getVel().x >= right_paddle.getPos().x &&
        ball.getPos().x + ball.getCurrentFrame().w/2 + ball.getVel().x <= right_paddle.getPos().x + right_paddle.getCurrentFrame().w &&
        ((ball.getPos().y + ball.getCurrentFrame().h < right_paddle.getPos().y && ball.getPos().y + ball.getCurrentFrame().h + ball.getVel().y >= right_paddle.getPos().y) ||
        (ball.getPos().y > right_paddle.getPos().y + right_paddle.getCurrentFrame().h && ball.getPos().y + ball.getVel().y <= right_paddle.getPos().y + right_paddle.getCurrentFrame().h)))
            ball.setVel(Vector2f(ball.getVel().x, -ball.getVel().y));
     
    //top and bottom of screen
    if (ball.getPos().y + ball.getCurrentFrame().h >= HEIGHT ||
        ball.getPos().y <= 0)
            ball.setVel(Vector2f(ball.getVel().x, -ball.getVel().y));
    
    //restricts paddle movement
    if (left_paddle.getPos().y + left_paddle.getVelY() <= 5 ||
        left_paddle.getPos().y + left_paddle.getCurrentFrame().h + left_paddle.getVelY() >= HEIGHT-5)
            left_paddle.setVelY(0);
    if (right_paddle.getPos().y + right_paddle.getVelY() <= 5 ||
        right_paddle.getPos().y + right_paddle.getCurrentFrame().h + right_paddle.getVelY() >= HEIGHT-5)
            right_paddle.setVelY(0); 
        
}