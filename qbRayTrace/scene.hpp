#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "objsphere.hpp"

namespace qbRT
{
    class Scene
    {
    private:
        qbRT::Camera camera;
        qbRT::ObjSphere testSphere;
        //a unit sphere centred in the origin for testing.
    public:
        Scene(/* args */);
        ~Scene();
        bool Render(qbImage &outputImage);
    };

}

#endif