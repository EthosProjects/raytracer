#pragma once
#include "../Ray.hpp"
#include "../GeometricTransform.hpp"
//TODO: Define M_PI locally to avoid dependence on external libraries
#include "../../SDL2/SDL.h"
class BaseMaterial;
class BaseObject {
public:
// TODO: Make sure base object handles pointers properly

    BaseObject();
    virtual ~BaseObject();

    virtual bool testForIntersections(
        const qbRT::Ray &castRay, 
        Vector3 &intersectionPoint, 
        Vector3 &localNormal,
        Vector3 &localColor
    );

    bool closeEnough(const double f1, const double f2);

    Vector3 baseColor;

    GeometricTransform geometricTransform;
    void setTransformMatrix(const GeometricTransform &transformMatrix);
    

    BaseMaterial* p_material { nullptr };
    void setMaterial(BaseMaterial* t_material);
    bool hasMaterial();
    // store UV coordinates from an intersection
    Vector3 UVCoordinates;
};