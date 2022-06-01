#pragma once
#include <vector>
#include "../SDL2/SDL.h"
#include "./qbImage.hpp"
#include "Camera.hpp"
#include "SphereObject.hpp"
#include "PlaneObject.hpp"
#include "PointLight.hpp"
namespace qbRT {
    class Scene {
    public:
        Scene();
        bool render(qbImage &outputImage);
        void update();
        qbRT::Camera camera;
        std::vector<BaseObject*> objectList;
        std::vector<BaseLight*> lightList;
    };
};