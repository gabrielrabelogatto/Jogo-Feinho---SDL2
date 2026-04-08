#ifndef BARREIRA_H
#define BARREIRA_H

#include <SDL2/SDL.h>
#include <string>

class Barreira {
    public:
        int y, limite, largura, altura;
        float x, limite_voltar;
        
        SDL_Surface* skin;

        bool isVisible = false;

        bool isMovie = false;
        bool auciliar_isMovie2 = true; //isto esta totalmente quebrado, esta variavel não precisava existir, só vai deixar mais dificil depois, mas estou cansado e quero terminar logo, GABRIEL DO FUTURO resolva isto depois, porque não é mais problema meu
        bool auciliar_isMovie = false; //para verificar ele voltar precisamos desta variavel, se acabar com ela, tudo acaba, esta ouvindo GABRIEL DO FUTURO!!
        bool isMovie_voltar = false;

        std::string modo = "Ir";
        std::string urlSkin;

        bool voltarMovie = false;

        float velocidade;

        Barreira(float x_, int y_, SDL_Surface* skin_, int largura_, int altura_, float velocidade_, std::string urlSkin_);

        void draw(SDL_Surface* dentro, int limite__);
        void aparecer(Uint32 intervalo, Uint32 tempoAtual, Uint32 &tempoAnterior, Uint32 intervaloVoltar, Uint32 tempoAtualVoltar, Uint32 &tempoAnteriorVoltar);

    private:
        void spawnBarreira();
        void voltarBarreira();
};

#endif