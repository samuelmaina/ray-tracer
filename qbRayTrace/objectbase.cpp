#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

qbRT::ObjectBase::ObjectBase()
{
}

qbRT::ObjectBase::~ObjectBase()
{
}

bool qbRT::ObjectBase::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    return false;
}

bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
    return fabs(f1 - f2) < EPSILON;
}
