#include "scene.hpp"

double getFactor(int size);

qbRT::Scene::Scene()
{
    camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
    camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    camera.SethorzSize(0.25);
    camera.SetAspect(16.0 / 9.0);
    camera.UpdateCameraGeometry();
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

            //generate an array for the pixel.

            camera.GenerateRay(normX, normY, cameraRay);

            bool validIntersection = testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);
            if (validIntersection)
            {
                outputImage.SetPixel(x, y, 255, 0.0, 0.0);
            }
            else
            {
                outputImage.SetPixel(x, y, 0, 0, 0.0);
            }
        }

    return true;
}

//generate a fuctor between 0, and 2,
double getFactor(int size)
{
    return 1.0 / (static_cast<double>(size) / 2.0);
}