#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./qbImage.hpp"

namespace qbRT
{
    class Scene
    {
    private:
        /* data */
    public:
        Scene(/* args */);
        ~Scene();
        bool Render(qbImage &outputImage);
    };

}

#endif