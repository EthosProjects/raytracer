#pragma once

#include "line\Matrix4.hpp"
#include "line\Vector3.hpp"
#include "Ray.hpp"
bool constexpr FWDTFORM = true;
bool constexpr BCKTFORM = false;
class GeometricTransform {
public: 
    GeometricTransform();
    GeometricTransform(const Matrix4 &fwd, const Matrix4 &bck);
    GeometricTransform(const Vector3 &translation, const Vector3 &rotation, const Vector3 &scale);

    void setTransform (const Vector3 &translation, const Vector3 &rotation, const Vector3 &scale);

    Matrix4 getForwardMatrix();
    Matrix4 getBackwardMatrix();
    qbRT::Ray apply (const qbRT::Ray &inputRay, bool directionFlag);
    Vector3 apply (const Vector3 &inputVector, bool directionFlag);
    qbRT::Ray ranFun(const qbRT::Ray &castRay, bool directionFlag);
    Vector3 ranFun (const Vector3 &inputVector, bool directionFlag);
    friend GeometricTransform operator* (const GeometricTransform &lhs, const GeometricTransform &rhs);
    GeometricTransform operator=(const GeometricTransform &rhs);
    friend std::ostream& operator<<(std::ostream& os, const GeometricTransform& gtfm);
    GeometricTransform operator*= (const GeometricTransform &rhs);
private: 
    Matrix4 forwardTransform;
    Matrix4 backwardTransform;

};
GeometricTransform operator* (const GeometricTransform &lhs, const GeometricTransform &rhs);