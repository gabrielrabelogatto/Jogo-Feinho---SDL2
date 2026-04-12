#ifndef MAGIANEGRA_H
#define MAGIANEGRA_H

#include <SDL2/SDL.h>

class Magia_Negra {
    public:
        int x, y, velocidade, largura, altura;
        SDL_Surface* skin = NULL;

        Magia_Negra(int x_, int y_, int velocidade_, SDL_Surface* skin_, int largura_, int altura_);

        void draw(SDL_Surface* dentro);
};

#endif