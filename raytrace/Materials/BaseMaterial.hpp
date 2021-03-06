#pragma once
#include "../Textures/BaseTexture.hpp"
#include "../Objects/BaseObject.hpp"
#include "../Lights/BaseLight.hpp"
#include "../line/Vector3.hpp"
#include "../Ray.hpp"

class BaseMaterial {
public:
    virtual Vector3 computeColor(
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        const BaseObject* t_closestObject,
        const Vector3 &t_closestIntersectionPoint,
        const Vector3 &t_closestLocalNormal, 
        const qbRT::Ray t_cameraRay
    );
    static Vector3 computeDiffuseColor(
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        const BaseObject* t_closestObject,
        const Vector3 &t_closestIntersectionPoint,
        const Vector3 &t_closestLocalNormal, 
        const qbRT::Ray t_cameraRay,
        //TODO: local refers to coordinates. It is redundant for colors
        const Vector3 &t_localColor
    );
    virtual Vector3 computeReflectionColor(
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        const BaseObject* t_closestObject,
        const Vector3 &t_closestIntersectionPoint,
        const Vector3 &t_closestLocalNormal, 
        const qbRT::Ray t_incidentRay
    );
    bool castRay (
        const qbRT::Ray t_ray,
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        const BaseObject* &t_object,
        BaseObject* &o_closestObject,
        Vector3 &o_closestIntersectionPoint,
        Vector3 &o_closestLocalNormal,
        Vector3 &o_closestLocalColor
    );
    // variables for reflections
    inline static int maxReflectionCount;
    inline static int reflectionCount;


    //TODO: verify this requires a function 
    //TODO: determine a method to make the input const but still get the color later
    // This will likely require making the getColor function const as well so that I can call
    // it on const instances of the texture class 
    void addTexture (Texture::BaseTexture &t_texture);

    // List of textures assigned to this material
    std::vector<const Texture::BaseTexture*> textureList;
    //Flag to indicate that at least one texture is assigned
    bool hasTexture { false };
};