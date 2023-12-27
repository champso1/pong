#include "Ball.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Ball::Ball(const Vector2f& p_pos, const Vector2f& p_vel, SDL_Texture* p_tex)
    : pos(p_pos), vel(p_vel), tex(p_tex) {}

void Ball::update() {
    pos.x += vel.x;
    pos.y += vel.y;
}
