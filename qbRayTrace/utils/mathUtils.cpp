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

std::vector<double> GetRoots(double a, double b, double c)
{
    std::vector<double> ans;
    double twoA = 2.0 * a;
    double det = pow(b, 2.0) - 4 * a * c;
    // we are working in plane and we don't expect any complex numbers
    // hence throw error  when the roots are complex
    if (det < 0)
        throw "The quadratic equation can not have real roots";
    double d = sqrt(det);
    ans.push_back((-b + d) / twoA);
    ans.push_back((-b - d) / twoA);
    return ans;
}
