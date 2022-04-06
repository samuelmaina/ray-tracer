#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H

#include "materialbase.hpp"
#include "../utils/vectormanipulators.hpp"
#include "../lights/pointlight.hpp"
#include "../utils/mathUtils.hpp"

namespace qbRT
{
    class SimpleMaterial : public MaterialBase
    {
    public:
        SimpleMaterial();
        virtual ~SimpleMaterial() override;
        virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                              const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                              const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                              const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                              const qbRT::Ray &cameraRay) override;

        // Function to  compute the specular highlights
        qbVector<double> ComputeSpecular(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                         const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                         const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const qbRT::Ray &cameraRay);
    };
}

#endif