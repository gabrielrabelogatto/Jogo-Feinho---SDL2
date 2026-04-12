#include "./H/magia_negra.h"

Magia_Negra::Magia_Negra(int x_, int y_, int velocidade_, SDL_Surface* skin_, int largura_, int altura_) {
    this->x = x_;
    this->y = y_;
    this->velocidade = velocidade_;
    this->skin = skin_;
    this->largura = largura_;
    this->altura = altura_;
}

void draw(SDL_Surface* dentro) {
    SDL_Rect pos = {x, y, largura, altura};
    SDL_BlitScaled(skin, NULL, dentro, &pos);
}