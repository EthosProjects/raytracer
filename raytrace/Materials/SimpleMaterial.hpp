#pragma once
#include "BaseMaterial.hpp"
class SimpleMaterial: public BaseMaterial {
public:
    Vector3 computeColor (
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        const BaseObject* t_closestObject,
        const Vector3 &t_closestIntersectionPoint,
        const Vector3 &t_closestLocalNormal, 
        const qbRT::Ray t_cameraRay
    ) override;
    Vector3 computeSpecularColor (
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        const Vector3 &t_closestIntersectionPoint,
        const Vector3 &t_closestLocalNormal, 
        const qbRT::Ray t_cameraRay
    );
    Vector3 color;
    double reflectivity;
    double shininess;
};