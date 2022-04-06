#ifndef GEOMETRYTRANSFORMATION_H
#define GEOMETRYTRANSRORMATION_H

// the class will be used to construct single matrix that will be used to
// transform the image.
// the matrices  produced will be multiples for scaling , rotating and tranlation.
// the class will also transform input vectors through a transformation.
#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"
#include "ray.hpp"

#include "math.h"

namespace qbRT
{
    // Define direction flag values.
    // the values will be used to store the bool values that
    // represent both the forward and backward transformation.

    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;
    class GTForm
    {
    public:
        GTForm();
        ~GTForm();
        GTForm(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);

        void SetTransformationValues(double Tx, double Ty, double Tz, double Rx, double Ry, double Rz, double Sx, double Sy, double Sz);

        void SetTransform(const qbVector<double> &translation,
                          const qbVector<double> &rotation,
                          const qbVector<double> &scale);

        // function that will return the transform matrices.
        qbMatrix2<double> GetForward();
        qbMatrix2<double> GetBackward();

        // apply a transformation according to specicfic direction.
        qbRT::Ray Apply(const qbRT::Ray &inputRay, bool dirFlag);

        // overload the Apply function so that it handles vectors  differently from rays.
        qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);

        // operator overloads.
        friend GTForm operator*(const qbRT::GTForm &lhs, const qbRT::GTForm &rhs);
        GTForm operator=(const GTForm &rhs);

        // used mostly for debugging to show the computed matrix and the input vector or the output vector.
        void PrintMatrix(bool dirFlag);
        static void PrintVector(const qbVector<double> &vector);

    private:
        // print the local matrix
        void print(const qbMatrix2<double> &matrix);

    private:
        // define the two forward and backward transform matrices. which will be
        // both 4 x 4 matrices. the Additional row and column (we are dealing with 3D as of now)
        // is to allow for translation.
        qbMatrix2<double> forwardTransform{4, 4};
        qbMatrix2<double> backwardTransform{4, 4};
    };

}
#endif