#ifndef CAPP_H
#define CAPP_H
#include <SDL2/SDL.h>
#include "./qbRayTrace/qbImage.hpp"
#include "./qbRayTrace/scene.hpp"
#include "./qbRayTrace/camera.hpp"

class CApp
{
public:
    CApp();
    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:
    qbImage m_image;
    qbRT::Scene m_scene;
    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};
#endif