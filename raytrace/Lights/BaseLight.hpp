#pragma once
#include "../Ray.hpp"
#include "../Objects/BaseObject.hpp"
class BaseLight {
public:
    // Function to compute illumination contribution.
    virtual bool computeIllumination(
        const Vector3 &t_intersectionPoint, 
        const Vector3 &t_localNormal,
        const std::vector<BaseObject*> &t_objectList,
        BaseObject* &t_currentObject,
        Vector3 &t_color,
        double &t_intensity
    );
    Vector3 color;
    Vector3 positionVector;
    double intensity;
};