#include "Paddle.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.h"

Paddle::Paddle(const Vector2f& p_pos, SDL_Texture* p_tex)
    : pos(p_pos), tex(p_tex), velY(0.0f) {}

void Paddle::setVelY(const float& p_velY) {
    velY = p_velY;
}

void Paddle::update() {
    pos.y += velY;
}
