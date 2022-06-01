#pragma once
#include "BaseObject.hpp"
class SphereObject: public BaseObject {
public:
    SphereObject();
    ~SphereObject();
    virtual bool testForIntersections(
        const qbRT::Ray &castRay, 
        Vector3 &intersectionPoint, 
        Vector3 &localNormal,
        Vector3 &localColor
    )  override;
};