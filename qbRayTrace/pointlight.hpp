#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightbase.hpp"

namespace qbRT
{
    class PointLight : public LightBase
    {
    public:
        PointLight();
        virtual ~PointLight() override;
        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList, const std::shared_ptr<qbRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity) override;
    };

}

#endif