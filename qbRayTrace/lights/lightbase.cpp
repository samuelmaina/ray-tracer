#include "lightbase.hpp"

qbRT::LightBase::LightBase(/* args */){};

qbRT::LightBase::~LightBase()
{
}
bool qbRT::LightBase::ComputeIllumination(const qbVector<double> &intPoint,
                                          const qbVector<double> &localNormal,
                                          const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                          const std::shared_ptr<qbRT::ObjectBase> &currentObject, qbVector<double> &color,
                                          double &intensity)
{
    return false;
}

void qbRT::LightBase::SetColor(const double r, const double g, const double b)
{
    color = ConstructVector(r, g, b);
}
void qbRT::LightBase::SetLocation(const double x, const double y, const double z)
{
    location = ConstructVector(x, y, z);
}
