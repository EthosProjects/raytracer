#pragma once
#include "PlaneObject.hpp"
#include <cmath>
PlaneObject::PlaneObject () {

};
bool PlaneObject::testForIntersections(
    const qbRT::Ray &castRay, 
    Vector3 &intersectionPoint, 
    Vector3 &localNormal,
    Vector3 &localColor
) const {
    qbRT::Ray backRay = geometricTransform.apply(castRay, false);
	// Compute the values of a, b and c.
	Vector3 vhat = backRay.labVector;
	vhat.normalize();
	
    if (closeEnough(backRay.labVector.z, 0.0)) return false;
    double t = backRay.aVector.z / -vhat.z;
    if (t < 0.0) return false;
    double u = backRay.aVector.x + vhat.x * t;
    double v = backRay.aVector.y + vhat.y * t;
    if (!(abs(u) < 1.0 && abs(v) < 1.0)) return false;
    Vector3 poi = backRay.aVector + vhat * t;
    intersectionPoint = geometricTransform.apply(poi, true);
    Vector3 objectOrigin { 0.0, 0.0, 0.0 };
    Vector3 normalVector = Vector3 { 0.0, 0.0, -1.0 };
    Vector3 globalObjectOrigin = geometricTransform.apply(objectOrigin, true);
    localNormal = geometricTransform.apply(normalVector, true) - globalObjectOrigin;
    localColor = baseColor;
    return true;
}
// get UV coordinates from an intersection
Vector3 PlaneObject::getUVCoordinates(const Vector3 &t_intersectionPoint) const {
    return Vector3 {
        t_intersectionPoint.x,
        t_intersectionPoint.y,
        0.0
    };
};