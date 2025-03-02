#include "DIM.h"
#include "Renderer.h"
#include "Scripting.h"
#include <iostream>

std::vector<DIM> DIM::dims;
SDL_Event event;

int main() {
    std::cout << "Engine started" << std::endl;
    DIM samir(200, 200);
    
    DIM::SetCurrDIM(&samir);

    ScriptInit();
    RendererInit("Window");

    while (true) {
        ScriptRun();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                SDL_Quit();
                exit(0);
            }
        }
        Render();
        SDL_Delay(5);
    }

    return 0;
}