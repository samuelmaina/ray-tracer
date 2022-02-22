#include "materialbase.hpp"

qbRT::MaterialBase::MaterialBase()
{
}

qbRT::MaterialBase::~MaterialBase()
{
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
    qbVector<double> diffuseColor{3}, color{3};
    double intensity, red = 0.0, green = 0.0, blue = 0.0;
    bool validIllum = false, illumFound = false;
    for (auto light : lightList)
    {
        validIllum = light->ComputeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);
        if (validIllum)
        {
            illumFound = true;
            red += color.GetElement(0) * intensity;
            green += color.GetElement(1) * intensity;
            blue += color.GetElement(2) * intensity;
        }
    }
    // No need to calculate the diffussion color if there was no illumination in the scene.
    if (illumFound)
    {
        diffuseColor.SetElement(0, red * baseColor.GetElement(0));
        diffuseColor.SetElement(1, green * baseColor.GetElement(1));
        diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
    }

    return diffuseColor;
}
