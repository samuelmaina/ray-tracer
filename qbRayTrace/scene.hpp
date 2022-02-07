#ifndef QBIMAGE_H
#define QBIMAGE_H

#include <vector>
#include <SDL2/SDL.h>

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