#pragma once
#include "../Ray.hpp"
#include "../line/Vector4.hpp"
#include <vector>
namespace Texture {
    class BaseTexture {
    public:
        BaseTexture();
        // Note that color is returned as a Vector4
        virtual Vector4 getColor (const Vector3 &UVCoordinate) const;
        static Vector3 blendColors (const std::vector<Vector4> t_colorList);
        void setTransform (const Vector3 &translation, const double &rotation, const Vector3 &scale);
        // idk why use this and not just apply the transform directly ngl
        Vector3 applyTransform(const Vector3 &t_Vector) const;
    private:
    Matrix4 transformMatrix;
    };
};