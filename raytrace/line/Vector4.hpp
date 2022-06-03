#pragma once
#include <iostream>
// TODO: create operator to take double and vector both
class Vector4 {
public:
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
    double w { 0.0 };
    Vector4();
    Vector4(double t_x, double t_y, double t_z, double t_w);
    // Define a constructor that takes a vector 3 and then a w value
    double getMagnitude();
    Vector4 getNormalized();
    void normalize();
    // 
    Vector4 operator+ (const Vector4 &rhs) const;
    Vector4 operator- (const Vector4 &rhs) const;
    Vector4 operator+= (const Vector4 &rhs);
    Vector4 operator-= (const Vector4 &rhs);
    //
    Vector4 operator+= (const double &rhs);
    Vector4 operator-= (const double &rhs);
    Vector4 operator*= (const double &rhs);
    //
    static double dot(const Vector4 &a, const Vector4 &b);
    static Vector4 cross(const Vector4 &a, const Vector4 &b);
    
    friend std::ostream& operator<<(std::ostream& os, const Vector4& vector);
};
Vector4 operator+ (const Vector4 &lhs, const double &rhs);
Vector4 operator+ (const double &lhs, const Vector4 &rhs);
Vector4 operator- (const Vector4 &lhs, const double &rhs);
Vector4 operator- (const double &lhs, const Vector4 &rhs);
Vector4 operator* (const Vector4 &lhs, const double &rhs);
Vector4 operator* (const double &lhs, const Vector4 &rhs);