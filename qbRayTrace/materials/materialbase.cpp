#include "materialbase.hpp"

qbRT::MaterialBase::MaterialBase()
{
}

qbRT::MaterialBase::~MaterialBase()
{
}
qbVector<double> qbRT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<qbRT::PointLight>> &lightList,
                                                  const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                  const qbRT::Ray &cameraRay)
{
    qbVector<double> matColor{3};
    return matColor;
}

qbVector<double> qbRT::MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                         const std::vector<std::shared_ptr<qbRT::PointLight>> &lightList,
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
