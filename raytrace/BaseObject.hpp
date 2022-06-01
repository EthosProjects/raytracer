#pragma once
#include "Ray.hpp"
#include "GeometricTransform.hpp"
class BaseObject {
public:
    BaseObject();
    virtual ~BaseObject();

    virtual bool testForIntersections(
        const qbRT::Ray &castRay, 
        Vector3 &intersectionPoint, 
        Vector3 &localNormal,
        Vector3 &localColor
    );

    void setTransformMatrix(const GeometricTransform &transformMatrix);
    
    bool closeEnough(const double f1, const double f2);

    Vector3 baseColor;

    GeometricTransform geometricTransform;
};