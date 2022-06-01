#pragma once
#include "Matrix4.hpp"

void Matrix4::setToIdentity() {
    values[0][0] = 1.0;
    values[0][1] = 0.0;
    values[0][2] = 0.0;
    values[0][3] = 0.0;

    values[1][0] = 0.0;
    values[1][1] = 1.0;
    values[1][2] = 0.0;
    values[1][3] = 0.0;
    
    values[2][0] = 0.0;
    values[2][1] = 0.0;
    values[2][2] = 1.0;
    values[2][3] = 0.0;
    
    values[3][0] = 0.0;
    values[3][1] = 0.0;
    values[3][2] = 0.0;
    values[3][3] = 1.0;
}
bool Matrix4::toInverse () {
    double determinant = getDeterminant();
    if (determinant == 0) return false;
    Matrix4 temp = *this;
    values[0][0] = (
        temp.values[1][1] * temp.values[2][2] * temp.values[3][3] +
        temp.values[2][1] * temp.values[3][2] * temp.values[1][3] +
        temp.values[3][1] * temp.values[1][2] * temp.values[2][3] -
        
        temp.values[3][1] * temp.values[2][2] * temp.values[1][3] -
        temp.values[2][1] * temp.values[1][2] * temp.values[3][3] -
        temp.values[1][1] * temp.values[3][2] * temp.values[2][3]) / determinant;
    values[1][0] = (
        - temp.values[1][0] * temp.values[2][2] * temp.values[3][3] -
        temp.values[2][0] * temp.values[3][2] * temp.values[1][3] -
        temp.values[3][0] * temp.values[1][2] * temp.values[2][3] +
        
        temp.values[3][0] * temp.values[2][2] * temp.values[1][3] +
        temp.values[2][0] * temp.values[1][2] * temp.values[3][3] +
        temp.values[1][0] * temp.values[3][2] * temp.values[2][3]
    )/determinant;
    values[2][0] = (
        temp.values[1][0] * temp.values[2][1] * temp.values[3][3] +
        temp.values[2][0] * temp.values[3][1] * temp.values[1][3] +
        temp.values[3][0] * temp.values[1][1] * temp.values[2][3] -
        
        temp.values[3][0] * temp.values[2][1] * temp.values[1][3] -
        temp.values[2][0] * temp.values[1][1] * temp.values[3][3] -
        temp.values[1][0] * temp.values[3][1] * temp.values[2][3]
    )/determinant;
    values[3][0] = (
        - temp.values[1][0] * temp.values[2][1] * temp.values[3][2] -
        temp.values[2][0] * temp.values[3][1] * temp.values[1][2] -
        temp.values[3][0] * temp.values[1][1] * temp.values[2][2] +
        
        temp.values[3][0] * temp.values[2][1] * temp.values[1][2] +
        temp.values[2][0] * temp.values[1][1] * temp.values[3][2] +
        temp.values[1][0] * temp.values[3][1] * temp.values[2][2]
    )/determinant;

    //Change all 1s to 0s
    values[0][1] = (
        - temp.values[0][1] * temp.values[2][2] * temp.values[3][3] -
        temp.values[2][1] * temp.values[3][2] * temp.values[0][3] -
        temp.values[3][1] * temp.values[0][2] * temp.values[2][3] +
        
        temp.values[3][1] * temp.values[2][2] * temp.values[0][3] +
        temp.values[2][1] * temp.values[0][2] * temp.values[3][3] +
        temp.values[0][1] * temp.values[3][2] * temp.values[2][3]) / determinant;
    values[1][1] = (
        temp.values[0][0] * temp.values[2][2] * temp.values[3][3] +
        temp.values[2][0] * temp.values[3][2] * temp.values[0][3] +
        temp.values[3][0] * temp.values[0][2] * temp.values[2][3] -
        
        temp.values[3][0] * temp.values[2][2] * temp.values[0][3] -
        temp.values[2][0] * temp.values[0][2] * temp.values[3][3] -
        temp.values[0][0] * temp.values[3][2] * temp.values[2][3]
    )/determinant;
    values[2][1] = (
        - temp.values[0][0] * temp.values[2][1] * temp.values[3][3] -
        temp.values[2][0] * temp.values[3][1] * temp.values[0][3] -
        temp.values[3][0] * temp.values[0][1] * temp.values[2][3] +
        
        temp.values[3][0] * temp.values[2][1] * temp.values[0][3] +
        temp.values[2][0] * temp.values[0][1] * temp.values[3][3] +
        temp.values[0][0] * temp.values[3][1] * temp.values[2][3]
    )/determinant;
    values[3][1] = (
        temp.values[0][0] * temp.values[2][1] * temp.values[3][2] +
        temp.values[2][0] * temp.values[3][1] * temp.values[0][2] +
        temp.values[3][0] * temp.values[0][1] * temp.values[2][2] -
        
        temp.values[3][0] * temp.values[2][1] * temp.values[0][2] -
        temp.values[2][0] * temp.values[0][1] * temp.values[3][2] -
        temp.values[0][0] * temp.values[3][1] * temp.values[2][2]
    )/determinant;
    //Change all 2s to 1s
    values[0][2] = (
        temp.values[0][1] * temp.values[1][2] * temp.values[3][3] +
        temp.values[1][1] * temp.values[3][2] * temp.values[0][3] +
        temp.values[3][1] * temp.values[0][2] * temp.values[1][3] +
        
        temp.values[3][1] * temp.values[1][2] * temp.values[0][3] -
        temp.values[1][1] * temp.values[0][2] * temp.values[3][3] -
        temp.values[0][1] * temp.values[3][2] * temp.values[1][3]) / determinant;
    values[1][2] = (
        - temp.values[0][0] * temp.values[1][2] * temp.values[3][3] -
        temp.values[1][0] * temp.values[3][2] * temp.values[0][3] -
        temp.values[3][0] * temp.values[0][2] * temp.values[1][3] +
        
        temp.values[3][0] * temp.values[1][2] * temp.values[0][3] +
        temp.values[1][0] * temp.values[0][2] * temp.values[3][3] +
        temp.values[0][0] * temp.values[3][2] * temp.values[1][3]
    )/determinant;
    values[2][2] = (
        temp.values[0][0] * temp.values[1][1] * temp.values[3][3] +
        temp.values[1][0] * temp.values[3][1] * temp.values[0][3] +
        temp.values[3][0] * temp.values[0][1] * temp.values[1][3] -
        
        temp.values[3][0] * temp.values[1][1] * temp.values[0][3] -
        temp.values[1][0] * temp.values[0][1] * temp.values[3][3] -
        temp.values[0][0] * temp.values[3][1] * temp.values[1][3]
    )/determinant;
    values[3][2] = (
        - temp.values[0][0] * temp.values[1][1] * temp.values[3][2] -
        temp.values[1][0] * temp.values[3][1] * temp.values[0][2] -
        temp.values[3][0] * temp.values[0][1] * temp.values[1][2] +
        
        temp.values[3][0] * temp.values[1][1] * temp.values[0][2] +
        temp.values[1][0] * temp.values[0][1] * temp.values[3][2] +
        temp.values[0][0] * temp.values[3][1] * temp.values[1][2]
    )/determinant;
    //Change all 3s to 2s
    values[0][3] = (
        temp.values[0][1] * temp.values[1][2] * temp.values[2][3] +
        temp.values[1][1] * temp.values[2][2] * temp.values[0][3] +
        temp.values[2][1] * temp.values[0][2] * temp.values[1][3] -
        
        temp.values[2][1] * temp.values[1][2] * temp.values[0][3] -
        temp.values[1][1] * temp.values[0][2] * temp.values[2][3] -
        temp.values[0][1] * temp.values[2][2] * temp.values[1][3]) / determinant;
    values[1][3] = (
        temp.values[0][0] * temp.values[1][2] * temp.values[2][3] +
        temp.values[1][0] * temp.values[2][2] * temp.values[0][3] +
        temp.values[2][0] * temp.values[0][2] * temp.values[1][3] -
        
        temp.values[2][0] * temp.values[1][2] * temp.values[0][3] -
        temp.values[1][0] * temp.values[0][2] * temp.values[2][3] -
        temp.values[0][0] * temp.values[2][2] * temp.values[1][3]
    )/determinant;
    values[2][3] = (
        - temp.values[0][0] * temp.values[1][1] * temp.values[2][3] -
        temp.values[1][0] * temp.values[2][1] * temp.values[0][3] -
        temp.values[2][0] * temp.values[0][1] * temp.values[1][3] +
        
        temp.values[2][0] * temp.values[1][1] * temp.values[0][3] +
        temp.values[1][0] * temp.values[0][1] * temp.values[2][3] +
        temp.values[0][0] * temp.values[2][1] * temp.values[1][3]
    )/determinant;
    values[3][3] = (
        temp.values[0][0] * temp.values[1][1] * temp.values[2][2] +
        temp.values[1][0] * temp.values[3][1] * temp.values[0][2] +
        temp.values[2][0] * temp.values[0][1] * temp.values[1][2] -
        
        temp.values[2][0] * temp.values[1][1] * temp.values[0][2] -
        temp.values[1][0] * temp.values[0][1] * temp.values[2][2] -
        temp.values[0][0] * temp.values[2][1] * temp.values[1][2]
    )/determinant;
    return true;
}
double Matrix4::getDeterminant() {
    return values[0][0] * (
        values[1][1] * values[2][2] * values[3][3] +
        values[2][1] * values[3][2] * values[1][3] +
        values[3][1] * values[1][2] * values[2][3] -
        
        values[3][1] * values[2][2] * values[1][3] -
        values[2][1] * values[1][2] * values[3][3] -
        values[1][1] * values[3][2] * values[2][3]
    ) - values[0][1] * (
        values[1][0] * values[2][2] * values[3][3] +
        values[2][0] * values[3][2] * values[1][3] +
        values[3][0] * values[1][2] * values[2][3] -
        
        values[3][0] * values[2][2] * values[1][3] -
        values[2][0] * values[1][2] * values[3][3] -
        values[1][0] * values[3][2] * values[2][3]
    ) + values[0][2] * (
        values[1][0] * values[2][1] * values[3][3] +
        values[2][0] * values[3][1] * values[1][3] +
        values[3][0] * values[1][1] * values[2][3] -
        
        values[3][0] * values[2][1] * values[1][3] -
        values[2][0] * values[1][1] * values[3][3] -
        values[1][0] * values[3][1] * values[2][3]
    ) - values[0][3] * (
        values[1][0] * values[2][1] * values[3][2] +
        values[2][0] * values[3][1] * values[1][2] +
        values[3][0] * values[1][1] * values[2][2] -
        
        values[3][0] * values[2][1] * values[1][2] -
        values[2][0] * values[1][1] * values[3][2] -
        values[1][0] * values[3][1] * values[2][2]
    ) ;
}
bool Matrix4::operator== (const Matrix4 &rhs) {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j ++) if (values[i][j] != rhs.values[i][j]) return false;
    return true;
}
Matrix4 Matrix4::operator*= (const Matrix4 &rhs) {
    Matrix4 temp = Matrix4(*this);
    values[0][0] = temp.values[0][0] * rhs.values[0][0] + temp.values[1][0] * rhs.values[0][1] + temp.values[2][0] * rhs.values[0][2] + temp.values[3][0] * rhs.values[0][3];
    values[0][1] = temp.values[0][1] * rhs.values[0][0] + temp.values[1][1] * rhs.values[0][1] + temp.values[2][1] * rhs.values[0][2] + temp.values[3][1] * rhs.values[0][3];
    values[0][2] = temp.values[0][2] * rhs.values[0][0] + temp.values[1][2] * rhs.values[0][1] + temp.values[2][2] * rhs.values[0][2] + temp.values[3][2] * rhs.values[0][3];
    values[0][3] = temp.values[0][3] * rhs.values[0][0] + temp.values[1][3] * rhs.values[0][1] + temp.values[2][3] * rhs.values[0][2] + temp.values[3][3] * rhs.values[0][3];

    values[1][0] = temp.values[0][0] * rhs.values[1][0] + temp.values[1][0] * rhs.values[1][1] + temp.values[2][0] * rhs.values[1][2] + temp.values[3][0] * rhs.values[1][3];
    values[1][1] = temp.values[0][1] * rhs.values[1][0] + temp.values[1][1] * rhs.values[1][1] + temp.values[2][1] * rhs.values[1][2] + temp.values[3][1] * rhs.values[1][3];
    values[1][2] = temp.values[0][2] * rhs.values[1][0] + temp.values[1][2] * rhs.values[1][1] + temp.values[2][2] * rhs.values[1][2] + temp.values[3][2] * rhs.values[1][3];
    values[1][3] = temp.values[0][3] * rhs.values[1][0] + temp.values[1][3] * rhs.values[1][1] + temp.values[2][3] * rhs.values[1][2] + temp.values[3][3] * rhs.values[1][3];

    values[2][0] = temp.values[0][0] * rhs.values[2][0] + temp.values[1][0] * rhs.values[2][1] + temp.values[2][0] * rhs.values[2][2] + temp.values[3][0] * rhs.values[2][3];
    values[2][1] = temp.values[0][1] * rhs.values[2][0] + temp.values[1][1] * rhs.values[2][1] + temp.values[2][1] * rhs.values[2][2] + temp.values[3][1] * rhs.values[2][3];
    values[2][2] = temp.values[0][2] * rhs.values[2][0] + temp.values[1][2] * rhs.values[2][1] + temp.values[2][2] * rhs.values[2][2] + temp.values[3][2] * rhs.values[2][3];
    values[2][3] = temp.values[0][3] * rhs.values[2][0] + temp.values[1][3] * rhs.values[2][1] + temp.values[2][3] * rhs.values[2][2] + temp.values[3][3] * rhs.values[2][3];

    values[3][0] = temp.values[0][0] * rhs.values[3][0] + temp.values[1][0] * rhs.values[3][1] + temp.values[2][0] * rhs.values[3][2] + temp.values[3][0] * rhs.values[3][3];
    values[3][1] = temp.values[0][1] * rhs.values[3][0] + temp.values[1][1] * rhs.values[3][1] + temp.values[2][1] * rhs.values[3][2] + temp.values[3][1] * rhs.values[3][3];
    values[3][2] = temp.values[0][2] * rhs.values[3][0] + temp.values[1][2] * rhs.values[3][1] + temp.values[2][2] * rhs.values[3][2] + temp.values[3][2] * rhs.values[3][3];
    values[3][3] = temp.values[0][3] * rhs.values[3][0] + temp.values[1][3] * rhs.values[3][1] + temp.values[2][3] * rhs.values[3][2] + temp.values[3][3] * rhs.values[3][3];
    return *this;
};
Matrix4 Matrix4::operator*= (const double &rhs) {
    for (int i = 0; i < 4; i++) {
        values[i][0] *= rhs;
        values[i][1] *= rhs;
        values[i][2] *= rhs;
        values[i][3] *= rhs;
    };
    return *this;
};
Matrix4 operator* (const Matrix4 &lhs, const Matrix4 &rhs) { return Matrix4(lhs) *= rhs; }
Matrix4 operator* (const Matrix4 &lhs, const double &rhs) { return Matrix4(lhs) *= rhs; }
Matrix4 operator* (const double &lhs, const Matrix4 &rhs) { return Matrix4(rhs) *= lhs; }
std::ostream& operator<<(std::ostream& os, const Matrix4& matrix4) {
    os << "[ " << matrix4.values[0][0] << ", " << matrix4.values[1][0] << ", " << matrix4.values[2][0] << ", " << matrix4.values[3][0] << ",\n  "
               << matrix4.values[0][1] << ", " << matrix4.values[1][1] << ", " << matrix4.values[2][1] << ", " << matrix4.values[3][1] << ",\n  "
               << matrix4.values[0][2] << ", " << matrix4.values[1][2] << ", " << matrix4.values[2][2] << ", " << matrix4.values[3][2] << ",\n  "
               << matrix4.values[0][3] << ", " << matrix4.values[1][3] << ", " << matrix4.values[2][3] << ", " << matrix4.values[3][3] << " ]";
    return os;
}