#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <memory>
#include "../ray.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../geometrytransformation.hpp"

namespace qbRT
{
    // The class MaterialBase could have been included in this file but that would create a circular dependencies
    // hence the class should be just be declared which it implementation will be done in the other fields that will be
    // included later.
    class MaterialBase;
    class ObjectBase
    {
    public:
        ObjectBase();

        // every child class will have its own
        // implementation of the destructor.
        virtual ~ObjectBase();

        // function to test for intersections.
        // the function test if the cast array intersect with the object so that the object point can be displayed on the screen.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                      qbVector<double> &localNormal, qbVector<double> &localColor);

        // function to set the transform matrix.
        void SetTranformMatrix(const qbRT ::GTForm &transformMatrix);
        // used to see if two points are close enough to reconsider calculation of whatever sort.
        bool CloseEnough(const double f1, const double f2);
        void SetColor(const double r, const double g, const double b);

        // Assign material to the object.
        bool AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial);

    public:
        // The color of the object
        qbVector<double> baseColor{3};
        qbRT::GTForm trnfrmMatrix;

        std::shared_ptr<qbRT::MaterialBase> material;
        // flag to indicate if the object has  a material.
        bool hasMaterial = false;

    private:
    };
};

#endif