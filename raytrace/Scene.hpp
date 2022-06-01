#pragma once
#include <vector>
#include "../SDL2/SDL.h"
#include "./qbImage.hpp"
#include "Camera.hpp"
#include "Objects/SphereObject.hpp"
#include "Objects/PlaneObject.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/BaseMaterial.hpp"
namespace qbRT {
    class Scene {
    public:
        Scene();
        // TODO: Make standardize o_ meaning output and t_ meaning input
        bool castRay(
            Ray t_ray, 
            BaseObject* &o_closestObject,
            Vector3 &o_closestIntersectionPoint,
            Vector3 &o_closestNormal,
            Vector3 &o_closestColor
        );
        bool render(qbImage &outputImage);
        void update();
        qbRT::Camera camera;
        std::vector<BaseObject*> objectList;
        std::vector<BaseLight*> lightList;
    };
};