#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.h"

class Ball {
public:
    Ball(const Vector2f& p_pos, const Vector2f& p_vel, SDL_Texture* p_tex);
    Vector2f& getPos() {return pos;}
    Vector2f& getVel() {return vel;}
    void setVel(const Vector2f& p_vel) {
        vel = p_vel;
    }
    void setPos(const Vector2f& new_pos) {
        pos = new_pos;
    }
    SDL_Texture* getTex() {return tex;};
    void update(); 
    SDL_Rect& getCurrentFrame() {return current_frame;}
    void setCurrentFrame(const SDL_Rect& p_frame) {
        current_frame = p_frame;
    };
private:
    SDL_Rect current_frame;
    Vector2f pos;
    Vector2f vel;
    SDL_Texture* tex;
};