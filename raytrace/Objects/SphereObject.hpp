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
    ) const override;
    // get UV coordinates from an intersection
    Vector3 getUVCoordinates(const Vector3 &t_intersectionPoint) const override;
};