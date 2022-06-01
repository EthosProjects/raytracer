#pragma once
#include <iostream>

class Matrix4 {
public:
    //The values
    double values[4][4] { 0.0 };
    void setToIdentity();
    bool toInverse();

    double getDeterminant();
    bool operator== (const Matrix4& rhs);
    Matrix4 operator*= (const Matrix4 &rhs);
    Matrix4 operator*= (const double &rhs);
};
Matrix4 operator* (const Matrix4 &lhs, const Matrix4 &rhs);
Matrix4 operator* (const Matrix4 &lhs, const double &rhs);
Matrix4 operator* (const double &lhs, const Matrix4 &rhs);
std::ostream& operator<<(std::ostream& os, const Matrix4& matrix4);