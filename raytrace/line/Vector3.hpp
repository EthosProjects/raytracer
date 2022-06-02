#pragma once
#include <math.h>
#include <iostream>
#include "Matrix4.hpp"
// TODO: create operator to take double and vector both
class Vector3 {
public:
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
    Vector3();
    Vector3(double t_x, double t_y, double t_z);
    double getMagnitude();
    Vector3 getNormalized();
    void normalize();
    Vector3 operator+ (const Vector3 &rhs) const;
    Vector3 operator- (const Vector3 &rhs) const;
    Vector3 operator+= (const double &rhs);
    Vector3 operator+= (const Vector3 &rhs);
    Vector3 operator-= (const double &rhs);
    Vector3 operator-= (const Vector3 &rhs);
    Vector3 operator*= (const Matrix4 &rhs);
    Vector3 operator*= (const double &rhs);

    static double dot(const Vector3 &a, const Vector3 &b);
    static Vector3 cross(const Vector3 &a, const Vector3 &b);
    
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);
};
Vector3 operator+ (const Vector3 &lhs, const double &rhs);
Vector3 operator+ (const double &lhs, const Vector3 &rhs);
Vector3 operator- (const Vector3 &lhs, const double &rhs);
Vector3 operator- (const double &lhs, const Vector3 &rhs);
//Vector3 operator* (const Vector3 &lhs, const Vector3 &rhs);
Vector3 operator* (const Vector3 &lhs, const double &rhs);
Vector3 operator* (const double &lhs, const Vector3 &rhs);
Vector3 operator* (const Matrix4 &lhs, const Vector3 &rhs);
Vector3 operator* (const Vector3 &lhs, const Matrix4 &rhs);