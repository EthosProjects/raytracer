#pragma once
#include "CheckerboardTexture.hpp"
Texture::CheckerboardTexture::CheckerboardTexture() {
    color1 = Vector4 { 1.0, 1.0, 1.0, 1.0 };
    color2 = Vector4 { 0.2, 0.2, 0.2, 1.0 };
};
Vector4 Texture::CheckerboardTexture::getColor(const Vector3 &t_UVCoordinates) const {
    Vector3 copiedCoordinates = t_UVCoordinates;
    Vector3 transformedCoordinates = applyTransform(copiedCoordinates);
    int check = floor(transformedCoordinates.x) + floor(transformedCoordinates.y);
    if (check % 2 == 0) return color1;
    else return color2;
}
void Texture::CheckerboardTexture::setColor(const Vector4 &t_color1, const Vector4 &t_color2) {
    color1 = t_color1;
    color2 = t_color2;
};