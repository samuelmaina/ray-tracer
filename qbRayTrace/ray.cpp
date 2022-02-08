#include "ray.hpp"

qbRT::Ray::Ray()
{
    m_point1 = qbVector<double>{
        std::vector<double>{0.0, 0.0, 0.0}};
    m_point1 = qbVector<double>{
        std::vector<double>{0.0, 0.0, 0 = 1.0}};
    Ray(m_point1, m_point2);
}

qbRT::Ray::Ray(const qbVector<double> &point1, const qbVector<double> &point2)
{
    m_point1 = point1;
    m_point2 = point2;
    m_lab = m_point2 - m_point1;
}
qbVector<double> qbRT::Ray::GetPoint1() const
{
    return m_point1;
}
qbVector<double> qbRT::Ray::GetPoint2() const
{
    return m_point2;
}

qbVector<double> qbRT::Ray::GetRayVector() const
{
    return m_lab;
}
