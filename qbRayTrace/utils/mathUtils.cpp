#include "mathUtils.hpp"

void ComputeColorIntensity(const qbVector<double> color, double &red, double &green, double &blue, const double intensity)
{
    red += color.GetElement(0) * intensity;
    green += color.GetElement(1) * intensity;
    blue += color.GetElement(2) * intensity;
};

qbVector<double> ConstructFinalColor(const double red, const double green, const double blue, const qbVector<double> baseColor)
{
    return ConstructVector(red * baseColor.GetElement(0), green * baseColor.GetElement(1), blue * baseColor.GetElement(2));
}
