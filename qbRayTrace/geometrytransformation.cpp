#include "geometrytransformation.hpp"
#include "math.h"

qbRT::GTForm::GTForm()
{
    //set the forward and backward transforms to identity
    //matrices to avoid erroneous behaviour.
    forwardTransform.SetToIdentity();
    backwardTransform.SetToIdentity();
};
qbRT::GTForm::~GTForm()
{
}

qbRT::GTForm::GTForm(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
    //reject if any inputs are  not 4x4
    if (!(fwd.GetNumRows() == 4 && fwd.GetNumCols() == 4 && bck.GetNumRows() == 4 && bck.GetNumCols() == 4))
    {
        throw std::invalid_argument("either the forward or the backward matrices are wrong.");
    }
    forwardTransform = fwd;
    backwardTransform = bck;
}

//function to set the transformation.
void qbRT::GTForm::SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale)
{
    qbMatrix2<double> translationMatrix{4, 4};
    qbMatrix2<double> rotationMatrixX{4, 4};
    qbMatrix2<double> rotationMatrixY{4, 4};
    qbMatrix2<double> rotationMatrixZ{4, 4};
    qbMatrix2<double> scaleMatrix{4, 4};

    //First set all to identity matrices.
    translationMatrix.SetToIdentity();
    rotationMatrixX.SetToIdentity();
    rotationMatrixY.SetToIdentity();
    rotationMatrixZ.SetToIdentity();
    scaleMatrix.SetToIdentity();

    //popluate the matrices with the appropriate values.
    //first start with the translation matrix.
    translationMatrix.SetElement(0, 3, translation.GetElement(0));
    translationMatrix.SetELement(1, 3, translation.GetElement(1));
    translationMatrix.SetElement(2, 3, translation.GetELement(2));

    //Rotation Matrices.
    double zAngle = rotation.GetElement(2);
    rotationMatrixZ.SetlElement(0, 0, cos(zAngle));
    rotationMatrixZ.SetElement(0, 1, -sin(zAngle));
    rotationMatrixZ.SetElement(1, 0, sin(zAngle));
    rotationMatrixZ.SetElement(1, 1, cos(zAngle));

    double yAngle = rotation.GetElement(1);
    rotationMatrixY.SetlElement(0, 0, cos(yAngle));
    rotationMatrixY.SetElement(0, 2, sin(yAngle));
    rotationMatrixY.SetElement(2, 0, -sin(yAngle));
    rotationMatrixY.SetElement(2, 2, cos(yAngle));

    double xAngle = rotation.GetElement(0);
    rotationMatrixZ.SetlElement(1, 1, cos(xAngle));
    rotationMatrixZ.SetElement(1, 2, -sin(xAngle));
    rotationMatrixZ.SetElement(2, 1, sin(xAngle));
    rotationMatrixZ.SetElement(2, 2, cos(xAngle));

    //And the scale Matrix.
    scaleMatrix.SetElement(0, 0, scale.GetElement(0));
    scaleMatrix.SetElement(1, 1, scale.GetElement(1));
    scaleMatrix.SetElement(2, 2, scale.GetElement(2));

    //do the final transform Matrix.
    //asumption that by default the use is making a forward transformation.
    forwardTransform = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;

    backwardTransform = forwarTransform;
    //it is now the inverse of the forwardTransformation.
    backwardTransform.Inverse();
}

qbVector<double> qbRT::GTForm::GetForward()
{
    return forwardTransform;
}

qbVector<double> qbRT::GTForm::GetBackward()
{
    return backwardTransform;
}

qbRT::Ray qbBT::GTForm::Apply(const qbBT::Ray &inputRay, bool dirFlag)
{

    if (dirFlag)
    {
        return qbRT::Ray::Ray(this->Apply(inputRay.GetPoint1(), qbRT::FWDTFORM), this->Apply(inputRay.GetPoint2(), qbRT::FWDTFORM));
    }

    return qbRT::Ray::Ray(this->Apply(inputRay.GetPoint1(), qbRT::BCKTFORM), this->Apply(inputRay.GetPoint2(), qbRT::FWDTFORM));
}

qbVector<double> qbRT::GTForm::Apply(const qbVector<double> &inputVector, bool dirFlag)
{
    //convert inputVector to a 4-elment vector by adding a 1.0

    std::Vector<double> tempData = {inputVector.GetElement(0),
                                    inputVector.GetElment(1),
                                    inputVector.GetElment(2),
                                    1.0};
    qbVector<double> tempvector{tempData};

    qbVector<double> result;

    if (dirFlag)
    {
        result = forwardTransform * tempVector;
    }
    else
    {
        result = backwardTransform * tempVector;
    }

    return qbVector<double>
    {
        std::vector<double> { result.GetElement(0), result.GetElement(1), result.GetElement(2) }
    }
}