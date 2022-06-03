#pragma once
#include "BaseTexture.hpp"
namespace Texture {
    class FlatTexture : public BaseTexture {
    public:
        FlatTexture();
        Vector4 getColor(const Vector3 &t_UVCoordiantes) const override;
        void setColor (const Vector4 &t_color);
    private:
        Vector4 color;
    };
};