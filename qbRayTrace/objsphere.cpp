#include "objsphere.hpp"
#include <cmath>

qbRT::ObjSphere::ObjSphere()
{
}
qbRT::ObjSphere::~ObjSphere()
{
}

bool qbRT::ObjSphere::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    //First the solve the quadratic equation  in which the determinant  is greater than 0.
    //compute the values of a, b and c.

    //TO DO  put link to where the quadratic that solves the intersection point of sphere and vector.
    qbVector<double> what = castRay.GetRayVector(), point1 = castRay.GetPoint1();
    what.Normalize();

    //a.a = 0  for vector hence no need of recalculating it.
    //calculate b.
    double b = 2.0 * qbVector<double>::dot(point1, what);
    double c = qbVector<double>::dot(point1, point1) - 1.0;

    double test = (b * b) - 4.0 * c;
    return test > 0.0;
}