#ifndef MATERIALBASE_H
#define MATERRIALBASE_H

#include "memory"
#include "../primitives/objectbase.hpp"
#include "../lights/lightbase.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../utils/mathUtils.hpp"

namespace qbRT
{
    class MaterialBase
    {
    public:
        MaterialBase();
        virtual ~MaterialBase();

        // function that will be used to return the current color of the material

        virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                              const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                              const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                              const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                              const qbRT::Ray &cameraRay);

        // function to calculate the diffussion color
        static qbVector<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                    const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                    const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                    const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                    const qbVector<double> &baseColor);

        // function to cast a ray into the scene.
        bool CastRay(const qbRT::Ray &castRay, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                     const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                     std::shared_ptr<qbRT::ObjectBase> &closestObject,
                     qbVector<double> &closestIntPoint, qbVector<double> &closetLocalNormal,
                     qbVector<double> closestLocalColor);

        // function to compute the reflection color.
        qbVector<double> ComputeReflectionColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                const qbRT::Ray &incidentRay);

    public:
        inline static int maxReflectionRays;
        inline static int reflectionRayCount;

    private:
    };
}

#endif