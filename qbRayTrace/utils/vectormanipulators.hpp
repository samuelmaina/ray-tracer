#ifndef VECTORMANIPULATORS_H
#define VECTORMANIPULATORS_H

#include "../qbLinAlg/qbVector.h"
qbVector<double> ConstructVector(double, double, double);
qbVector<double> CrossProduct(qbVector<double>, qbVector<double>);
double DotProduct(qbVector<double>, qbVector<double>);
#endif