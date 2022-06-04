#pragma once
#include "GeometricTransform.hpp"
GeometricTransform::GeometricTransform() {
    forwardTransform.setToIdentity();
    backwardTransform.setToIdentity();
};
GeometricTransform::GeometricTransform(const Matrix4 &fwd, const Matrix4 &bck):
    forwardTransform(fwd), backwardTransform(bck) {
};
GeometricTransform::GeometricTransform(const Vector3 &translation, const Vector3 &rotation, const Vector3 &scale) {
    //Define a matrix for each part of the transform
    Matrix4 translationMatrix;
    Matrix4 rotationXMatrix;
    Matrix4 rotationYMatrix;
    Matrix4 rotationZMatrix;
    Matrix4 scaleMatrix;
    //Set to identity
    translationMatrix.setToIdentity();
    rotationXMatrix.setToIdentity();
    rotationYMatrix.setToIdentity();
    rotationZMatrix.setToIdentity();
    scaleMatrix.setToIdentity();
    //Populate matrixes
    //Starting with the translation matrix
    translationMatrix.values[3][0] = translation.x;
    translationMatrix.values[3][1] = translation.y;
    translationMatrix.values[3][2] = translation.z;
    //Next is rotation
    rotationZMatrix.values[0][0] = cos(rotation.z);
    rotationZMatrix.values[1][0] = -sin(rotation.z);
    rotationZMatrix.values[0][1] = sin(rotation.z);
    rotationZMatrix.values[1][1] = cos(rotation.z);
    
    rotationYMatrix.values[0][0] = cos(rotation.y);
    rotationYMatrix.values[2][0] = sin(rotation.y);
    rotationYMatrix.values[0][2] = -sin(rotation.y);
    rotationYMatrix.values[2][2] = cos(rotation.y);
    
    rotationXMatrix.values[1][1] = cos(rotation.x);
    rotationXMatrix.values[2][1] = -sin(rotation.x);
    rotationXMatrix.values[1][2] = sin(rotation.x);
    rotationXMatrix.values[2][2] = cos(rotation.x);
    // Last is scalar
    scaleMatrix.values[0][0] = scale.x;
    scaleMatrix.values[1][1] = scale.y;
    scaleMatrix.values[2][2] = scale.z;
    // Combine
    forwardTransform = 
        translationMatrix * 
        rotationXMatrix * 
        rotationYMatrix * 
        rotationZMatrix *
        scaleMatrix;
    backwardTransform = forwardTransform;
    backwardTransform.toInverse();
};
void GeometricTransform::setTransform(const Vector3 &translation, const Vector3 &rotation, const Vector3 &scale) {
    //Define a matrix for each part of the transform
    Matrix4 translationMatrix;
    Matrix4 rotationXMatrix;
    Matrix4 rotationYMatrix;
    Matrix4 rotationZMatrix;
    Matrix4 scaleMatrix;
    //Set to identity
    translationMatrix.setToIdentity();
    rotationXMatrix.setToIdentity();
    rotationYMatrix.setToIdentity();
    rotationZMatrix.setToIdentity();
    scaleMatrix.setToIdentity();
    //Populate matrixes
    //Starting with the translation matrix
    translationMatrix.values[3][0] = translation.x;
    translationMatrix.values[3][1] = translation.y;
    translationMatrix.values[3][2] = translation.z;
    //Next is rotation
    rotationZMatrix.values[0][0] = cos(rotation.z);
    rotationZMatrix.values[1][0] = -sin(rotation.z);
    rotationZMatrix.values[0][1] = sin(rotation.z);
    rotationZMatrix.values[1][1] = cos(rotation.z);
    
    rotationYMatrix.values[0][0] = cos(rotation.y);
    rotationYMatrix.values[2][0] = sin(rotation.y);
    rotationYMatrix.values[0][2] = -sin(rotation.y);
    rotationYMatrix.values[2][2] = cos(rotation.y);
    
    rotationXMatrix.values[1][1] = cos(rotation.x);
    rotationXMatrix.values[2][1] = -sin(rotation.x);
    rotationXMatrix.values[1][2] = sin(rotation.x);
    rotationXMatrix.values[2][2] = cos(rotation.x);
    // Last is scalar
    scaleMatrix.values[0][0] = scale.x;
    scaleMatrix.values[1][1] = scale.y;
    scaleMatrix.values[2][2] = scale.z;
    // Combine
    forwardTransform = 
        translationMatrix * 
        rotationXMatrix * 
        rotationYMatrix * 
        rotationZMatrix *
        scaleMatrix;
    backwardTransform = forwardTransform;
    backwardTransform.toInverse();
};
Matrix4 GeometricTransform::getForwardMatrix() const { return forwardTransform; };
Matrix4 GeometricTransform::getBackwardMatrix() const { return backwardTransform; };

Ray GeometricTransform::apply (const Ray &inputRay, bool directionFlag) const {
    Ray outputRay;
    outputRay.aVector = apply(inputRay.aVector, directionFlag);
    outputRay.bVector = apply(inputRay.bVector, directionFlag);
    outputRay.labVector = outputRay.bVector - outputRay.aVector;
    return outputRay;
}
Vector3 GeometricTransform::apply (const Vector3 &inputVector, bool directionFlag) const {
    if (directionFlag) return forwardTransform * inputVector;
    else return backwardTransform * inputVector;
}
GeometricTransform GeometricTransform::operator= (const GeometricTransform &rhs) {
    if (this == &rhs) return *this;
    forwardTransform = rhs.forwardTransform;
    backwardTransform = rhs.backwardTransform;
    return *this;
}
GeometricTransform GeometricTransform::operator*= (const GeometricTransform &rhs) {
    forwardTransform *= rhs.forwardTransform;
    backwardTransform = forwardTransform;
    backwardTransform.toInverse();
    return *this;
};
GeometricTransform operator* (const GeometricTransform &lhs, const GeometricTransform &rhs) { 
    return GeometricTransform(lhs.forwardTransform, lhs.backwardTransform) *= rhs;
}