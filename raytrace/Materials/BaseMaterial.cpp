#pragma once
#include "BaseMaterial.hpp"

Vector3 BaseMaterial::computeColor(
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    const BaseObject* t_closestObject,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const qbRT::Ray t_cameraRay
) {
    return Vector3();

};
Vector3 BaseMaterial::computeDiffuseColor(
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    const BaseObject* t_closestObject,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const qbRT::Ray t_cameraRay,
    const Vector3 &t_localColor
) {
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    bool illuminationFound = false;
    for (auto currentLight: t_lightList) {
        double intensity { 1.0 };
        Vector3 color;
        if (!currentLight->computeIllumination(
            t_closestIntersectionPoint,
            t_closestLocalNormal,
            t_objectList,
            t_closestObject,
            color,
            intensity
        )) continue;
        illuminationFound = true;
        red += color.x * intensity;
        green += color.y * intensity;
        blue += color.z * intensity;
    }
    //if (!illuminationFound) return Vector3(0.0, 0.0, 0.0);
    return Vector3 {
        red * t_localColor.x,
        green * t_localColor.y,
        blue * t_localColor.z
    };
};

Vector3 BaseMaterial::computeReflectionColor(
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    const BaseObject* t_closestObject,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const qbRT::Ray t_incidentRay
) {
    Vector3 reflectionColor;
    Vector3 d = t_incidentRay.labVector;
    Vector3 reflectionVector = d - (2.0 * Vector3::dot(d, t_closestLocalNormal) * t_closestLocalNormal);
    //Construct the reflection ray
    qbRT::Ray reflectionRay { t_closestIntersectionPoint, t_closestIntersectionPoint + reflectionVector};
    //Cast ray into scene
    //TODO: duplicate of inner part of scene file. 
    //I could make this simpler by creating an "intersection" class
    //Could be rewritten as Intersection intersection = t_incidentRay.cast(...)
    // if (!intersection.exists) return;
    BaseObject* closestObject;
    Vector3 closestIntersectionPoint;
    Vector3 closestLocalNormal;
    Vector3 closestLocalColor;
    bool intersectionFound = castRay (
        reflectionRay,
        t_objectList,
        t_lightList,
        t_closestObject,
        closestObject,
        closestIntersectionPoint,
        closestLocalNormal,
        closestLocalColor
    );
    //ENDBLOCK
    // compute illumination of closest object
    Vector3 materialColor;
    if (intersectionFound && reflectionCount < maxReflectionCount) {
        reflectionCount++;
        if (closestObject->hasMaterial()) {
            // Using material
            materialColor = closestObject->p_material->computeColor(
                t_objectList,
                t_lightList,
                closestObject,
                closestIntersectionPoint,
                closestLocalNormal,
                reflectionRay
            );
        } else {
            materialColor = computeDiffuseColor(
                t_objectList,
                t_lightList,
                closestObject,
                closestIntersectionPoint,
                closestLocalNormal,
                reflectionRay,
                closestObject->baseColor
            );
        }
    }
    reflectionColor = materialColor;
    return reflectionColor;
};
// TODO:
// nearly an exact copy from the scene's function. Could possibly make into a global function instead
// Proposal: I could possibly make cast ray a function of ray rather than doing this. Making it 
// a function of ray would make logical sense. I could call it using Ray::Cast(...)
bool BaseMaterial::castRay(
    const qbRT::Ray t_ray,
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    const BaseObject* &t_object,
    BaseObject* &o_closestObject,
    Vector3 &o_closestIntersectionPoint,
    Vector3 &o_closestLocalNormal,
    Vector3 &o_closestLocalColor
) {
    double minimumDistance = 1e6;
    bool intersectionFound = false;
    for (auto currentObject: t_objectList) {
        if (currentObject == t_object) continue;;
        Vector3 intersectionPoint;
        Vector3 localNormal;
        Vector3 localColor;
        bool validIntersection = currentObject->testForIntersections(
            t_ray,
            intersectionPoint,
            localNormal,
            localColor
        );
        if (!validIntersection) continue;
        intersectionFound = true;
        double dist = (intersectionPoint - t_ray.aVector).getMagnitude();
        if (dist < minimumDistance) {
            minimumDistance = dist;
            o_closestObject = currentObject;
            o_closestIntersectionPoint = intersectionPoint;
            o_closestLocalNormal = localNormal;
            o_closestLocalColor = localColor;
        }
    }
    return intersectionFound;
};