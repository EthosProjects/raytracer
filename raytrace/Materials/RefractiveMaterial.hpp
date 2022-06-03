#pragma once
#include "BaseMaterial.hpp"
class SimpleRefractiveMaterial : public BaseMaterial {
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
    Vector3 computeTranslucencyColor (
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        const BaseObject* t_closestObject,
        const Vector3 &t_closestIntersectionPoint,
        const Vector3 &t_closestLocalNormal, 
        const qbRT::Ray t_cameraRay
    );
    Vector3 color;
    double reflectivity { 0.0 };
    double shininess { 0.0 };
    double transluncy { 0.0 };
    double refractiveIndex { 0.0 };
};