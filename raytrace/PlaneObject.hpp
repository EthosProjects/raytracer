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
    ) override;
private:
};