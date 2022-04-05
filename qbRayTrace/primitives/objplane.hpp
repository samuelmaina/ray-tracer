#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "./objectbase.hpp"
#include "../utils/vectormanipulators.hpp"

namespace qbRT
{
    class ObjPlane : public ObjectBase
    {

    public:
        ObjPlane();

        virtual ~ObjPlane() override;
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                      qbVector<double> &localNormal, qbVector<double> &localColor) override;

        bool CalculateIntersection(qbVector<double> &origin, qbVector<double> &rayVector, qbVector<double> &intPoint,
                                   qbVector<double> &localNormal, qbVector<double> &localColo);

    private:
    };
};

#endif