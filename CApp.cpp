#include "CApp.h"
#include <iostream>

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

    pWindow = SDL_CreateWindow("qbRayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 720, SDL_WINDOW_SHOWN);
    if (pWindow != NULL)
    {
        int xLength = 1280, yLength = 720;
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
        m_image.Initialize(xLength, yLength, pRenderer);
        for (int x = 0; x < xLength; ++x)
            for (int y = 0; y < yLength; ++y)
            {
                double red = (static_cast<double>(x) / static_cast<double>(xLength)) * 255.0;
                double green = (static_cast<double>(y) / static_cast<double>(xLength)) * 255.0;
                m_image.SetPixel(x, y, red, green, 0.0);
            }
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
    //set the default colour that will be displayed to the screen.
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);
    m_image.Display();
    SDL_RenderPresent(pRenderer);
}
void CApp::OnExit()
{
    //clear th  e SDL2 stuff
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}
void CApp::OnLoop()
{
}