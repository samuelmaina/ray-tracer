#include "materialbase.hpp"

qbRT::MaterialBase::MaterialBase()
{
    maxReflectionRays = 3;
    reflectionRayCount = 0;

    baseColor = ConstructVector(1.0, 1.0, 1.0);
    reflectivity = 0.0;
    shininess = 0.0;
}

qbRT::MaterialBase::~MaterialBase()
{
}

void qbRT::MaterialBase::SetColor(const double red, const double green, const double blue)
{
    baseColor = ConstructVector(red, green, blue);
}

void qbRT::MaterialBase::SetColor(const qbVector<double> color)
{
    baseColor = color;
}

void qbRT::MaterialBase::SetReflectivity(const double ref)
{
    reflectivity = ref;
}

void qbRT::MaterialBase::SetShininess(const double shineVal)
{
    shininess = shineVal;
}
qbVector<double> qbRT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                  const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                  const qbRT::Ray &cameraRay)
{
    qbVector<double> matColor{3};
    return matColor;
}

qbVector<double> qbRT::MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                         const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                         const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                         const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                         const qbVector<double> &baseColor)
{
    qbVector<double> color{3}, diffuseColor{3};
    double intensity, red = 0.0, green = 0.0, blue = 0.0;
    bool validIllum = false, illumFound = false;
    for (auto light : lightList)
    {
        validIllum = light->ComputeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);
        if (validIllum)
        {
            illumFound = true;
            ComputeColorIntensity(color, red, green, blue, intensity);
        }
    }
    // No need to calculate the diffussion color if there was no illumination in the scene.
    if (illumFound)
    {
        diffuseColor = ConstructFinalColor(red, green, blue, baseColor);
    }

    return diffuseColor;
}

qbVector<double> qbRT::MaterialBase::ComputeReflectionColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                            const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                            const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                            const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                            const qbRT::Ray &incidentRay)
{

    qbVector<double> reflectionVector{3}, d = incidentRay.GetRayVector();

    reflectionVector = d - (2 * DotProduct(d, localNormal) * localNormal);
    qbRT::Ray reflectionRay(intPoint, intPoint + reflectionVector);
    std::shared_ptr<qbRT::ObjectBase> closestObject;
    qbVector<double> closestIntPoint{3}, closestLocalNormal{3}, closestLocalColor{3}, matColor{3};
    bool intFound = CastRay(reflectionRay, objectList, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

    if (intFound && (reflectionRayCount < maxReflectionRays))
    {

        reflectionRayCount++;
        if (closestObject->hasMaterial)
        {
            // use the material to compute the color
            matColor = closestObject->material->ComputeColor(objectList, lightList, currentObject, intPoint, localNormal, reflectionRay);
        }
        else
            // use the diffusion color if there are no materials to do the work.
            matColor = qbRT::MaterialBase::ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->baseColor);
    }
    // the current material color is the reflection Color.
    return matColor;
}

// Function to cast ray into the scene.
bool qbRT::MaterialBase::CastRay(const qbRT::Ray &castRay, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                 const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                 std::shared_ptr<qbRT::ObjectBase> &closestObject,
                                 qbVector<double> &closestIntPoint, qbVector<double> &closetLocalNormal,
                                 qbVector<double> closestLocalColor)
{

    qbVector<double> intPoint{3}, localNormal{3}, localColor{3};
    double minDist = 1e6;
    bool intFound = false;
    for (auto obj : objectList)
    {
        if (currentObject != obj)
        {
            bool validInt = obj->TestIntersection(castRay, intPoint, localNormal, localColor);
            if (validInt)
            {
                intFound = true;
                // compute the distance between the start and the point of inter
                double dist = (intPoint - castRay.GetPoint1()).norm();

                // store the object and its positions and characteristic if it is the closest
                if (dist < minDist)
                {
                    minDist = dist;
                    closestObject = obj;
                    closetLocalNormal = localNormal;
                    closestLocalColor = localColor;
                    closestIntPoint = intPoint;
                }
            }
        }
    }
    return intFound;
}

void qbRT::MaterialBase::ResetRayCount()
{
    reflectionRayCount = 0;
}
