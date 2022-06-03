#pragma once
#include "BaseObject.hpp"
class PlaneObject : public BaseObject {
public:
    PlaneObject();
    bool testForIntersections(
        const qbRT::Ray &castRay, 
        Vector3 &intersectionPoint, 
        Vector3 &localNormal,
        Vector3 &localColor
    ) const override;
    // get UV coordinates from an intersection
    virtual Vector3 getUVCoordinates(const Vector3 &t_intersectionPoint) const override;
};