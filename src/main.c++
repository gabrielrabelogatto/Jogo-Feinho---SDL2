#include <SDL2/SDL.h>

#include <iostream>
#include <chrono>

#include "./H/player.h"
#include "./H/barreira.h"

int const SCREEN_WIDTH = 1200;
int const SCREEN_HEIGHT = 700;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gSkinPlayer = NULL;
SDL_Surface* gSkinBarreira = NULL;

bool init();
bool loadMedia();
bool close();

int main(int argc, char** argv) {
    if ( !init() ) {
        std::cout << "Falha ao tentar iniciar o programa";
    } else {
        if ( !loadMedia() ) {
            std::cout << "Falha ao tentar carregar os assets do programa";
        } else {
            Player player(350, 250, gSkinPlayer, 200, 200);
            Barreira barreira(1200.0f, 350, gSkinBarreira, 1200, 400, 3.5f, "assets/Barreira.bmp");

            SDL_Event e;
            bool quit = false;

            Uint32 intervalo = 3000;
            Uint32 tempoAnterior = SDL_GetTicks();
            Uint32 tempoAtual;

            Uint32 intervaloVoltar = 3000;
            Uint32 tempoAnteriorVoltar = SDL_GetTicks();
            Uint32 tempoAtualVoltar;

            while ( quit == false ) {
                while ( SDL_PollEvent(&e) ) {
                    if ( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                }

                barreira.aparecer(intervalo, tempoAtual, tempoAnterior, intervaloVoltar, tempoAtualVoltar, tempoAnteriorVoltar);
                player.movimento(2.0f);

                SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 255, 255, 255));

                player.draw(gScreenSurface);
                barreira.draw(gScreenSurface, 0);
                
                SDL_UpdateWindowSurface(gWindow);
                SDL_Delay(16);
            }
        }
    }

    close();
    return 0;
}

bool init() {
    bool success = true;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::cout << "Erro SDL: " << SDL_GetError();
        success = false;
    } else {
        gWindow = SDL_CreateWindow( "Jogo feinho", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        if ( gWindow == NULL ) {
            std::cout << "Erro na janela: " << SDL_GetError();
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    gSkinPlayer = SDL_LoadBMP("assets/Player.bmp");
    if(gSkinPlayer == NULL) {
        std::cout << "A imagem 'assets/Player.bmp' não foi encontrada. Erro do SDL2: " << SDL_GetError() << std::endl;
        success = false;
    }

    gSkinBarreira = SDL_LoadBMP("assets/Barreira.bmp");
    if(gSkinBarreira == NULL) {
        std::cout << "A imagem 'assets/Barreira.bmp' não foi encontrada. Erro do SDL2: " << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

bool close() {
    if(gSkinPlayer != NULL) {
        SDL_FreeSurface(gSkinPlayer);
        gSkinPlayer = NULL;
    }

    if(gSkinBarreira != NULL) {
        SDL_FreeSurface(gSkinBarreira);
        gSkinBarreira = NULL;
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();

    return true;
}