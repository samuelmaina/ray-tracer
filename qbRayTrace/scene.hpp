#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "camera.hpp"
#include "qbImage.hpp"

#include "./primitives/objsphere.hpp"
#include "./primitives/objplane.hpp"
#include "./primitives/cylinder.hpp"

#include "./lights/pointlight.hpp"

#include "./utils/vectormanipulators.hpp"
#include "./utils/mathUtils.hpp"

#include "./materials/simplematerial.hpp"

namespace qbRT
{
    class Scene
    {
    private:
        qbRT::Camera camera;

        unsigned noOfObjects;
        unsigned noOfPlanes;
        unsigned noOfPointLights;
        unsigned noOfMaterials;

        std::vector<std::shared_ptr<qbRT::ObjectBase>> objectList;
        std::vector<std::shared_ptr<qbRT::LightBase>> lightList;
        std::vector<std::shared_ptr<qbRT::MaterialBase>> materialList;

        unsigned xSize, ySize;
        double xFact, yFact;
        const double minDist = 0.0, maxDist = 1e6;

        void SetCamera();

        void SetMaterialsAndAssignToObjects();

        void SetTransformationMatricesAndApplyToObjects();

        void AssignColorsToObject();

        void SetPointLightsColorsAndLocations();

        void ComputeXAndYFactors();

        void NormalizeXandYCoordinates(unsigned xPosition, unsigned yPosition, double &normX, double &normY);

        bool IsThereValidLightIllumination(std::shared_ptr<qbRT::ObjectBase> &closestObject, qbVector<double> &closestIntPoint,
                                           qbVector<double> &closestLocalNormal, qbVector<double> &color, double &red, double &blue, double &green);

    public:
        Scene(/* args */);
        ~Scene();
        bool Render(qbImage &outputImage);
        void AddObjects();

        // function to cast ray into the scene.
        bool CastRay(qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
                     qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
                     qbVector<double> &closestLocalColor);

        qbVector<double> ComputePixelColor(unsigned xPosition, unsigned yPosition);
    };
}

#endif