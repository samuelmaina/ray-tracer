#include "simplematerial.hpp"

qbRT::SimpleMaterial::SimpleMaterial(){};
qbRT::SimpleMaterial::~SimpleMaterial()
{
}

qbVector<double> qbRT::SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                    const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                    const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                    const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                    const qbRT::Ray &cameraRay)
{
    qbVector<double> refColor{3}, difColor{3}, spcColor{3};

    // compute the diffuse component
    difColor = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, baseColor);

    // compute the specular component if there is any.
    if (shininess > 0.0)
        spcColor = ComputeSpecular(objectList, lightList, intPoint, localNormal, cameraRay);

    // combine the diffusion color with the specular color as the final colors of the Material.
    return difColor + spcColor;
}

// Function to calculate the specular.
qbVector<double> qbRT::SimpleMaterial::ComputeSpecular(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                       const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                       const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                       const qbRT::Ray &cameraRay)
{

    qbVector<double> spcColor{3};
    double red = 0.0, green = 0.0, blue = 0.0;
    // compute the spectacular for each light in the scene.
    for (auto light : lightList)
    {
        double intensity = 0.0;

        qbVector<double> lightDir = (light->location - intPoint).Normalized();

        qbVector<double> startPoint = intPoint + (lightDir * 0.001);

        // construct a ray from the point of intersection to the light.
        qbRT::Ray lightRay(startPoint, startPoint + lightDir);

        qbVector<double> poi{3}, poiNormal{3}, poiColor{3};
        bool validInt = false;
        // check if there is any obstruction from the source.
        for (auto obj : objectList)
        {
            validInt = obj->TestIntersection(lightRay, poi, poiNormal, poiColor);
            if (validInt)
                break;
        }
        // if there there was not any intersection found, proceed to calculate
        // the specular component.
        if (!validInt)
        {
            // compute the reflection vector.
            qbVector<double> diff, reflection, v;
            double dotProduct;
            diff = lightRay.GetRayVector();

            reflection = diff - (2 * DotProduct(diff, localNormal) * localNormal);
            reflection.Normalize();
            v = cameraRay.GetRayVector();
            v.Normalize();
            dotProduct = DotProduct(reflection, v);

            if (dotProduct > 0.0)
            {
                intensity = reflectivity * std::pow(dotProduct, shininess);
            }
        }
        ComputeColorIntensity(light->color, red, green, blue, intensity);
    }
    return ConstructVector(red, green, blue);
}

void qbRT::SimpleMaterial::SetColor(double red, double green, double blue)
{
    baseColor = ConstructVector(red, green, blue);
}

void qbRT::SimpleMaterial::SetReflectivity(double ref)
{
    reflectivity = ref;
}
void qbRT::SimpleMaterial::SetShininess(double shineVal)
{
    shininess = shineVal;
}
