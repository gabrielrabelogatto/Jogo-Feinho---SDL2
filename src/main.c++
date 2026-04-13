#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <ctime>
#include <vector>
#include <any>

#include "./H/player.h"
#include "./H/barreira.h"
#include "./H/timer.h"
#include "./H/magia_negra.h"

int const SCREEN_WIDTH = 1200;
int const SCREEN_HEIGHT = 700;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

Mix_Music* gMusica_Game = NULL;
SDL_Surface* gSkinPlayer = NULL;
SDL_Surface* gSkinBarreira = NULL;
SDL_Surface* gSkinMagia_Negra = NULL;

std::vector<std::any> gTimer_Spawn_MagiaNegra;

bool init();
bool loadMedia();
bool close();

void spawn_magiaNegra(Magia_Negra* gMagia_negra);

int main(int argc, char** argv) {
    srand(time(0));

    if ( !init() ) {
        std::cout << "Falha ao tentar iniciar o programa";
    } else {
        if ( !loadMedia() ) {
            std::cout << "Falha ao tentar carregar os assets do programa";
        } else {
            Player player(350, 250, gSkinPlayer, 200, 200);
            Barreira barreira(1200.0f, 350, gSkinBarreira, 1200, 400, 10.5f, "assets/Barreira.bmp", 0);
            Magia_Negra gMagia_negra(5, gSkinMagia_Negra, 100, 100);

            SDL_Event e;
            bool quit = false;

            Uint32 intervalo = 3000;
            Uint32 tempoAnterior = SDL_GetTicks();
            Uint32 tempoAtual;

            Uint32 intervaloVoltar = 3000;
            Uint32 tempoAnteriorVoltar = SDL_GetTicks();
            Uint32 tempoAtualVoltar;

            timer_config(&gTimer_Spawn_MagiaNegra, 2000, true);

            if(gMusica_Game != NULL) {
                Mix_PlayMusic(gMusica_Game, -1);
            }

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

                spawn_magiaNegra(&gMagia_negra);
                
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

    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        std::cout << "Erro SDL: " << SDL_GetError();
        success = false;
    } else {
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cout << "Erro ao tentar inicializar o audio: " << SDL_GetError();
            success = false;
        }
        
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

    gMusica_Game = Mix_LoadMUS("assets/Musica_Game.wav");
    if(gMusica_Game == NULL) {
        std::cout << "A musica 'assets/Musica_Game.wav' não foi encontrada. Erro do SDL2: " << SDL_GetError() << std::endl;
        success = false;
    }

    gSkinMagia_Negra = SDL_LoadBMP("assets/Magia negra.bmp");
    if(gSkinMagia_Negra == NULL) {
        std::cout << "O asset 'assets/Magia negra.bmp' não foi encontrada. Erro do SDL2: " << SDL_GetError() << std::endl;
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

    if(gMusica_Game != NULL) {
        Mix_FreeMusic(gMusica_Game);
        gMusica_Game = NULL;
    }

    if(gSkinMagia_Negra != NULL) {
        SDL_FreeSurface(gSkinBarreira);
        gSkinMagia_Negra = NULL;
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    Mix_CloseAudio();
    SDL_Quit();

    return true;
}

void spawn_magiaNegra(Magia_Negra* gMagia_negra) {
    timer_iniciarCronometro(&gTimer_Spawn_MagiaNegra);

    if(gMagia_negra->create == true) {
        gMagia_negra->draw(gScreenSurface, 100, 100);
    }

    if(timer_verificar(&gTimer_Spawn_MagiaNegra)) {
        gMagia_negra->create = true;
    }
}