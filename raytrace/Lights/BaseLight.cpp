#pragma once
#include "BaseLight.hpp"

// Function to compute illumination
bool BaseLight::computeIllumination(
    const Vector3 &t_intersectionPoint, 
    const Vector3 &t_localNormal,
    const std::vector<BaseObject*> &t_objectList,
    BaseObject* &t_currentObject,
    Vector3 &t_color,
    double &t_intensity
) {
    return false;
};