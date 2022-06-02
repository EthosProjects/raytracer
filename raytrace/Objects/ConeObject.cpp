#pragma once
#include "ConeObject.hpp"
#include <array>
//TODO: DONT COPY BAD CODE YOU FUCKING MORON. WHY DID YOU COPY THIS SHIT INSTEAD OF REFACTORING FIRST???
//THIS IS WHY NO ONE FUCKING LIKES YOU
bool ConeObject::testForIntersections(
    const qbRT::Ray &t_ray, 
    Vector3 &o_intersectionPoint, 
    Vector3 &o_localNormal,
    Vector3 &o_color
) {
    qbRT::Ray backRay = geometricTransform.apply(t_ray, false);
    // Copy the lab ray's lab vector and normalize
	Vector3 vhat = backRay.labVector;
	vhat.normalize();
    //Get the start point
    Vector3 p = backRay.aVector;
    //compute a b and c
    double a = vhat.x * vhat.x + vhat.y * vhat.y - vhat.z * vhat.z;
    double b = 2.0 * (p.x * vhat.x + p.y * vhat.y - p.z * vhat.z);
    double c = p.x * p.x + p.y * p.y - p.z * p.z;
    // Compute b^2 - 4ac
	double numSQRT = sqrtf((b*b) - 4.0 * a * c); 
    std::array<Vector3, 3> pointOfIntersection;
    std::array<double, 3> t;
    bool t1Valid, t2Valid, t3Valid { 0 };
    if (numSQRT < 0.0) {
        t1Valid = false;
        t2Valid = false;
        t.at(0) = 100e6;
        t.at(1) = 100e6;
    } else {
        // There was an intersection. Compute values for t
        t.at(0) = (-b + numSQRT) / (2 * a);
        t.at(1) = (-b - numSQRT) / (2 * a);
        // Compute the points of intersection
        pointOfIntersection.at(0) = backRay.aVector + (vhat * t.at(0));
        pointOfIntersection.at(1) = backRay.aVector + (vhat * t.at(1));
        //Check if any of these are valid
        if (t.at(0) > 0 && pointOfIntersection.at(0).z > 0.0 && pointOfIntersection.at(0).z < 1.0) {
            t1Valid = true;
        } else {
            t1Valid = false;
            t.at(0) = 100e6;
        }
        if (t.at(1) > 0 && pointOfIntersection.at(1).z > 0.0 && pointOfIntersection.at(1).z < 1.0) {
            t2Valid = true;
        } else {
            t2Valid = false;
            t.at(1) = 100e6;
        }
    }
    if (closeEnough(vhat.z, 0.0)) {
        t3Valid = false;
        t.at(2) = 100e6;
    } else {
        //This is a plane :)
        t.at(2) = (backRay.aVector.z - 1.0) / -vhat.z;
        pointOfIntersection.at(2) = backRay.aVector + t.at(2) * vhat;
        //Check if these are valid
        if (t.at(2) > 0.0 && sqrtf(pointOfIntersection.at(2).x * pointOfIntersection.at(2).x + pointOfIntersection.at(2).y * pointOfIntersection.at(2).y) < 1.0) {
            t3Valid = true;
        } else {
            t3Valid = false;
            t.at(2) = 100e6;
        }
    }
    if (!t1Valid && !t2Valid && !t3Valid) return false;
    int minimumIndex = 0;
    double minimumValue = 100.0;
    for (int i = 0; i < 3; i++) {
        if (t.at(i) < minimumValue) {
            minimumIndex = i;
            minimumValue = t.at(i);
        }
    }
    // If x is either 0 or 1, then we have a valid intersection with the cylinder itself
    Vector3 validPointOfIntersection = pointOfIntersection.at(minimumIndex);
    // TODO: ensure that "localNormal" refers exclusively to normal vectors in their local coordinate space
    // This is to ensure the meaning of local is clear when it refers to position. local refers to a vector
    // in an object's local coordinate space
    if (minimumIndex < 2) {
        // In the cylinder
        // In the cylinder
        o_intersectionPoint = geometricTransform.apply(validPointOfIntersection, true);
        // Compute the local normal
        Vector3 localNormal;
        Vector3 globalNormal;
        Vector3 localOrigin { 0.0, 0.0, 0.0 };
        Vector3 globalOrigin = geometricTransform.apply(localOrigin, true);
        localNormal.x = validPointOfIntersection.x; 
        localNormal.y = validPointOfIntersection.y; 
        localNormal.z = -sqrtf(
            validPointOfIntersection.x * validPointOfIntersection.x +
            validPointOfIntersection.y * validPointOfIntersection.y
        );
        globalNormal = geometricTransform.apply(localNormal, true) - globalOrigin;
        o_localNormal = globalNormal.getNormalized();
        o_color = baseColor;
        return true;
    } else {
        // In the disk
        o_intersectionPoint = geometricTransform.apply(validPointOfIntersection, true);
        // Compute the local normal
        Vector3 localOrigin;
        Vector3 localNormal {
            0.0,
            0.0,
            0.0 + validPointOfIntersection.z
        };
        Vector3 globalOrigin = geometricTransform.apply(localOrigin, true);
        Vector3 normal = geometricTransform.apply(localNormal, true) - globalOrigin;
        o_localNormal = normal.getNormalized();
        o_color = baseColor;
        return true; 
    };
};