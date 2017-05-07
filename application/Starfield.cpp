#include "graphics/Window.h"
#include <iostream>
#include <SDL2/SDL.h>
int main()
{
    std::cout << "Hello World" << std::endl;
    Graphics::Window w("Fancy Starfield", 800, 600);

    SDL_Event e;
    bool keepRunning = true;
    while (keepRunning)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            // handle user inputs
            if (e.type == SDL_QUIT)
            {
                keepRunning = false;
            }
        }
        w.Update();

    }
}
