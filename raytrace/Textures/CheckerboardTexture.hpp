#pragma once
#include "BaseTexture.hpp"
namespace Texture {
    class CheckerboardTexture : public BaseTexture {
    public:
        CheckerboardTexture();
        Vector4 getColor (const Vector3 &UVCoordinate) const override;
        void setColor (const Vector4 &t_color1, const Vector4 &t_color2);
    private: 
        Vector4 color1;
        Vector4 color2;
    };
};