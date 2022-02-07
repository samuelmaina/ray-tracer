#include "scene.hpp"

using namespace qbRT;

Scene::Scene()
{
}
bool Scene::Render(abImage &outputImage)
{
    int xSize = outputImage.getXSize();
    int ySize = outputImage.getYSize();

    for (int x = 0; x < xSize; ++x)
        for (int y = 0; y < ySize; ++y)
        {
            double red = (static_cast<double>(x) / static_cast<double>(xSize)) * 255.0;
            double green = (static_cast<double>(y) / static_cast<double>(ySize)) * 255.0;
            outputImage.SetPixel(x, y, red, green, 0.0);
        }

    return true;
}