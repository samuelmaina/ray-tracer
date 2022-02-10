#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"
#include "geometrytransformation.hpp"

namespace qbRT
{
    class ObjPlane : public ObjectBase
    {

    public:
        ObjPlane();

        virtual ~ObjPlane() override;
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;

    private:
    };
};

#endif