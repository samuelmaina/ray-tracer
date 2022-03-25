#ifndef CYLINDER_H
#define CYLINDER_H

#include "objectbase.hpp"
#include "../geometrytransformation.hpp"

#include <cmath>
namespace qbRT
{
    class Cylinder : public ObjectBase
    {
    private:
        /* data */
    public:
        Cylinder(/* args */);
        virtual ~Cylinder() override;
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                      qbVector<double> &localNormal, qbVector<double> &localColor) override;
    };
}
#endif