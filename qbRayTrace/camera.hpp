#ifndef CAMERA_H
#define CAMERA_H
#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
namespace qbRT
{
    class Camera
    {
    private:
    public:
        Camera();
        //function to set the camera parameter
        void SetPosition(const qbVector<double> &newPosition);
        void SetLookAt(const qbVector<double> &newLookAt);
        void SetUp(const qbVector<double> &upVector);
        void SetLength(double newLength);
        void SetAspect(double newAspect);
        void SethorzSize(double newSize);

        qbVector<double> GetPosition();
        qbVector<double> GetLookAt();
        qbVector<double> GetUp();
        qbVector<double> GetU();
        qbVector<double> GetV();
        qbVector<double> GetScreenCentre();

        double GetLength();
        double GetHorizontalSize();

        Ray GenerateRay(float proScreenX, float proScreenY);
        void UpdateCameraGeometry();

    private:
        qbVector<double> m_position{3};
        qbVector<double> m_lookAt{3};
        qbVector<double> m_cameraUp{3};
        double m_length;
        double m_horiLength;
        double m_aspectRatio;

        qbVector<double> m_alignVector{3};
        qbVector<double> m_projectionScreenU{3};
        qbVector<double> m_projectionScreenV{3};
        qbVector<double> m_projectionScreenCentre{3};

        ~Camera();
    };

}

#endif
