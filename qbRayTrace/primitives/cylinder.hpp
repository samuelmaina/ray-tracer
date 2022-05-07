#ifndef CYLINDER_H
#define CYLINDER_H

#include "objectbase.hpp"
#include "../utils/mathUtils.hpp"
namespace qbRT
{
    class Cylinder : public ObjectBase
    {
    private:
        bool IsZValueIsInRangeOfNegativeOneAndOne(const qbVector<double> point);
        bool IsSqrtOfSumOfXanYSquaresLessThan1(const qbVector<double> point);
        bool IsParallelToTheZOrigin(const qbVector<double> point);

    public:
        Cylinder(/* args */);
        virtual ~Cylinder() override;
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                      qbVector<double> &localNormal, qbVector<double> &localColor) override;
    };
}
#endif