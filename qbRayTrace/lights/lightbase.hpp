#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>

#include "../primitives/objectbase.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"
#include "../utils/vectormanipulators.hpp"

namespace qbRT
{
    class LightBase
    {
    private:
    public:
        LightBase();
        virtual ~LightBase();
        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                         const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                         qbVector<double> &color, double &intensity);
        void SetColor(const double r, const double g, const double b);
        void SetLocation(const double x, const double y, const double z);

    public:
        qbVector<double> color{3}, location{3};
        double intensity;
    };
}

#endif