// File: Renderer.cpp

#include "Renderer.h"
#include <iostream>
#include "DIM.h"
#include "SDL3/SDL.h"
#include <iostream>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void RendererInit(const char* name) {
    std::cout << "Initialization..."<< std::endl; 
    std::cout << "inited: " << SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) << std::endl;
    window = SDL_CreateWindow(name, DIM::GetCurrDIM().GetWidth(), DIM::GetCurrDIM().GetHeight(), 0);
    renderer = SDL_CreateRenderer(window, NULL);
    std::cout << "Created renderer: " << renderer << std::endl;
    std::cout << "Created window: " << window << std::endl;

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    std::cout << "Initialized" << std::endl;
}


void Render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    for (const Object &obj : DIM::GetCurrDIM().GetObjects()) {
        SDL_FRect rect = {.x = obj.GetPosX(), .y=obj.GetPosY(), .w=obj.GetWidth(), .h=obj.GetHeight()};
        SDL_SetRenderDrawColor(renderer, obj.GetColorR(), obj.GetColorG(), obj.GetColorB(), SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_RenderPresent(renderer);
}