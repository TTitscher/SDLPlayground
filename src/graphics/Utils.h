#pragma once
#include <SDL2/SDL_events.h>


namespace Graphics
{
inline void KeepAlive()
{
    SDL_Event e;
    while (true)
        while (SDL_PollEvent(&e) != 0)
            if (e.type == SDL_QUIT)
                return;
}
} /* Graphics */ 
