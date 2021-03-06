#include "objsphere.hpp"
#include <cmath>

qbRT::ObjSphere::ObjSphere()
{
}
qbRT::ObjSphere::~ObjSphere()
{
}

bool qbRT::ObjSphere::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                       qbVector<double> &localNormal, qbVector<double> &localColor)
{

    // copy the ray and perform the backward transform.

    // the castRay is in the 3D world hence we need to convert it to the local scale of the sphere, by doing the backward transformation,

    qbRT::Ray bckRay = trnfrmMatrix.Apply(castRay, qbRT::BCKTFORM);

    // First the solve the quadratic equation  in which the determinant  is greater than 0.
    // compute the values of a, b and c.

    // TO DO  put link to where the quadratic that solves the intersection point of sphere and vector.
    qbVector<double>
        vhat = bckRay.GetRayVector(),
        point1 = bckRay.GetPoint1();
    vhat.Normalize();

    // a.a = 1.0 for vector hence no need of recalculating it.
    // calculate b.
    double b = 2.0 * DotProduct(point1, vhat);
    double c = DotProduct(point1, point1) - 1.0;

    qbVector<double> pointOfIntersection;

    double t1, t2;

    if (GetRoots(1.0, b, c, t1, t2))
    {

        // if either t1 or t2 is less that 0, then there is some part
        // of the object that is behind the camera, hence ignore the point.

        if ((t1 < 0.0) || (t2 < 0.0))
            return false;
        // t1, and t2, will give the forward and the backward point under which the ray cuts the sphere.
        // The point that is closest to the camera is given by the less of t1 or t2
        if (t1 < t2)
        {
            pointOfIntersection = point1 + (vhat * t1);
        }
        else
        {
            pointOfIntersection = point1 + (vhat * t2);
        }

        // transform the intesction point back to the world co-ordinate.
        intPoint = trnfrmMatrix.Apply(pointOfIntersection, qbRT::FWDTFORM);

        // compute the local normal again.
        qbVector<double>
            objOrigin = ConstructVector(0.0, 0.0, 0.0),
            newOrigin = trnfrmMatrix.Apply(objOrigin, qbRT::FWDTFORM);
        localNormal = intPoint - newOrigin;
        localNormal.Normalize();
        localColor = baseColor;
        return true;
    }
    return false;
}