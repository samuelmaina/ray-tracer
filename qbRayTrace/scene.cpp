#include "scene.hpp"
#include "objsphere.hpp"

double getFactor(int size);

qbRT::Scene::Scene()
{

    //set the camera.
    camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
    camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    camera.SethorzSize(0.25);
    camera.SetAspect(16.0 / 9.0);
    camera.UpdateCameraGeometry();
    //set some objects
    objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));
    objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));
    objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));

    qbRT::GTForm matrix1, matrix2, matrix3;
    matrix1.SetTransform(qbVector<double>{
                             std::vector<double>{
                                 -1.5, 0.0, 0, 0}},
                         qbVector<double>{std::vector<double>{0.0, 0.0, 0, 0}}, qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});
    matrix2.SetTransform(qbVector<double>{
                             std::vector<double>{
                                 0.0, 0.0, 0, 0}},
                         qbVector<double>{std::vector<double>{0.0, 0.0, 0, 0}}, qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
    matrix3.SetTransform(qbVector<double>{
                             std::vector<double>{
                                 1.5, 0.0, 0, 0}},
                         qbVector<double>{std::vector<double>{0.0, 0.0, 0, 0}}, qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

    objectList.at(0)->SetTranformMatrix(matrix1);
    objectList.at(1)->SetTranformMatrix(matrix2);
    objectList.at(2)->SetTranformMatrix(matrix3);

    objectList.at(0)
        ->baseColor = qbVector<double>{
        std::vector<double>{64.0, 128.0, 200.0}};
    objectList.at(1)->baseColor = qbVector<double>{
        std::vector<double>{255.0, 128.0, 0.0}};
    objectList.at(2)->baseColor = qbVector<double>{
        std::vector<double>{255.0, 200.0, 0.0}};

    lightList.push_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));

    //the light
    lightList.at(0)->location = qbVector<double>{
        std::vector<double>{5.0, -10.0, -5.0}};
    lightList.at(0)->color = qbVector<double>{
        std::vector<double>{255.0, 255.0, 255.0}};
};

qbRT::Scene::~Scene()
{
}
bool qbRT::Scene::Render(qbImage &outputImage)
{
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    //loop over every pixel of each image.
    qbRT::Ray cameraRay;
    qbVector<double> intPoint{3};
    qbVector<double> localNormal{3};
    qbVector<double> localColor{3};

    double xFact = getFactor(xSize);
    double yFact = getFactor(ySize);
    double minDist = 0.0;
    double maxDist = 1e6;

    int counter = 0;
    int total = xSize * ySize;

    double normX, normY;

    for (int x = 0; x < xSize; ++x)
        for (int y = 0; y < ySize; ++y)
        {
            //Normalize the x and y coordinates.
            normX = x * xFact - 1.0;
            normY = y * yFact - 1.0;

            counter++;

            //test for intersection for all objects in the  scene.
            //generate an array for the pixel.

            camera.GenerateRay(normX, normY, cameraRay);
            for (auto obj : objectList)
            {
                bool validIntersection = obj->TestIntersection(cameraRay, intPoint, localNormal, localColor);
                if (validIntersection)
                {
                    double intensity;
                    qbVector<double> color{3};
                    bool validIllum = false;
                    for (auto light : lightList)
                    {
                        validIllum = light->ComputeIllumination(intPoint, localNormal, objectList, obj, color, intensity);

                        if (validIllum)
                        {
                            outputImage.SetPixel(x, y, localColor.GetElement(0) * intensity, localColor.GetElement(1) * intensity, localColor.GetElement(2) * intensity);
                        }
                        else
                        {
                            //leave the pixel unchanged.
                            // outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                        }
                    }

                    //compute the intenisty of                    //compute the distance the camera and the point of intersection.
                    //the norm method calculates the distances.
                    double dist = (intPoint - cameraRay.GetPoint1()).norm();
                    if (dist > maxDist || dist < minDist)
                    {
                        std::cout << "Point can not be displayed";
                        exit(1);
                    }
                    //if  max distance bettween the sphere and the camera is 9.9505, and the lowest will be 9, since the radius is
                    //1 and the camera is placed  at -10 in the y direction.
                    //outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.9405) * 255.0, 0.0, 0.0);
                }
                else
                {
                    //leave the pixel unchanged.
                    // outputImage.SetPixel(x, y, 0, 0, 0.0);
                }
            }
        }

    return true;
}

//generate a factor between 0, and 2,
double getFactor(int size)
{
    return 1.0 / (static_cast<double>(size) / 2.0);
}