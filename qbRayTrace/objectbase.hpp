#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "ray.hpp"
#include "./qbLinAlg/qbVector.h"

namespace qbRT
{
    class ObjectBase
    {
    public:
        ObjectBase();

        //every child class will have its own
        //implementation of the destructor.
        virtual ~ObjectBase();

        //function to test for intersections.
        //the function test if the cast array intersect with the object so that the object point can be displayed on the screen.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

    private:
    };
};

#endif