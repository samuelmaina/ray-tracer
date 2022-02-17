#include "pointlight.hpp"
#include "math.h"

#define _USE_MATH_DEFINES
qbRT::PointLight::PointLight()
{
    color = qbVector<double>{
        std::vector<double>{1.0, 1.0, 1.0}};
    intensity = 1.0;
}

qbRT::PointLight::~PointLight()
{
}
bool qbRT::PointLight::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList, const std::shared_ptr<qbRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity)
{

    qbVector<double> lightDir = (location - intPoint).Normalized();
    qbVector<double> startPoint = intPoint;

    // construct a ray from the point of intersection(which is assumed to be the starting Point at the beginning ) to the light source.
    qbRT::Ray lightRay(startPoint, startPoint + lightDir);

    /***
     * check the intersection point of all the objects except for the current
     * object.
     */

    qbVector<double> interscPoint{3}, interscPointNormal{3}, interPointColor{3};
    bool validInt;
    for (auto obj : objectList)
    {
        if (obj != currentObject)
        {
            validInt = obj->TestIntersection(lightRay, interscPoint, interscPointNormal, interPointColor);
        }
        // if there is an intersection, thne the object is blocking light from the light source so we no need
        // to search further.
        if (validInt)
            break;
    }
    if (!validInt)
    {
        // compute the the angle between the light ray and the local normal.
        //  The normal vector is  assumed to be assumed to normalized.
        // Since the normal and the lightVector are assumed to be unit vector their
        // produce will be just be 1, which will make it easy for us to compute the
        // angle between ray and the normal.
        double angle = acos(qbVector<double>::dot(localNormal, lightDir));

        // if the normal is point away from the  light source, then there is no illumination.
        double angle_ninety = acos(0.0);
        if (angle > angle_ninety)
        {
            color = this->color;
            intensity = 0.0;
            return false;
        }
        else
        {
            color = this->color;
            intensity = this->intensity * (1.0 - (angle / angle_ninety));
            return true;
        }
    }
    else
    { // so there is no illumination, only a shadow so intensity is 0.0
        color = this->color;
        intensity = 0.0;
        return false;
    }
}
