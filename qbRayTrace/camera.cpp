#include "camera.hpp"
#include "math.h"

qbRT::Camera::Camera()
{
    m_position = qbVector<double>{
        std::vector<double>{0.0, -10, 0.0}};
    m_lookAt = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
    m_cameraUp = qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}};
    m_length = 1.0;
    m_horiLength = 1.0;
    m_aspectRatio = 1.0;
}

qbRT::Camera::~Camera(){

};
void qbRT::Camera::SetPosition(const qbVector<double> &newPosition)
{
    m_position = newPosition;
}

void qbRT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
    m_lookAt = newLookAt;
}

void qbRT::Camera::SetUp(const qbVector<double> &upVector)
{
    m_cameraUp = upVector;
}

void qbRT::Camera::SetLength(double newLength)
{
    m_length = newLength;
}
void qbRT::Camera::SethorzSize(double newHorzSize)
{
    m_horiLength = newHorzSize;
}

void qbRT::Camera::SetAspect(double newAspect)
{
    m_aspectRatio = newAspect;
}

qbVector<double> qbRT::Camera::GetPosition()
{
    return m_position;
}

double qbRT::Camera::GetLength()
{
    return m_length;
}

qbVector<double> qbRT::Camera::GetU()
{
    return m_projectionScreenU;
}

qbVector<double> qbRT::Camera::GetV()
{
    return m_projectionScreenV;
}
qbVector<double> qbRT::Camera::GetScreenCentre()
{
    return m_projectionScreenCentre;
}

//function to calculate the camera geometry;
void qbRT::Camera::UpdateCameraGeometry()
{
    //first, compute the vector from the camera position to the lookAt position.
    m_alignVector = m_lookAt - m_position;

    //normalize the vector. The normalize vector has a magnitude of 1 which is convinient
    //for calculations.
    m_alignVector.Normalize();

    //compute the U and V vectors of the camera.
    m_projectionScreenU = qbVector<double>::cross(m_alignVector, m_cameraUp);
    m_projectionScreenU.Normalize();
    //we have the alignVector and the U vector. use the two to find the V.
    //V is perpendicular to the plane spanned by the align vector and U.
    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignVector);
    m_projectionScreenV.Normalize();

    //compute  the position of the centre point of the screen.
    //move the screen;
    m_projectionScreenCentre = m_position + (m_length * m_alignVector);

    //Modify the U and V vectors to match the size and the aspect ratio.
    m_projectionScreenU = m_projectionScreenU * m_horiLength;
    m_projectionScreenV = m_projectionScreenV * (m_horiLength / m_aspectRatio);
}

//pro is projection
bool qbRT::Camera::GenerateRay(float proScreenX, float proScreenY, qbRT::Ray &cameraRay)
{
    //compute the location of the screen point in world coordinate.
    qbVector<double> screen3DPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
    qbVector<double> screen3DCoordinate = screen3DPart1 + (m_projectionScreenV * proScreenY);

    Ray r = Ray(m_position, screen3DCoordinate);
    cameraRay = r;
    return true;
}