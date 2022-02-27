#include "CApp.h"
#include <iostream>

std::vector initColorAndAlpha = std::vector<double>{255, 255, 255, 255};

CApp::CApp()
{
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    double factor = 0.75;

    int xLength = static_cast<int>(1280 * factor), yLength = static_cast<int>(720 * factor);

    pWindow = SDL_CreateWindow("qbRayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xLength, yLength, SDL_WINDOW_SHOWN);
    if (pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
        m_image.Initialize(xLength, yLength, pRenderer);
        SDL_SetRenderDrawColor(pRenderer, initColorAndAlpha[0], initColorAndAlpha[1], initColorAndAlpha[2], initColorAndAlpha[3]);
        SDL_RenderClear(pRenderer);
        m_scene.Render(m_image);
        m_image.Display();
        SDL_RenderPresent(pRenderer);
    }
    else
    {
        return false;
    }
    return true;
}

int CApp::OnExecute()
{
    SDL_Event event;
    if (OnInit() == false)
        return -1;
    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
}

void CApp::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}
void CApp::OnRender()
{
    // set the default colour that will be displayed to the screen.
    SDL_SetRenderDrawColor(pRenderer, initColorAndAlpha[0], initColorAndAlpha[1], initColorAndAlpha[2], initColorAndAlpha[3]);
    SDL_RenderClear(pRenderer);
    m_scene.Render(m_image);
    m_image.Display();
    SDL_RenderPresent(pRenderer);
}
void CApp::OnExit()
{
    // clear the SDL2 stuff
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}
void CApp::OnLoop()
{
}