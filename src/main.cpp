#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.h"
#include "Math.h"
#include "Ball.h"
#include "Paddle.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const float VELOCITY = 3.0f;



int main(int argc, char* argv[]) {
    srand(time(0));

    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init has failed: " << SDL_GetError() << std::endl;

    RenderWindow window("Pong", WIDTH, HEIGHT);

    SDL_Texture* ball_texture = window.loadTexture("gfx/ball.png");
    SDL_Texture* paddle_texture = window.loadTexture("gfx/paddle.png");

    
    Ball ball(Vector2f(WIDTH/2, HEIGHT/2), Vector2f(VELOCITY, rand()%3+5), ball_texture);
    Paddle left_paddle(Vector2f(10, HEIGHT/2-50), paddle_texture);
    Paddle right_paddle(Vector2f(WIDTH-25, HEIGHT/2-50), paddle_texture);


    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            window.handleInput(event, left_paddle, right_paddle, ball, running);
        }

        window.clear();
        window.checkCollision(left_paddle, right_paddle, ball);
        window.render(ball);
        window.render(left_paddle);
        window.render(right_paddle);
        window.display();

    }

    window.cleanUp();
    SDL_Quit();

    return EXIT_SUCCESS;
}

