#include <SDL2/SDL.h>
#include <iostream>
#include "graphics/Window.h"

Graphics::Window::Window(const char* rTitle, int rWidth, int rHeigth)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error while initializing SDL" << SDL_GetError()
                  << std::endl;
        throw;
    }
    mWindow = SDL_CreateWindow(rTitle, SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, rWidth, rHeigth, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr)
    {
        std::cout << "Error while creating window" << SDL_GetError()
                  << std::endl;
    }
    mSurface = SDL_GetWindowSurface(mWindow);
}
Graphics::Window::~Window()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Graphics::Window::Update()
{
    SDL_UpdateWindowSurface(mWindow);
}
