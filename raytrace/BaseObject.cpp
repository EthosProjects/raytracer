#pragma once
#include "BaseObject.hpp"

#define EPSILON 1e-21f;

BaseObject::BaseObject() {

}
BaseObject::~BaseObject() {

}
bool BaseObject::testForIntersections (
    const qbRT::Ray &castRay, 
    Vector3 &intersectionPoint, 
    Vector3 &localNormal,
    Vector3 &localColor
) { return false; }
void BaseObject::setTransformMatrix(const GeometricTransform &transformMatrix) { 
    geometricTransform = transformMatrix;
};
bool BaseObject::closeEnough(const double f1, const double f2) { return fabs(f1 - f2) < EPSILON }