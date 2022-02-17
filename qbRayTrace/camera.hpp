#ifndef CAMERA_H
#define CAMERA_H
#include "math.h"
#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "vectormanipulators.hpp"
namespace qbRT
{
    class Camera
    {
    private:
    public:
        Camera();
        // function to set the camera parameter
        void SetPosition(double x, double y, double z);
        void SetLookAt(double x, double y, double z);
        void SetUp(double x, double y, double z);
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

        // the camera array will be used as output, but the function will return true
        // if it was able to create an ray.
        bool GenerateRay(float proScreenX, float proScreenY, qbRT::Ray &cameraRay);
        void UpdateCameraGeometry();

        ~Camera();

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
    };

}

#endif
