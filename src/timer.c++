#include "./H/timer.h"

void timer_config(std::vector<std::any>* arrayTimer, Uint32 intervalo, bool loop) {
    bool primeiraTeste = true;
    arrayTimer->push_back(primeiraTeste);

    arrayTimer->push_back(intervalo);
    arrayTimer->push_back(loop);
}

void timer_iniciarCronometro(std::vector<std::any>* arrayTimer) {
    Uint32 tempoAnterior = SDL_GetTicks();
    arrayTimer->push_back(tempoAnterior);
}

bool timer_verificar(std::vector<std::any>* arrayTimer) {
    Uint32 tempoAtual = SDL_GetTicks();

    Uint32 intervalo = std::any_cast<Uint32>((*arrayTimer)[1]);
    bool loop = std::any_cast<bool>((*arrayTimer)[2]);
    Uint32 tempoAnterior = std::any_cast<Uint32>((*arrayTimer)[3]);

    bool primeira = std::any_cast<bool>((*arrayTimer)[0]);

    if(tempoAtual - tempoAnterior >= intervalo && loop == false) {
        if(primeira == true) {
            std::any_cast<bool&>((*arrayTimer)[0]) = false;
            return true;
        }
    }

    return false;
}