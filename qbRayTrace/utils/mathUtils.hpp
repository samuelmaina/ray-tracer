#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <vector>
#include <cmath>
#include "../qbLinAlg/qbVector.h"
#include "../utils/vectormanipulators.hpp"
void ComputeColorIntensity(const qbVector<double> color, double &red, double &green, double &blue, const double intensity);
qbVector<double> ConstructFinalColor(const double red, const double green, const double blue, const qbVector<double> baseColor);

bool GetRoots(double const a, double const b, double const c, double &root1, double &root2);
double GetSquare(double const a);

#endif