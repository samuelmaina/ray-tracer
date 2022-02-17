#include "vectormanipulators.hpp"

qbVector<double> ConstructVector(double a, double b, double c)
{
    return qbVector<double>{
        std::vector<double>{a, b, c}};
}

qbVector<double> CrossProduct(qbVector<double> v1, qbVector<double> v2)
{
    return qbVector<double>::cross(v1, v2);
}

double DotProduct(qbVector<double> v1, qbVector<double> v2)
{
    return qbVector<double>::dot(v1, v2);
}
