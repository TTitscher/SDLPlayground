#include "graphics/Window.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>

Graphics::Window::Window(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error while initializing SDL" << SDL_GetError() << std::endl;
        throw;
    }
    mWindow =
            SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    assert(mWindow != nullptr);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    assert(mRenderer != nullptr);
    SetColor(255, 255, 255);
    SDL_RenderClear(mRenderer);
    SetColor(0, 0, 0);
}
Graphics::Window::~Window()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Graphics::Window::SetColor(unsigned short r, unsigned short g, unsigned short b)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, 255);
}

void Graphics::Window::DrawLine(double x0, double y0, double x1, double y1)
{
    SDL_RenderDrawLine(mRenderer, std::round(x0), std::round(y0), std::round(x1), std::round(y1));
}

void Graphics::Window::DrawPixel(double x, double y)
{
    SDL_RenderDrawPoint(mRenderer, std::round(x), std::round(y));
}

void Graphics::Window::DrawCircle(double x, double y, int radius)
{
    // thanks to http://stackoverflow.com/a/41902448
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
                DrawPixel(x + dx, y + dy);
        }
    }
}

void Graphics::Window::Update()
{
    SDL_RenderPresent(mRenderer);
}
