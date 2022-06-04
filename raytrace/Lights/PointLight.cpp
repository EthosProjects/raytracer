#pragma once
#include "PointLight.hpp"

//Default constructor
PointLight::PointLight () {
    color = Vector3(1.0, 1.0, 1.0);
    intensity = 1.0;
};
bool PointLight::computeIllumination(	
    const Vector3 &t_intersectionPoint, 
    const Vector3 &t_localNormal,
    const std::vector<BaseObject*> &t_objectList,
    BaseObject* &t_currentObject,
    Vector3 &o_color, 
    double &o_intensity
) {
	// Construct a vector pointing from the intersection point to the light.
    Vector3 lightDirection = (positionVector - t_intersectionPoint).getNormalized();
    double lightDistance = (positionVector - t_intersectionPoint).getMagnitude();
	
	// Compute a starting point.
	Vector3 startPoint = t_intersectionPoint;
	
	// Construct a ray from the point of intersection to the light.
	Ray lightRay (startPoint, startPoint + lightDirection);
	
	/* Check for intersections with all of the objects
		in the scene, except for the current one. */
	Vector3 pointOfIntersection;
	Vector3 pointOfIntersectionNormal;
	Vector3 pointOfIntersectionColor;
	bool validIntersection = false;
	for (auto sceneObject : t_objectList) {
		if (sceneObject == t_currentObject) continue;
        validIntersection = sceneObject -> testForIntersections(lightRay, pointOfIntersection, pointOfIntersectionNormal, pointOfIntersectionColor);
        if (validIntersection) {
            double dist = (pointOfIntersection - startPoint).getMagnitude();
            if (dist > lightDistance)
                validIntersection = false;
        }
		
		/* If we have an intersection, then there is no point checking further
			so we can break out of the loop. In other words, this object is
			blocking light from this light source. */
		if (validIntersection) break;
	}

	if (validIntersection) {
		// Shadow, so no illumination.
		o_color = color;
		o_intensity = 0.0;
		return false;

    } 
    /* Only continue to compute illumination if the light ray didn't
        intersect with any objects in the scene. Ie. no objects are
        casting a shadow from this light source. */
    // Compute the angle between the local normal and the light ray.
    // Note that we assume that localNormal is a unit vector.
    double angle = acos(Vector3::dot(t_localNormal, lightDirection));
    
    // If the normal is pointing away from the light, then we have no illumination.
    if (angle > 1.5708) {
        // No illumination.
        o_color = color;
        o_intensity = 0.0;
        return false;
    }
    // We do have illumination.
    o_color = color;
    o_intensity = intensity * (1.0 - (angle / 1.5708));
    return true;
}