#include "./H/barreira.h"
#include <iostream>

Barreira::Barreira(float x_, int y_, SDL_Surface* skin_, int largura_, int altura_, float velocidade_, std::string urlSkin_, float y_segundo_) {
    this->x = x_;
    this->y = y_;
    this->skin = skin_;
    this->largura = largura_;
    this->altura = altura_;
    this->velocidade = velocidade_;
    this->limite_voltar = x_;
    this->urlSkin = urlSkin_;
    this->y_segundo = y_segundo_;
};

void Barreira::draw(SDL_Surface* dentro, int limite__) {
    limite = limite__;
    if (isVisible == true) {
        if(sorteio == 0) {
            SDL_Rect pos = { (int)x, y, largura, altura };
            SDL_BlitScaled(skin, NULL, dentro, &pos);
        } else if(sorteio == 1) {
            SDL_Rect pos = { (int)x, y_segundo, largura, altura };
            SDL_BlitScaled(skin, NULL, dentro, &pos);
        }
    }
};

void Barreira::aparecer(Uint32 intervalo, Uint32 tempoAtual, Uint32 &tempoAnterior, Uint32 intervaloVoltar, Uint32 tempoAtualVoltar, Uint32 &tempoAnteriorVoltar) {
    if(skin == NULL) {
        skin = SDL_LoadBMP(urlSkin.c_str());
        if(skin == NULL) {
            std::cout << "A imagem 'assets/Barreira.bmp' não foi encontrada. Erro do SDL2: " << SDL_GetError() << std::endl;
        }
    }
    
    if(modo == "Ir") {
        if(sorteou == false) {
            sorteio = rand() % 2;
            sorteou = true;
        }

        tempoAtual = SDL_GetTicks();

        if(tempoAtual - tempoAnterior >= intervalo) {
            // std::cout << "Deu o tempo" << std::endl;
            spawnBarreira();

            tempoAnterior = tempoAtual;
        }

        if(isMovie == true && x > limite) {
            x -= velocidade;
            //std::cout << "Posição x: " << x << std::endl;
        } else if(isMovie == true && x <= limite && auciliar_isMovie2 == true) {
            auciliar_isMovie2 = false;
            isMovie = false;
            auciliar_isMovie = true;
            
            modo = "Voltar";
            tempoAnteriorVoltar = SDL_GetTicks();
        }
    } else if(modo == "Voltar") {
        tempoAtualVoltar = SDL_GetTicks();
        if(tempoAtualVoltar - tempoAnteriorVoltar >= intervaloVoltar && auciliar_isMovie == true) {
            //std::cout << "Deu o tempo" << std::endl;
            voltarBarreira();

            tempoAnteriorVoltar = tempoAtualVoltar;
        }

        if(isMovie_voltar == true) {
            if(x < limite_voltar) {
                x += velocidade;
            } else {
                modo = "Finalizar";
            }
        }
    } else if(modo == "Finalizar") {
        isVisible = false;

        isMovie = false;
        auciliar_isMovie2 = true;
        auciliar_isMovie = false;
        isMovie_voltar = false;
        sorteou = false;

        x = 1200.0f;
        modo = "Ir";

        tempoAnterior = SDL_GetTicks();

        voltarMovie = false;
        if(skin != NULL) {
            SDL_FreeSurface(skin);
            skin = NULL;

            //std::cout << "Skin Barreira é removido do jogo" << std::endl;
        }
    }
}

void Barreira::spawnBarreira() {
    isVisible = true;
    isMovie = true;
}

void Barreira::voltarBarreira() {
    isMovie_voltar = true;
}