#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../ray.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../geometrytransformation.hpp"

namespace qbRT
{
    class ObjectBase
    {
    public:
        ObjectBase();

        // every child class will have its own
        // implementation of the destructor.
        virtual ~ObjectBase();

        // function to test for intersections.
        // the function test if the cast array intersect with the object so that the object point can be displayed on the screen.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

        // function to set the transform matrix.
        void SetTranformMatrix(const qbRT ::GTForm &transformMatrix);
        // used to see if two points are close enough to reconsider calculation of whatever sort.
        bool CloseEnough(const double f1, const double f2);
        void SetColor(const double r, const double g, const double b);

    public:
        // The color of the object
        qbVector<double> baseColor{3};
        qbRT::GTForm trnfrmMatrix;

    private:
    };
};

#endif