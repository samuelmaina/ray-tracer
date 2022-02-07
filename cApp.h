#ifndef CAPP_H
#define CAPP_H
#include <SDL2/SDL.h>
#include "./qbRayTrace/qbImage.hpp"

class CApp
{
public:
    Capp();
    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:
    qbImage m_image;
    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};
#endif