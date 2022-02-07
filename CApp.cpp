#include "CApp.h"

CApp::Capp()
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
    pWindow = SQL_CreateWindow('qbRayTracer', SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 720, 5, SDL_WINDOW_SHOWN);
    if (pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
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
            OnEvent(&event)
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
    //set the default colour that will be displayed to the screen.
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RendererPresent(pRenderer);
}
void CApp::OnExit()
{
    //clear the SDL2 stuff
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}