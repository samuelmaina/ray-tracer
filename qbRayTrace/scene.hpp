#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "objectbase.hpp"
#include "pointlight.hpp"

namespace qbRT
{
    class Scene
    {
    private:
        qbRT::Camera camera;
        std::vector<std::shared_ptr<qbRT::ObjectBase>> objectList;
        std::vector<std::shared_ptr<qbRT::PointLight>> lightList;

    public:
        Scene(/* args */);
        ~Scene();
        bool Render(qbImage &outputImage);
    };
}

#endif