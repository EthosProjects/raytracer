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
    double lightDistance = (positionVector - t_intersectionPoint).getMagnitude();
    //Compute a starting point
    Vector3 startPoint = t_intersectionPoint;
    //Contruct a ray to the light source
    qbRT::Ray lightRay {startPoint, startPoint + lightDirection};
    Vector3 pointOfIntersection;
    Vector3 pointOfIntersectionNormal;
    Vector3 pointOfIntersectionColor;
    bool validIntersection { false };
    for (auto currentObject : t_objectList) {
        if (currentObject == t_currentObject) continue;
        validIntersection = currentObject->testForIntersections(
            lightRay,
            pointOfIntersection,
            pointOfIntersectionNormal,
            pointOfIntersectionColor
        );
        // Tells the code to keep looking for one if it didn't find one. If it did, then next
        // I compute to make sure the found item is between the light and the object;
        if (!validIntersection) continue;
        double distance = (pointOfIntersection - startPoint).getMagnitude();
        if (distance > lightDistance) validIntersection = false;
        if (validIntersection) return false;
    }
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