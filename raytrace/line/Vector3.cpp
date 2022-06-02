#pragma once
#include "Vector3.hpp"
Vector3::Vector3() {};
Vector3::Vector3(double t_x, double t_y, double t_z): x(t_x), y(t_y), z(t_z) {}
double Vector3::getMagnitude() { return sqrt(x*x + y*y + z*z); };
Vector3 Vector3::getNormalized() {
    double mag = getMagnitude();
    if (mag == 0) return Vector3(0, 0, 0);
    double xOut = x == 0 ? x : x/mag;
    double yOut = y == 0 ? y : y/mag;
    double zOut = z == 0 ? z : z/mag;
    return Vector3(xOut, yOut, zOut);
};
void Vector3::normalize() {
    double mag = getMagnitude();
    if (mag == 0) return;
    x = x == 0 ? x : x/mag;
    y = y == 0 ? y : y/mag;
    z = z == 0 ? z : z/mag;
}
Vector3 Vector3::operator+ (const Vector3 &rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);};


Vector3 Vector3::operator+= (const double &rhs) { return Vector3(x + rhs, y + rhs, z + rhs);  };
Vector3 operator+ (const Vector3 &lhs, const double &rhs) { return Vector3(lhs) += rhs; };
Vector3 operator+ (const double &lhs, const Vector3 &rhs) { return Vector3(rhs) += lhs; };


Vector3 Vector3::operator-= (const double &rhs) { return Vector3(x - rhs, y - rhs, z - rhs);  };
Vector3 operator- (const Vector3 &lhs, const double &rhs) { return Vector3(lhs) -= rhs; };
Vector3 operator- (const double &lhs, const Vector3 &rhs) { return Vector3(rhs) -= lhs; };

Vector3 Vector3::operator- (const Vector3 &rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);};
Vector3 Vector3::operator*= (const double &rhs) { return Vector3(x * rhs, y * rhs, z * rhs);  }
Vector3 operator* (const Vector3 &lhs, const double &rhs) { return Vector3(lhs) *= rhs; };
Vector3 operator* (const double &lhs, const Vector3 &rhs) { return Vector3(rhs) *= lhs; };
Vector3 Vector3::operator*= (const Matrix4 &rhs) {
    Vector3 outVector {
        rhs.values[0][0] * x + rhs.values[1][0] * y + rhs.values[2][0] * z + rhs.values[3][0],
        rhs.values[0][1] * x + rhs.values[1][1] * y + rhs.values[2][1] * z + rhs.values[3][1],
        rhs.values[0][2] * x + rhs.values[1][2] * y + rhs.values[2][2] * z + rhs.values[3][2]
    };
    
    x = outVector.x;
    y = outVector.y;
    z = outVector.z;
    return *this;
};
Vector3 operator* (const Matrix4 &lhs, const Vector3 &rhs) { return Vector3(rhs) *= lhs; };
Vector3 operator* (const Vector3 &lhs, const Matrix4 &rhs) { return Vector3(lhs) *= rhs; };
double Vector3::dot(const Vector3 &a, const Vector3 &b) { 
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector3 Vector3::cross(const Vector3 &a, const Vector3 &b) { 
    return Vector3(
        a.y * b.z - a.z * b.y,
        -(a.x * b.z - a.y * b.x),
        a.x * b.y - a.y * b.x
    );
}

std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
    os << "x: " << vector.x << " y: " << vector.y << " z: " << vector.z;
    return os;
}