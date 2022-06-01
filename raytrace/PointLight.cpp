#pragma once
#include "PointLight.hpp"
PointLight::PointLight () {
    color = Vector3(1.0, 1.0, 1.0);
    intensity = 1.0;
};
PointLight::~PointLight () {

}
bool PointLight::computeIllumination(
    const Vector3 &t_intersectionPoint, 
    const Vector3 &t_localNormal,
    const std::vector<BaseObject*> &t_objectList,
    const BaseObject* t_currentObject,
    Vector3 &t_color,
    double &t_intensity
) {
    //Compute the direction
    Vector3 lightDirection = (positionVector - t_intersectionPoint).getNormalized();
    //Compute a starting point
    Vector3 startPoint = t_intersectionPoint;
    //Compute angle between local normal and the light ray
    //Note that we assume that localNormal is a unit vector
    double angle = acos(Vector3::dot(t_localNormal, lightDirection));
    if (angle > 1.5708) {
        t_color = color;
        t_intensity = 0.0;
        return false;
    }
    t_color = color;
    t_intensity = intensity * (1.0 - (angle / 1.5708));
    return true;
};