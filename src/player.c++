#include "./H/player.h"

Player::Player(int x_, int y_, SDL_Surface* skin_, int largura_, int altura_) {
        this->x = x_;
        this->y = y_;
        this->skin = skin_;
        this->largura = largura_;
        this->altura = altura_;
}

void Player::draw(SDL_Surface* dentro) {
    SDL_Rect pos = { x, y, largura, altura };
    SDL_BlitScaled(skin, NULL, dentro, &pos);
}

void Player::movimento(float velocidade) {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LEFT])  x -= velocidade;
    if (state[SDL_SCANCODE_RIGHT]) x += velocidade;
    if (state[SDL_SCANCODE_UP])    y -= velocidade;
    if (state[SDL_SCANCODE_DOWN])  y += velocidade;
}