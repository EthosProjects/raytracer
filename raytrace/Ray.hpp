#pragma once
#include "line/Vector3.hpp"
#include <vector>

class Ray {
public:
    Ray();
    Ray(const Vector3 &point1, const Vector3 &point2);
    
    Vector3 GetAVector() const;
    Vector3 GetBVector() const;
    Vector3 aVector;
    Vector3 bVector;
    Vector3 labVector;
};