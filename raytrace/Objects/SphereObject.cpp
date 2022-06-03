#pragma once
#include "SphereObject.hpp"
SphereObject::SphereObject() {};
SphereObject::~SphereObject() {
    
};
qbRT::Ray ranFun(const qbRT::Ray &castRay) {
    qbRT::Ray outputRay;
    outputRay.aVector = castRay.aVector;
    outputRay.bVector = castRay.bVector;
    //outputRay.aVector = apply(inputRay.aVector, directionFlag);
    //outputRay.bVector = apply(inputRay.bVector, directionFlag);
    outputRay.labVector = outputRay.bVector - outputRay.aVector;
    return outputRay;
}
bool SphereObject::testForIntersections(
    const qbRT::Ray &castRay, 
    Vector3 &intersectionPoint, 
    Vector3 &localNormal,
    Vector3 &localColor
) {
    qbRT::Ray backRay = geometricTransform.apply(castRay, false);
	// Compute the values of a, b and c.
	Vector3 vhat = backRay.labVector;
	vhat.normalize();
	
	/* Note that a is equal to the squared magnitude of the
		direction of the cast ray. As this will be a unit vector,
		we can conclude that the value of 'a' will always be 1. */
	// a = 1.0;
	
	// Calculate b.
	double b = 2.0 * Vector3::dot(backRay.aVector, vhat);
	
	// Calculate c.
	double c = Vector3::dot(backRay.aVector, backRay.aVector) - 1.0;
	
	// Test whether we actually have an intersection.
	double intersectionTest = (b*b) - 4.0 * c;
	Vector3 poi;
	if (intersectionTest < 0.0) return false;
    double numSQRT = sqrtf(intersectionTest);
    double t1 = (-b + numSQRT) / 2.0;
    double t2 = (-b - numSQRT) / 2.0;
    
    /* If either t1 or t2 are negative, then at least part of the object is
        behind the camera and so we will ignore it. */
    if ((t1 < 0.0) || (t2 < 0.0)) return false;
    // Determine which point of intersection was closest to the camera.
    if (t1 < t2) poi = backRay.aVector + (vhat * t1);
    else poi = backRay.aVector + (vhat * t2);
    intersectionPoint = geometricTransform.apply(poi, true);
    // Compute local normal (Easy for a sphere at the origin!)
    Vector3 objectOrigin{ 0.0, 0.0, 0.0 };
    
//        std::cout << geometricTransform.getForwardMatrix() << std::endl;
    Vector3 transformedObjectOrigin = geometricTransform.apply(objectOrigin, true);

    localNormal = intersectionPoint - transformedObjectOrigin;
    localNormal.normalize();

    // Return color
    localColor = baseColor;

    //TODO: move defining UV coordinates to a function
    // compute UV coordinates
    double x = poi.x;
    double y = poi.y;
    double z = poi.z;
    double u = atan(sqrtf(x * x + y * y) / z);
    double v = atan(y/x);
    if (x < 0) {
        v += M_PI;
    }
    u /= M_PI;
    v /= M_PI;
    UVCoordinates.x = u;
    UVCoordinates.y = v;
    return true;
}