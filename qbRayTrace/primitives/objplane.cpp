#include <cmath>
#include "objplane.hpp"

qbRT::ObjPlane::ObjPlane()
{
}
qbRT::ObjPlane::~ObjPlane()
{
}

bool qbRT::ObjPlane::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                      qbVector<double> &localNormal, qbVector<double> &localColor)
{

    // create a new backward transformed ray from the cast ray.
    qbRT::Ray bckRay = trnfrmMatrix.Apply(castRay, qbRT::BCKTFORM);

    // get the ray vector and normalize it.
    qbVector<double> k = bckRay.GetRayVector(), point1 = bckRay.GetPoint1();
    k.Normalize();

    // check if there is an intersection , i.e. if the castRay is not parallel to
    // to the plane
    if (!CloseEnough(k.GetElement(2), 0.0))
    {
        double t = point1.GetElement(2) / (-k.GetElement(2));

        /*If t is negative, then the intersection point must be behind
         the camera and we ignore it.*/
        if (t > 0.0)
        {
            // compute the values of u and v.
            double u = point1.GetElement(0) + t * k.GetElement(0);
            double v = point1.GetElement(1) + k.GetElement(1) * t;
            // if both magnitudes of u and v are less than equlalto 1
            //  then they must be on the plane.

            if (abs(u) <= 1.0 && abs(v) <= 1.0)
            {

                // compute the point of intersection.
                qbVector<double> poi = point1 + t * k;

                // transform the intersection point back into world coordinates.
                intPoint = trnfrmMatrix.Apply(poi, qbRT::FWDTFORM);

                // compute the local normal.
                qbVector<double> localOrigin = ConstructVector(0.0, 0.0, 0.0),
                                 normalVector = ConstructVector(0.0, 0.0, -1.0),
                                 globalOrigin = trnfrmMatrix.Apply(localOrigin, qbRT::FWDTFORM);
                localNormal = trnfrmMatrix.Apply(normalVector, qbRT::FWDTFORM) - globalOrigin;
                localNormal.Normalize();
                localColor = baseColor;

                return true;
            }
        }
        return false;
    }
    return false;
}
