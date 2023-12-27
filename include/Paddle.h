#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.h"

class Paddle {
public:
    Paddle(const Vector2f& pos, SDL_Texture* p_tex);
    Vector2f& getPos() {return pos;}
    void setPos(const Vector2f new_pos) {
        pos = new_pos;
    }
    SDL_Texture* getTex() {return tex;}
    float getVelY() {return velY;}
    void setVelY(const float& p_velY);
    void update();
    void setCurrentFrame(const SDL_Rect& p_current_frame) {
        current_frame = p_current_frame;
    }
    SDL_Rect& getCurrentFrame() {return current_frame;}
private:
    SDL_Texture* tex;
    Vector2f pos;
    float velY;
    SDL_Rect current_frame;
};