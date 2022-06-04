#pragma once
#include "Ray.hpp"
Ray::Ray(): 
	aVector (0.0, 0.0, 0.0),
	bVector (0.0, 0.0, 1.0)
{
    labVector = bVector - aVector;
}

Ray::Ray(const Vector3 &point1, const Vector3 &point2): 
	aVector (point1),
	bVector (point2){
    labVector = bVector - aVector;
};
Vector3 Ray::GetBVector() const { return bVector; };
Vector3 Ray::GetAVector() const { return aVector; };
