#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "objectbase.hpp"
#include "vectormanipulators.hpp"

namespace qbRT
{
    class ObjSphere : public qbRT::ObjectBase
    {
    public:
        // used to create a unit(radius 1) from the origin.
        ObjSphere();
        virtual ~ObjSphere() override;
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

    private:
    };
};

#endif