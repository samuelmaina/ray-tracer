#include "lightbase.hpp"

qbRT::LightBase::LightBase(/* args */){};

qbRT::LightBase::~LightBase()
{
}
bool qbRT::LightBase::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList, const std::shared_ptr<qbRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity)
{
    return false;
}
