#include "ray.hpp"

qbRT::Ray::Ray()
{
    qbVector<double> point1 = ConstructVector(0.0, 0.0, 0.0),
                     point2 = ConstructVector(0.0, 0.0, 1.0);
    Ray(point1, point2);
}

qbRT::Ray::Ray(const qbVector<double> &point1, const qbVector<double> &point2)
{
    this->point1 = point1;
    this->point2 = point2;
    ray_vector = this->point2 - this->point1;
}
qbVector<double> qbRT::Ray::GetPoint1() const
{
    return point1;
}
qbVector<double> qbRT::Ray::GetPoint2() const
{
    return point2;
}

qbVector<double> qbRT::Ray::GetRayVector() const
{
    return ray_vector;
}
