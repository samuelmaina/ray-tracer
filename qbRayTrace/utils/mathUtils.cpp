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

bool GetRoots(double const a, double const b, double const c, double &root1, double &root2)
{
    double twoA = 2.0 * a;
    double det = GetSquare(b) - 4 * a * c;
    // we are working in plane and we don't expect any complex numbers
    // hence return false (unable to find roots) when the roots are complex
    if (det < 0)
        return false;
    double d = sqrt(det);
    double firstPart = -b / twoA;
    double secondPart = d / twoA;
    root1 = firstPart + secondPart;
    root2 = firstPart - secondPart;
    return true;
}

double GetSquare(double const a)
{
    return pow(a, 2.0);
}
