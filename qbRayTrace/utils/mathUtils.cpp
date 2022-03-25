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

bool GetRoots(double a, double b, double c, double &root1, double &root2)
{
    double twoA = 2.0 * a;
    double det = pow(b, 2.0) - 4 * a * c;
    // we are working in plane and we don't expect any complex numbers
    // hence throw error  when the roots are complex
    if (det < 0)
        return false;
    double d = sqrt(det);
    root1 = (-b + d) / twoA;
    root2 = (-b - d) / twoA;
    return true;
}
