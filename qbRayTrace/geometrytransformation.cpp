#include "geometrytransformation.hpp"
#include "math.h"

qbRT::GTForm::GTForm()
{
    // set the forward and backward transforms to identity
    // matrices to avoid erroneous behaviour.
    forwardTransform.SetToIdentity();
    backwardTransform.SetToIdentity();
};
qbRT::GTForm::~GTForm()
{
}

qbRT::GTForm::GTForm(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
    // reject if any inputs are  not 4x4
    if (!(fwd.GetNumRows() == 4 && fwd.GetNumCols() == 4 && bck.GetNumRows() == 4 && bck.GetNumCols() == 4))
    {
        throw std::invalid_argument("either the forward or the backward matrices are wrong.");
    }
    forwardTransform = fwd;
    backwardTransform = bck;
}

// function to set the transformation.
void qbRT::GTForm::SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale)
{
    qbMatrix2<double> translationMatrix{4, 4};
    qbMatrix2<double> rotationMatrixX{4, 4};
    qbMatrix2<double> rotationMatrixY{4, 4};
    qbMatrix2<double> rotationMatrixZ{4, 4};
    qbMatrix2<double> scaleMatrix{4, 4};

    // First set all to identity matrices.
    translationMatrix.SetToIdentity();
    rotationMatrixX.SetToIdentity();
    rotationMatrixY.SetToIdentity();
    rotationMatrixZ.SetToIdentity();
    scaleMatrix.SetToIdentity();

    // popluate the matrices with the appropriate values.
    // first start with the translation matrix.
    translationMatrix.SetElement(0, 3, translation.GetElement(0));
    translationMatrix.SetElement(1, 3, translation.GetElement(1));
    translationMatrix.SetElement(2, 3, translation.GetElement(2));

    // Rotation Matrices.
    double zAngle = rotation.GetElement(2);
    double cosZ = cos(zAngle);
    double sinZ = sin(zAngle);
    rotationMatrixZ.SetElement(0, 0, cosZ);
    rotationMatrixZ.SetElement(0, 1, -sinZ);
    rotationMatrixZ.SetElement(1, 0, sinZ);
    rotationMatrixZ.SetElement(1, 1, cosZ);

    double yAngle = rotation.GetElement(1);
    double cosY = cos(yAngle);
    double sinY = sin(yAngle);
    rotationMatrixY.SetElement(0, 0, cosY);
    rotationMatrixY.SetElement(0, 2, sinY);
    rotationMatrixY.SetElement(2, 0, -sinY);
    rotationMatrixY.SetElement(2, 2, cosY);

    double xAngle = rotation.GetElement(0);
    double cosX = cos(xAngle);
    double sinX = sin(xAngle);
    rotationMatrixZ.SetElement(1, 1, cosX);
    rotationMatrixZ.SetElement(1, 2, -sinX);
    rotationMatrixZ.SetElement(2, 1, sinX);
    rotationMatrixZ.SetElement(2, 2, cosX);

    // And the scale Matrix.
    scaleMatrix.SetElement(0, 0, scale.GetElement(0));
    scaleMatrix.SetElement(1, 1, scale.GetElement(1));
    scaleMatrix.SetElement(2, 2, scale.GetElement(2));

    // do the final transform Matrix.
    // asumption that by default the use is making a forward transformation.
    // set the scaling to be done first so as to accommdodate both cylinder and cones.
    forwardTransform = translationMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ * scaleMatrix;

    backwardTransform = forwardTransform;
    // it is now the inverse of the forwardTransformation.
    backwardTransform.Inverse();
}

qbMatrix2<double> qbRT::GTForm::GetForward()
{
    return forwardTransform;
}

qbMatrix2<double> qbRT::GTForm::GetBackward()
{
    return backwardTransform;
}

qbRT::Ray qbRT::GTForm::Apply(const qbRT::Ray &inputRay, bool dirFlag)
{

    if (dirFlag)
    {
        return qbRT::Ray(this->Apply(inputRay.GetPoint1(), qbRT::FWDTFORM), this->Apply(inputRay.GetPoint2(), qbRT::FWDTFORM));
    }
    return qbRT::Ray(this->Apply(inputRay.GetPoint1(), qbRT::BCKTFORM), this->Apply(inputRay.GetPoint2(), qbRT::BCKTFORM));
}

qbVector<double> qbRT::GTForm::Apply(const qbVector<double> &inputVector, bool dirFlag)
{
    // convert inputVector to a 4-elment vector by adding a 1.0

    std::vector<double> tempData = {inputVector.GetElement(0),
                                    inputVector.GetElement(1),
                                    inputVector.GetElement(2),
                                    1.0};
    qbVector<double> tempVector{tempData};

    qbVector<double> result;

    if (dirFlag)
    {
        result = forwardTransform * tempVector;
    }
    else
    {
        result = backwardTransform * tempVector;
    }

    return qbVector<double>{
        std::vector<double>{result.GetElement(0), result.GetElement(1), result.GetElement(2)}};
}

// must specify that the code is in the namespace since the operator can not acess
// the member variables of the class. If the namespace is left out , the complier will throw many
// errors.
namespace qbRT
{
    GTForm operator*(const qbRT::GTForm &lhs, const qbRT::GTForm &rhs)
    {
        // perform the product of the two forward transforms.
        qbMatrix2<double> fwdResult = lhs.forwardTransform * rhs.forwardTransform;

        qbMatrix2<double> bckResult = fwdResult;
        bckResult.Inverse();

        // form the final result
        qbRT::GTForm finalResult(fwdResult, bckResult);
        return finalResult;
    }
}

// overload the = operator

qbRT::GTForm qbRT::GTForm ::operator=(const qbRT::GTForm &rhs)
{

    // ensure that we are not reassingining.
    if (this != &rhs)
    {
        forwardTransform = rhs.forwardTransform;
        backwardTransform = rhs.backwardTransform;
    }
    return *this;
}

void qbRT::GTForm::PrintMatrix(bool dirFlag)
{
    if (dirFlag)
    {
        print(forwardTransform);
    }
    else
        print(backwardTransform);
}

void qbRT::GTForm::print(const qbMatrix2<double> &matrix)
{
    int nRows = matrix.GetNumRows();
    int nCols = matrix.GetNumCols();
    for (int row = 0; row < nRows; ++row)
    {
        for (int col = 0; col < nCols; ++col)
        {
            std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
        }
        std::cout << std::endl;
    }
}

void qbRT::GTForm::PrintVector(const qbVector<double> &inputVector)
{
    int nRows = inputVector.GetNumDims();
    for (int row = 0; row < nRows; ++row)
    {
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << "\n";
    }
}