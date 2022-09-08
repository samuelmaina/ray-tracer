#include "scene.hpp"

double GetFactor(int size);

qbRT::Scene::Scene()
{
    SetCamera();

    // each object is centered at the origin by default  and translation is
    // used to move them  to their respective location hence no need to specify
    // their position.
    AddObjects();

    AssignColorsToObject();

    SetMaterialsAndAssignToObjects();

    // does not need to pass the number of matrices since
    // some objects in the scene won't require any transformations.
    SetTransformationMatricesAndApplyToObjects();

    SetPointLightsColorsAndLocations();
};

qbRT::Scene::~Scene()
{
}

void qbRT::Scene::SetCamera()
{
    camera.SetPosition(0.0, -10.0, -1.0);
    camera.SetLookAt(0.0, 0.0, 0.0);
    camera.SetUp(0.0, 0.0, 1.0);
    camera.SetHorizontalSize(0.25);
    camera.SetAspect(16.0 / 9.0);
    camera.UpdateCameraGeometry();
}

void qbRT::Scene::AddObjects()
{
    unsigned noOfSpheres = 3;
    unsigned noOfPlanes = 1;
    unsigned noOfCylinders = 3;
    unsigned noOfCones = 3;

    noOfObjects = noOfPlanes + noOfSpheres + noOfCylinders + noOfCones;

    for (int i = 0; i < noOfPlanes; ++i)
    {
        objectList.push_back(std::make_shared<qbRT::ObjPlane>(qbRT::ObjPlane()));
    }

    for (int i = 0; i < noOfSpheres; ++i)
    {
        objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));
    }

    for (int i = 0; i < noOfCylinders; ++i)
    {
        objectList.push_back(std::make_shared<qbRT::Cylinder>(qbRT::Cylinder()));
    }
    for (int i = 0; i < noOfCones; ++i)
    {
        objectList.push_back(std::make_shared<qbRT::Cone>(qbRT::Cone()));
    }
}

void qbRT::Scene::AssignColorsToObject()
{

    qbVector<qbVector<double>> colors{noOfObjects};

    colors.SetElement(0, ConstructVector(0.5, 0.5, 0.5));
    colors.SetElement(1, ConstructVector(0.25, 0.5, 0.8));
    colors.SetElement(2, ConstructVector(1.0, 0.5, 1.0));
    colors.SetElement(3, ConstructVector(1.0, 0.8, 0.5));

    for (unsigned i = 0; i < noOfObjects; i++)
    {
        objectList.at(i)->SetColor(colors.GetElement(i));
    }
}

void qbRT::Scene::SetMaterialsAndAssignToObjects()
{

    noOfMaterials = 4;

    qbVector<qbVector<double>> colors{noOfMaterials};
    colors.SetElement(0, ConstructVector(1.0, 1.0, 1.0));
    colors.SetElement(1, ConstructVector(0.25, 0.5, 0.8));
    colors.SetElement(0, ConstructVector(1.0, 0.5, 1.0));
    colors.SetElement(1, ConstructVector(0.25, 0.5, 1.2));

    qbVector<double> reflectivities{noOfMaterials},
        shinelinessValues{noOfMaterials};

    reflectivities.SetElement(0, 0.5);
    reflectivities.SetElement(1, 0.3);

    shinelinessValues.SetElement(0, 0.0);
    shinelinessValues.SetElement(1, 10.0);

    for (unsigned i = 0; i < noOfMaterials; i++)
    {
        materialList.push_back(std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial()));
        materialList.at(i)->SetColor(colors.GetElement(i));
        materialList.at(i)->SetReflectivity(reflectivities.GetElement(i));
        materialList.at(i)->SetShininess(shinelinessValues.GetElement(i));
    }
    // some objects  won't have materials hence don't assign materials to object using
    // object index.
    objectList.at(0)->AssignMaterial(materialList.at(0));
    objectList.at(1)->AssignMaterial(materialList.at(1));
}

void qbRT::Scene::SetTransformationMatricesAndApplyToObjects()
{

    for (size_t i = 1; i <= 4; i++)
    {
        qbRT::GTForm matrix1, matrix2, matrix3, matrix4, matrix5, matrix6, matrix7;

        matrix1.SetTransformationValues(-1.5 * i, 0.0, 0.0, 1.0 * i, 0.0, 0.0, 0.5, 0.5, 0.5);
        matrix2.SetTransformationValues(0.0 * i, 0.0, 0.0, 1.0 * i, 0.0, 0.0, 0.5, 0.5, 0.5);
        matrix3.SetTransformationValues(1.5 * i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5 * i, 0.5, 0.5);
        matrix4.SetTransformationValues(-1.5 * i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.5, 0.5);
        matrix5.SetTransformationValues(0.0 * i, 0.0, 0.0, 0.0, 0.5 * i, 0.0, 0.5, 0.5 * i, 0.5 * i);
        matrix6.SetTransformationValues(1.5 * i, 0.0, 0.0, 0.0, 0.5 * i, 0.0, 0.5 * i, 0.5, 0.5);
        matrix6.SetTransformationValues(1.5 * i, 0.0, 0.0, 0.0, 0.5 * i, 0.0, 0.5, 0.5, 0.5);

        // the object start at 0 hence the need to minus 1 from the i*n (it will always start from 0)
        objectList.at(1 * i - 1)->SetTranformMatrix(matrix1);
        objectList.at(2 * i - 1)->SetTranformMatrix(matrix1);
        objectList.at(3 * i - 1)->SetTranformMatrix(matrix1);
        objectList.at(4 * i - 1)->SetTranformMatrix(matrix1);
        objectList.at(5 * i - 1)->SetTranformMatrix(matrix1);
        objectList.at(6 * i - 1)->SetTranformMatrix(matrix1);
    }
}

