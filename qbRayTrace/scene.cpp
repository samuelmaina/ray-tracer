#include "scene.hpp"

//where T represent translation, R rotation and S scale
void setTransformationInMatrix(qbRT::GTForm &matrix, double Tx, double Ty, double Tz, double Rx, double Ry, double Rz, double Sx, double Sy, double Sz);

double getFactor(int size);

qbRT::Scene::Scene()
{

    //set the camera.
    camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, -1.0}});
    camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    camera.SethorzSize(0.25);
    camera.SetAspect(16.0 / 9.0);
    camera.UpdateCameraGeometry();
    // //set some objects
    objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));
    objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));
    objectList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));

    qbRT::GTForm matrix1, matrix2, matrix3;

    setTransformationInMatrix(matrix1, -1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.5, 0.75);

    matrix2.SetTransform(qbVector<double>{
                             std::vector<double>{
                                 0.0, 0.0, 0, 0}},
                         qbVector<double>{std::vector<double>{0.0, 0.0, 0, 0}}, qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
    matrix3.SetTransform(qbVector<double>{
                             std::vector<double>{
                                 1.5, 0.0, 0, 0}},
                         qbVector<double>{std::vector<double>{0.0, 0.0, 0, 0}}, qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

    objectList.push_back(std::make_shared<qbRT::ObjPlane>(qbRT::ObjPlane()));
    qbRT::GTForm planeMatrix;
    setTransformationInMatrix(planeMatrix, 0.0, 0.0, 0.75, 0.0, 0.0, 0.0, 4.0, 4.0, 1.0);

    objectList.at(3)->SetTranformMatrix(planeMatrix);
    objectList.at(0)
        ->SetTranformMatrix(matrix1);
    objectList.at(1)->SetTranformMatrix(matrix2);
    objectList.at(2)->SetTranformMatrix(matrix3);

    objectList.at(0)
        ->baseColor = qbVector<double>{
        std::vector<double>{0.25, 0.5, 0.8}};
    objectList.at(1)->baseColor = qbVector<double>{
        std::vector<double>{1.0, 0.5, 0.0}};
    objectList.at(2)->baseColor = qbVector<double>{
        std::vector<double>{1.0, 0.8, 0.0}};

    //the color should be specified with values from 0 to 1.
    objectList.at(3)->baseColor = qbVector<double>{
        std::vector<double>{0.5, 0.5, 0.5}};

    lightList.push_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));

    //the light
    lightList.at(0)->location = qbVector<double>{
        std::vector<double>{5.0, -10.0, -5.0}};
    lightList.at(0)->color = qbVector<double>{
        std::vector<double>{1.0, 1.0, 1.0}};
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

            std::shared_ptr<qbRT::ObjectBase> closestObject;
            qbVector<double> closestIntPoint{3};
            qbVector<double> closestLocalNormal{3};
            qbVector<double> closestLocalColor{3};

            double minDist = 1e6;
            double intFound = false;

            for (auto obj : objectList)
            {
                bool validIntersection = obj->TestIntersection(cameraRay, intPoint, localNormal, localColor);
                if (validIntersection)
                {

                    //set that there is an intersection that .
                    intFound = true;

                    //compute the distance between intersection point and the camera.
                    double dist = (intPoint - cameraRay.GetPoint1()).norm();

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
                if (intFound)
                {
                    //compute the intensity of il lumination of the point of intersection.
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
                            red += color.GetElement(0) * intensity;
                            green += color.GetElement(1) * intensity;
                            blue += color.GetElement(2) * intensity;
                        }
                    }
                    if (illumFound)
                    {
                        //multiply the closestLocalColor with the previous color.
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

//generate a factor between 0, and 2,
double getFactor(int size)
{
    return 1.0 / (static_cast<double>(size) / 2.0);
}

void setTransformationInMatrix(qbRT::GTForm &matrix, double Tx, double Ty, double Tz, double Rx, double Ry, double Rz, double Sx, double Sy, double Sz)
{
    matrix.SetTransform(qbVector<double>{
                            std::vector<double>{Tx, Ty, Tz}},
                        qbVector<double>{std::vector<double>{Rx, Ry, Rz}}, qbVector<double>{std::vector{Sx, Sy, Sz}});
}