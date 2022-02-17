#ifndef RAY_H
#define RAY_H

#include "./qbLinAlg/qbVector.h"
#include "vectormanipulators.hpp"

namespace qbRT
{
    class Ray
    {
    public:
        Ray();
        Ray(const qbVector<double> &point1, const qbVector<double> &point2);
        qbVector<double> GetPoint1() const;
        qbVector<double> GetPoint2() const;
        qbVector<double> GetRayVector() const;

    private:
        qbVector<double> point1{3};
        qbVector<double> point2{3};
        qbVector<double> ray_vector{3};
    };
};
#endif
