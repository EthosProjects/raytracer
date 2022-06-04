#pragma once
#include "BaseLight.hpp"
class PointLight: public BaseLight {
    public:
    PointLight();
    virtual bool computeIllumination(
        const Vector3 &t_intersectionPoint, 
        const Vector3 &t_localNormal,
        const std::vector<BaseObject*> &t_objectList,
        BaseObject* &t_currentObject,
        Vector3 &t_color,
        double &t_intensity
    );
};