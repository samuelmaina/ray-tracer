#include "scene.hpp"

// where T represent translation, R rotation and S scale
void setTransformationInMatrix(qbRT::GTForm &matrix, double Tx, double Ty, double Tz, double Rx, double Ry, double Rz, double Sx, double Sy, double Sz);

double getFactor(int size);

qbRT::Scene::Scene()
{
    int noOfObjects = 3;
    int noOfPlanes = 1;
    int noOfLights = 3;
    int noOfMaterials = 1;

    // set the camera.
    camera.SetPosition(0.0, -10.0, -1.0);
    camera.SetLookAt(0.0, 0.0, 0.0);
    camera.SetUp(0.0, 0.0, 1.0);
    camera.SethorzSize(0.25);
    camera.SetAspect(16.0 / 9.0);
    camera.UpdateCameraGeometry();

    // set the objects, planes, materials and lights.
    AddNSpheres(noOfObjects);

    AddNPlanes(noOfPlanes);

    AddNPointLights(noOfLights);

    AddNSimpleMaterials(noOfMaterials);

    // the transformation matrix for the three objects and one plane
    qbRT::GTForm matrix1, matrix2, matrix3, planeMatrix;

    setTransformationInMatrix(matrix1, -1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.75, 0.5, 0.5);
    setTransformationInMatrix(matrix2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.75, 0.5);
    setTransformationInMatrix(matrix3, 1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.25, 0.25);
    setTransformationInMatrix(planeMatrix, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 4.0, 4.0, 1.0);

    // Apply the matrix to the objects and the plane.
    objectList.at(0)->SetTranformMatrix(matrix1);
    objectList.at(1)->SetTranformMatrix(matrix2);
    objectList.at(2)->SetTranformMatrix(matrix3);
    objectList.at(3)->SetTranformMatrix(planeMatrix);

    // set the base colors for the objects and the plane.
    objectList.at(0)->SetColor(0.25, 0.5, 0.8);
    objectList.at(1)
        ->SetColor(1.0, 0.5, 1.0);
    objectList.at(2)->SetColor(1.0, 0.8, 0.0);
    // set the plane to gray.
    objectList.at(3)->SetColor(0.5, 0.5, 0.5);

    objectList.at(0)->AssignMaterial(materialList.at(0));

    // the lights
    lightList.at(0)
        ->SetLocation(5.0, -10.0, -5.0);
    lightList.at(0)->SetColor(1.0, 0.0, 0.0);

    lightList.at(1)->SetLocation(-5.0, -10.0, -5.0);
    lightList.at(1)->SetColor(0.0, 1.0, 0.0);

    lightList.at(2)->SetLocation(0.0, -10.0, -5.0);
    lightList.at(2)->SetColor(0.0, 0.0, 1.0);
};

qbRT::Scene::~Scene()
{
}
bool qbRT::Scene::Render(qbImage &outputImage)
{
    int xSize = outputImage.GetXSize(), ySize = outputImage.GetYSize();

    qbRT::Ray cameraRay;
    qbVector<double> intPoint{3}, localNormal{3}, localColor{3};

    double xFact = getFactor(xSize),
           yFact = getFactor(ySize),
           minDist = 0.0, maxDist = 1e6;

    int counter = 0, total = xSize * ySize;

    double normX, normY;

    for (int x = 0; x < xSize; ++x)
        for (int y = 0; y < ySize; ++y)
        {
            // Normalize the x and y coordinates.
            normX = x * xFact - 1.0;
            normY = y * yFact - 1.0;

            counter++;

            // test for intersection for all objects in the  scene.
            // generate an array for the pixel.

            camera.GenerateRay(normX, normY, cameraRay);

            std::shared_ptr<qbRT::ObjectBase> closestObject;
            qbVector<double> closestIntPoint{3}, closestLocalNormal{3}, closestLocalColor{3};

            bool intFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

            if (intFound)
            {

                // first check if the current object has a material.
                if (closestObject->hasMaterial)
                {
                    // reset  so that the other materials have a fresh count of number of rays.
                    qbRT::MaterialBase::ResetRayCount();
                    // use the material to compute the color.
                    qbVector<double> color = closestObject->material->ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, cameraRay);

                    outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                }
                else
                {

                    qbVector<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->baseColor);
                    // compute the intensity of il lumination of the point of intersection.
                    outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));

                    double intensity;
                    qbVector<double> color{3};
                    double red = 0.0, green = 0.0, blue = 0.0;
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
                    if (illumFound)
                    {
                        // multiply the closestLocalColor with the previous color.
                        red *= closestLocalColor.GetElement(0);
                        green *= closestLocalColor.GetElement(1);
                        blue *= closestLocalColor.GetElement(2);
                        outputImage.SetPixel(x, y, red, green, blue);
                    }
                }
            }
        }
    return true;
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

void qbRT::Scene::AddNSpheres(int no)
{
    for (int i = 0; i < no; ++i)
    {
        objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));
    }
}

void qbRT::Scene::AddNPlanes(int no)
{
    for (int i = 0; i < no; ++i)
    {
        objectList.push_back(std::make_shared<qbRT::ObjPlane>(qbRT::ObjPlane()));
    }
}

void qbRT::Scene::AddNSimpleMaterials(int no)
{
    for (int i = 0; i < no; ++i)
    {

        auto material = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());
        material->SetColor(0.25, 0.5, 0.8);
        material->SetReflectivity(0.5);
        material->SetShininess(10.0);
        materialList.push_back(material);
    }
}

void qbRT::Scene::AddNPointLights(int no)
{
    for (int i = 0; i < no; ++i)
    {
        lightList.push_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));
    }
}

// generate a factor between 0, and 2,
double getFactor(int size)
{
    return 1.0 / (static_cast<double>(size) / 2.0);
}

void setTransformationInMatrix(qbRT::GTForm &matrix, double Tx, double Ty, double Tz, double Rx, double Ry, double Rz, double Sx, double Sy, double Sz)
{
    matrix.SetTransform(ConstructVector(Tx, Ty, Tz), ConstructVector(Rx, Ry, Rz), ConstructVector(Sx, Sy, Sz));
}
