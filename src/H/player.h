#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
    public:
        int x, y, largura, altura;

        SDL_Surface* skin;

        Player(int x_, int y_, SDL_Surface* skin_, int largura, int altura);

        void draw(SDL_Surface* dentro);

        void movimento(float velocidade);
};

#endif