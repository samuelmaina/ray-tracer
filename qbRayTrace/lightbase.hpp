#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include <memory>
#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "objectbase.hpp"

namespace qbRT
{
    class LightBase
    {
    private:
    public:
        LightBase();
        virtual ~LightBase();
        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList, const std::shared_ptr<qbRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity);

    public:
        qbVector<double> color{3};
        qbVector<double> location{3};
        double intensity;
    };
}

#endif