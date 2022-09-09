
#ifndef CONE_H
#define CONE_H

#include <cmath>
#include <vector>
#include "objectbase.hpp"
#include "../geometrytransformation.hpp"

namespace qbRT
{
    class Cone : public ObjectBase
    {
    public:
        // Default constructor.
        Cone();

        // Override the destructor.
        virtual ~Cone() override;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                      qbVector<double> &localNormal, qbVector<double> &localColor) override;
    };
}

#endif
