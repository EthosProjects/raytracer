#pragma once
#include "Ray.hpp"

class Camera {
public:
    // The default constructor.
    Camera();
    
    // Functions to set camera parameters.
    void setPositionVector	(const Vector3 &newPositionVector);
    void setLookAtVector	(const Vector3 &newLookAtVector);
    void setUpVector		(const Vector3 &upVector);
    void setLength	        (double newLength);
    void setWidth           (double newWidth);
    void setAspectRatio	    (double newAspectRatio);
    
    // Functions to return camera parameters.
    Vector3	getPositionVector();
    Vector3	getLookAtVector();
    Vector3	getUpVector();
    Vector3	getUVector();
    Vector3	getVVector();
    Vector3	getProjectionScreenCenterVector();
    double	getLength();
    double	getWidth();
    double	getAspectRatio();
    
    // Function to generate a ray.
    bool generateRay(float projectionScreenX, float projectionScreenY, Ray &cameraRay);
    
    // Function to update the camera geometry.
    void updateCameraGeometry();
    
private:
    Vector3 positionVector	            ;
    Vector3 lookAtVector		        ;
    Vector3 upVector				    ;
    double length;
    double width;
    double aspectRatio;
    
    Vector3 alignmentVector				;
    Vector3 UVector			;
    Vector3 VVector			;
    Vector3 projectionScreenCenterVector;
};