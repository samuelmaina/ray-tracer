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

    std::vector<qbVector<double>> pointsOfIntersections;

    // there will be 4 points of intersections, two that one circular side of the
    // cylinder and the  other two at the other circular surface.
    std::vector<double> tValues{4};

    bool t1Valid, t2Valid, t3Valid, t4Valid;

    // Compute a, b and c
    double a, b, c;
    double vx = v.GetElement(0), vy = v.GetElement(1),
           px = p.GetElement(0), py = p.GetElement(1);

    a = GetSquare(vx) + GetSquare(vy);
    b = 2.0 * (px * py + py * vy);
    c = GetSquare(vx) + GetSquare(py) - 1.0;

    if (GetRoots(a, b, c, tValues.at(0), tValues.at(1)))
    {
        qbVector<double> firstIntPoint = pointsOfIntersections.at(0), secondIntPoint = pointsOfIntersections.at(1);
        // there is a valid intersection for the first two intersection points.
        // compute the intersection using the values of t1 and t2
        double t1 = tValues.at(0), t2 = tValues.at(1);
        firstIntPoint = p + (v * t1);
        secondIntPoint = p + (v * t2);
        if (t1 > 0.0 && CheckIfZValueIsInRangeOfNegativeOneAndOne(firstIntPoint))
        {
            t1Valid = true;
        }
        else
        {
            t1Valid = false;
            tValues.at(0) = maxT;
        }
        if (t2 > 0.0 && CheckIfZValueIsInRangeOfNegativeOneAndOne(secondIntPoint))
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
    if (CloseEnough(v.GetElement(2), 0.0))
    {
        t1Valid = false;
        t2Valid = false;
        tValues.at(0) = maxT;
        tValues.at(1) = maxT;
    }
    else
    {
        double negVz = -v.GetElement(2);
        double part1 = p.GetElement(2) / negVz;
        double part2 = 1.0 / negVz;
        tValues.at(2) = part1 - part2;
        tValues.at(3) = part1 + part2;

        qbVector<double> thirdIntPoint = pointsOfIntersections.at(2), fourthIntPoint = pointsOfIntersections.at(3);

        double t3 = tValues.at(2), t4 = tValues.at(3);

        thirdIntPoint = p + t3 * v;
        fourthIntPoint = p + t4 * v;

        // check if the two pointsOfIntersection are valid

        if (t3 > 0.0 && CheckIfTheSqrtOfSumOfXanYSquaresLessThan1(thirdIntPoint))
        {
            t3Valid = true;
        }
        else
        {
            t3Valid = false;
            tValues.at(2) = maxT;
        }

        if (t4 > 0.0 && CheckIfTheSqrtOfSumOfXanYSquaresLessThan1(fourthIntPoint))
        {
            t4Valid = true;
        }
        else
        {
            t4Valid = false;
            tValues.at(3) = maxT;
        }
    }

    // stop if there was no intersection found.
    if (!(t1Valid || t2Valid || t3Valid || t4Valid))
        return false;

    double minT = 0.0;
    int minTIndex = 0;
    double tValue;
    for (int i = 0; i < tValues.size(); i++)
    {
        tValue = tValues.at(i);
        if (tValue < minT)
        {
            minT = tValue;
            minTIndex = i;
        }
    }
    // if the minimum value is found at index 0 or 1,  we have a valid intersection with the cylinder itself.
    if (minTIndex < 2)
    {
    }
}

bool CheckIfZValueIsInRangeOfNegativeOneAndOne(const qbVector<double> point)
{
    return fabs(point.GetElement(2)) < 1.0;
}

bool CheckIfTheSqrtOfSumOfXanYSquaresLessThan1(const qbVector<double> point)
{
    return sqrtf(GetSquare(point.GetElement(0)) + GetSquare(point.GetElement(1))) < 1.0;
}