#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <iostream>

#include "vector"
#include "any"

void timer_config(std::vector<std::any>* arrayTimer, Uint32 intervalo, bool loop);
void timer_iniciarCronometro(std::vector<std::any>* arrayTimer);
bool timer_verificar(std::vector<std::any>* arrayTimer);

#endif