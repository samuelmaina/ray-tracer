#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

qbRT::ObjectBase::ObjectBase()
{
}

qbRT::ObjectBase::~ObjectBase()
{
}

void qbRT::ObjectBase::SetTranformMatrix(const qbRT::GTForm &transformation)
{
    trnfrmMatrix = transformation;
}

bool qbRT::ObjectBase::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    return false;
}

bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
    return fabs(f1 - f2) < EPSILON;
}

void qbRT::ObjectBase::SetColor(const double r, const double g, const double b)
{
    baseColor = ConstructVector(r, g, b);
}