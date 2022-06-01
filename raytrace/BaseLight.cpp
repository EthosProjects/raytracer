#pragma once
#include "BaseLight.hpp"
BaseLight::BaseLight() {

};
BaseLight::~BaseLight(){

};
bool BaseLight::computeIllumination(
    const Vector3 &t_intersectionPoint, 
    const Vector3 &t_localNormal,
    const std::vector<BaseObject*> &t_objectList,
    const BaseObject* t_currentObject,
    Vector3 &t_color,
    double &t_intensity
) {
    return false;
};