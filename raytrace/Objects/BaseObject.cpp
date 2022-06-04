#pragma once
#include "BaseObject.hpp"

#define EPSILON 1e-21f;

BaseObject::BaseObject() {

}
BaseObject::~BaseObject() {

}
bool BaseObject::testForIntersections (
    const Ray &castRay, 
    Vector3 &intersectionPoint, 
    Vector3 &localNormal,
    Vector3 &localColor
) const { return false; }
void BaseObject::setTransformMatrix(const GeometricTransform &transformMatrix) { 
    geometricTransform = transformMatrix;
};
void BaseObject::setMaterial(BaseMaterial* t_material) {
    p_material = t_material;
};
bool BaseObject::hasMaterial() const {
    return p_material != nullptr;
};
bool BaseObject::closeEnough(const double f1, const double f2) { return fabs(f1 - f2) < EPSILON; };
bool BaseObject::closeEnoughLoose(const double f1, const double f2) { return fabs(f1 - f2) < 1e-5; };
Vector3 BaseObject::getUVCoordinates(const Vector3 &t_intersectionPoint) const {
    return Vector3 {
        0.5,
        0.5,
        0.5
    };
};