#pragma once
#include "FlatTexture.hpp"
Texture::FlatTexture::FlatTexture() {
    color = Vector4 { 1.0, 0.0, 0.0, 1.0 };
};
Vector4 Texture::FlatTexture::getColor(const Vector3 &t_UVCoordinates) const {
    return color;
}
void Texture::FlatTexture::setColor(const Vector4 &t_color) {
    color = t_color;
};