void qbRT::Scene::SetPointLightsColorsAndLocations()
{

    noOfPointLights = 3;
    qbVector<qbVector<double>> colors{noOfPointLights};
    qbVector<qbVector<double>> locations{noOfPointLights};

    colors.SetElement(0, ConstructVector(1.0, 0.0, 0.0));
    colors.SetElement(1, ConstructVector(0.0, 1.0, 0.0));
    colors.SetElement(2, ConstructVector(0.0, 0.0, 1.0));

    locations.SetElement(0, ConstructVector(5.0, -10.0, -5.0));
    locations.SetElement(1, ConstructVector(-5.0, -10.0, -5.0));
    locations.SetElement(2, ConstructVector(0.0, -10.0, -5.0));

    for (int i = 0; i < noOfPointLights; ++i)
    {
        lightList.push_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));
        lightList.at(i)->SetColor(colors.GetElement(i));
        lightList.at(i)->SetLocation(locations.GetElement(i));
    }
}

bool qbRT::Scene::Render(qbImage &outputImage)
{
    xSize = outputImage.GetXSize();
    ySize = outputImage.GetYSize();
    ComputeXAndYFactors();
    for (int y = 0; y < ySize; ++y)
    {
        std::cout << "progress = " << y << " of  " << ySize << std::endl;
        for (int x = 0; x < xSize; ++x)
        {
            qbVector<double> color = ComputePixelColor(x, y);
            outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
        }
    }
    return true;
}

qbVector<double> qbRT::Scene::ComputePixelColor(unsigned xPosition, unsigned yPosition)
{
    qbRT::Ray cameraRay;

    qbVector<double> unsignedPoint{3}, localNormal{3}, localColor{3},
        closestIntPoint{3}, closestLocalNormal{3}, closestLocalColor{3};

    std::shared_ptr<qbRT::ObjectBase> closestObject;

    double normX, normY;

    NormalizeXandYCoordinates(xPosition, yPosition, normX, normY);

    camera.GenerateRay(normX, normY, cameraRay);

    bool intFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
    if (intFound)
    {

        // first check if the current object has a material.
        if (closestObject->hasMaterial)
        {
            // reset  so that the other materials have a fresh count of number of rays.
            qbRT::MaterialBase::ResetRayCount();
            // use the material to compute the color.
            return closestObject->material->ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, cameraRay);
        }
        else
        {

            qbVector<double> matColor, color{3};

            double red = 0.0, green = 0.0, blue = 0.0;

            matColor = qbRT::MaterialBase::ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->baseColor);
            // compute the intensity of il lumination of the point of intersection.
            bool illumFound = IsThereValidLightIllumination(closestObject, closestIntPoint, closestLocalNormal, color, red, green, blue);

            if (illumFound)
                return ConstructFinalColor(red, green, blue, closestLocalColor);

            return matColor;
        }
    }
    // default is the black color
    return ConstructVector(0.0, 0.0, 0.0);
}

void qbRT::Scene::NormalizeXandYCoordinates(unsigned xPosition, unsigned yPosition, double &normX, double &normY)
{
    normX = xPosition * xFact - 1.0;
    normY = yPosition * yFact - 1.0;
}

bool qbRT::Scene::CastRay(qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
                          qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
                          qbVector<double> &closestLocalColor)
{
    qbVector<double> intPoint{3}, localNormal{3}, localColor{3};

    double minDist = 1e6;
    double intFound = false;

    for (auto obj : objectList)
    {
        bool validIntersection = obj->TestIntersection(castRay, intPoint, localNormal, localColor);
        if (validIntersection)
        {

            // set that there is an intersection that .
            intFound = true;

            // compute the distance between intersection point and the camera.
            double dist = (intPoint - castRay.GetPoint1()).norm();

            /**
             * Store the current object that is closest to the camera, so that it can be displayed first.
             *
             */

            if (dist < minDist)
            {
                minDist = dist;
                closestObject = obj;
                closestIntPoint = intPoint;
                closestLocalNormal = localNormal;
                closestLocalColor = localColor;
            }
        }
    }
    return intFound;
}

bool qbRT::Scene::IsThereValidLightIllumination(
    std::shared_ptr<qbRT::ObjectBase> &closestObject, qbVector<double> &closestIntPoint,
    qbVector<double> &closestLocalNormal, qbVector<double> &color, double &red, double &green, double &blue)
{
    double intensity;

    bool validIllum = false, illumFound = false;

    for (auto light : lightList)
    {
        validIllum = light->ComputeIllumination(closestIntPoint, closestLocalNormal, objectList, closestObject, color, intensity);
        if (validIllum)
        {
            illumFound = true;
            ComputeColorIntensity(color, red, green, blue, intensity);
        }
    }
    return illumFound;
}

void qbRT::Scene::ComputeXAndYFactors()
{
    xFact = GetFactor(xSize);
    yFact = GetFactor(ySize);
}

double GetFactor(int size)
{
    return 1.0 / (static_cast<double>(size) / 2.0);
}