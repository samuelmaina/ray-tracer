#include "cylinder.hpp"

const double maxT = 100e6;

qbRT::Cylinder::Cylinder(){

};

qbRT::Cylinder::~Cylinder()
{
}

bool qbRT::Cylinder::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                      qbVector<double> &localNormal, qbVector<double> &localColor)
{

    // coy the ray and apply the backwards transform.
    qbRT::Ray bckRay = trnfrmMatrix.Apply(castRay, qbRT::BCKTFORM);
    qbVector<double> v = bckRay.GetRayVector();
    v.Normalize();

    // get p vector( the start of the cast ray)
    qbVector<double> p = bckRay.GetPoint1();

    // Compute a, b and c
    double a, b, c;
    double vx = v.GetElement(0), vy = v.GetElement(1),
           px = p.GetElement(0), py = p.GetElement(1);

    a = GetSquare(vx) + GetSquare(vy);
    b = 2.0 * (px * py + py * vy);
    c = GetSquare(vx) + GetSquare(py) - 1.0;

    std::vector<qbVector<double>> pointsOfIntersections(4);

    // there will be 4 points of intersections, two that one circular side of the
    // cylinder and the  other two at the other circular surface.
    std::vector<double> tValues(4);

    bool t1Valid, t2Valid, t3Valid, t4Valid;

    if (GetRoots(a, b, c, tValues.at(0), tValues.at(1)))
    {

        // there is a valid intersection for the first two intersection points.
        // compute the intersection using the values of t1 and t2

        double t1 = tValues.at(0), t2 = tValues.at(1);
        pointsOfIntersections.at(0) = p + (v * t1);
        pointsOfIntersections.at(1) = p + (v * t2);
        qbVector<double> firstIntPoint = pointsOfIntersections.at(0), secondIntPoint = pointsOfIntersections.at(1);

        if (t1 > 0.0 && IsZValueIsInRangeOfNegativeOneAndOne(firstIntPoint))
        {
            t1Valid = true;
        }
        else
        {
            t1Valid = false;
            tValues.at(0) = maxT;
        }
        if (t2 > 0.0 && IsZValueIsInRangeOfNegativeOneAndOne(secondIntPoint))
        {

            t2Valid = true;
        }
        else
        {
            t2Valid = false;
            tValues.at(1) = maxT;
        }
    }
    else
    {
        t1Valid = false;
        t2Valid = false;

        tValues.at(0) = maxT;
        tValues.at(1) = maxT;
    }

    // test the end caps
    // check to see if were are parallel to  the  z axis origin. If that the case
    // the cylinder is not valid.
    if (IsParallelToTheZOrigin(v))
    {
        t3Valid = false;
        t4Valid = false;
        tValues.at(2) = maxT;
        tValues.at(3) = maxT;
    }
    else
    {

        double negVz = -v.GetElement(2);
        double part1 = p.GetElement(2) / negVz;
        double part2 = 1.0 / negVz;
        tValues.at(2) = part1 - part2;
        tValues.at(3) = part1 + part2;

        double t3 = tValues.at(2), t4 = tValues.at(3);

        pointsOfIntersections.at(2) = p + t3 * v;
        pointsOfIntersections.at(3) = p + t4 * v;

        qbVector<double> thirdIntPoint = pointsOfIntersections.at(2), fourthIntPoint = pointsOfIntersections.at(3);
        // check if the two pointsOfIntersection are valid

        if (t3 > 0.0 && IsSqrtOfSumOfXanYSquaresLessThan1(thirdIntPoint))
        {

            t3Valid = true;
        }
        else
        {
            t3Valid = false;
            tValues.at(2) = maxT;
        }

        if (t4 > 0.0 && IsSqrtOfSumOfXanYSquaresLessThan1(fourthIntPoint))
        {

            t4Valid = true;
        }
        else
        {
            t4Valid = false;
            tValues.at(3) = maxT;
        }
    }
    if (!(t1Valid || t2Valid || t3Valid || t4Valid))
    {
        return false;
    }

    double minT = maxT;
    int minTIndex = 0;
    double tValue;
    for (int i = 0; i < 4; i++)
    {
        tValue = tValues.at(i);
        if (tValue < minT)
        {
            minT = tValue;
            minTIndex = i;
        }
    }

    qbVector<double>
        validIntPoint = pointsOfIntersections.at(minTIndex);

    // if the minimum value is found at index 0 or 1,  we have a valid intersection with the cylinder itself.
    if (minTIndex < 2)
    {

        // transform the intersection point back into world coordinates.

        intPoint = trnfrmMatrix.Apply(validIntPoint, qbRT::FWDTFORM);

        // computer the local Normal.
        qbVector<double> orgNormal{3}, newNormal{3}, localOrigin, globalOrigin;
        localOrigin = ConstructVector(0.0, 0.0, 0.0);
        // globalOrgin is the local orgin converted to the world coordinates.
        globalOrigin = trnfrmMatrix.Apply(localOrigin, qbRT::FWDTFORM);

        orgNormal.SetElement(0, validIntPoint.GetElement(0));
        orgNormal.SetElement(1, validIntPoint.GetElement(1));
        // Normal for the z value will always be 0.
        orgNormal.SetElement(2, 0.0);

        newNormal = trnfrmMatrix.Apply(orgNormal, qbRT::FWDTFORM) - globalOrigin;
        newNormal.Normalize();
        localNormal = newNormal;
        // set color as the base color.
        localColor = baseColor;
        return true;
    }
    else
    {
        if (!IsParallelToTheZOrigin(v))
        {
            // check if we are inside the cylinder
            if (IsSqrtOfSumOfXanYSquaresLessThan1(validIntPoint))
            {

                intPoint = trnfrmMatrix.Apply(validIntPoint, qbRT::FWDTFORM);
                qbVector<double> localOrigin = ConstructVector(0.0, 0.0, 0.0), globalOrigin, normalVector = ConstructVector(0.0, 0.0, 0.0 + validIntPoint.GetElement(2));
                globalOrigin = trnfrmMatrix.Apply(localOrigin, qbRT::FWDTFORM);
                localNormal = trnfrmMatrix.Apply(normalVector, qbRT::FWDTFORM) - globalOrigin;
                localNormal.Normalize();
                localColor = baseColor;
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    return false;
}

bool qbRT::Cylinder::IsZValueIsInRangeOfNegativeOneAndOne(const qbVector<double> point)
{
    return fabs(point.GetElement(2)) < 1.0;
}

bool qbRT::Cylinder::IsParallelToTheZOrigin(const qbVector<double> point)
{

    return CloseEnough(point.GetElement(2), 0.0);
}

bool qbRT::Cylinder::IsSqrtOfSumOfXanYSquaresLessThan1(const qbVector<double> point)
{
    return sqrtf(GetSquare(point.GetElement(0)) + GetSquare(point.GetElement(1))) < 1.0;
}