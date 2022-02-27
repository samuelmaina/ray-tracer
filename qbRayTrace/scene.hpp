#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "camera.hpp"
#include "qbImage.hpp"
#include "./primitives/objsphere.hpp"
#include "./lights/pointlight.hpp"
#include "./utils/vectormanipulators.hpp"
#include "./materials/simplematerial.hpp"

namespace qbRT
{
    class Scene
    {
    private:
        qbRT::Camera camera;
        std::vector<std::shared_ptr<qbRT::ObjectBase>> objectList;
        std::vector<std::shared_ptr<qbRT::LightBase>> lightList;
        std::vector<std::shared_ptr<qbRT::MaterialBase>> materialList;

    public:
        Scene(/* args */);
        ~Scene();
        bool Render(qbImage &outputImage);
        void AddNObjects(int no);
        void AddNLights(int no);
        void AddNPlanes(int no);
        void AddNMaterials(int no);

        // function to cast ray into the scene.
        bool CastRay(qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject, qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor);
    };
}

#endif