#pragma once
#include "BaseTexture.hpp"
Texture::BaseTexture::BaseTexture() {
    transformMatrix.setToIdentity();
};
Vector4 Texture::BaseTexture::getColor(const Vector3 &t_UVCoordinates) const {
    Vector4 outputColor;

    return outputColor;
}
void Texture::BaseTexture::setTransform (const Vector3 &translation, const double &rotation, const Vector3 &scale) {
    //Define a matrix for each part of the transform
    Matrix4 translationMatrix;
    Matrix4 rotationMatrix;
    Matrix4 scaleMatrix;
    //Set to identity
    translationMatrix.setToIdentity();
    rotationMatrix.setToIdentity();
    scaleMatrix.setToIdentity();
    //Populate matrixes
    //Starting with the translation matrix
    translationMatrix.values[2][0] = translation.x;
    translationMatrix.values[2][1] = translation.y;
    //Next is rotation
    rotationMatrix.values[0][0] = cos(rotation);
    rotationMatrix.values[1][0] = -sin(rotation);
    rotationMatrix.values[0][1] = sin(rotation);
    rotationMatrix.values[1][1] = cos(rotation);
    // Last is scalar
    scaleMatrix.values[0][0] = scale.x;
    scaleMatrix.values[1][1] = scale.y;
    // Combine
    transformMatrix = 
        translationMatrix * 
        rotationMatrix *
        scaleMatrix;
};
Vector3 Texture::BaseTexture::blendColors (const std::vector<Vector4> t_colorList) {
    Vector3 outputColor;

    return outputColor;
};
Vector3 Texture::BaseTexture::applyTransform(const Vector3 &t_vector) const {
    Vector3 copiedVecor = t_vector;
    return transformMatrix * t_vector;
};