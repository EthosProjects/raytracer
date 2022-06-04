#pragma once
#include "../Textures/BaseTexture.hpp"
#include "../Objects/BaseObject.hpp"
#include "../Lights/BaseLight.hpp"
#include "../line/Vector3.hpp"
#include "../Ray.hpp"

class BaseMaterial {
public:
//    BaseMaterial();
    // Function to return the color of the material.
    virtual Vector3 computeColor(
        const std::vector<BaseObject*> &t_objectList,
        const std::vector<BaseLight*> &t_lightList,
        BaseObject* &t_currentObject,
        const Vector3 &t_intersectionPoint,
        const Vector3 &t_localNormal,
        const Ray &cameraRay
    );
    // Function to compute diffuse color.
    static Vector3 computeDiffuseColor(	
        const std::vector<BaseObject*> &objectList,
        const std::vector<BaseLight*> &lightList,
        BaseObject* &currentObject,
        const Vector3 &intPoint, 
        const Vector3 &localNormal,
        //TODO: local refers to coordinates. It is redundant for colors
        const Vector3 &baseColor
    );                                  
    // Function to compute the reflection color.
    Vector3 computeReflectionColor(
        const std::vector<BaseObject*> &objectList,
        const std::vector<BaseLight*> &lightList,
        BaseObject* &currentObject,
        const Vector3 &intPoint,
        const Vector3 &localNormal,
        const Ray &incidentRay
    );                            
    // Function to cast a ray into the scene.
    bool castRay(
        const Ray &t_castRay, 
        const std::vector<BaseObject*> &t_objectList,
        BaseObject* &t_currentObject,
        BaseObject* &o_closestObject,
        Vector3 &o_closestIntPoint, 
        Vector3 &o_closestLocalNormal,
        Vector3 &o_closestLocalColor
    );
                
    // Function to assign a texture.

    //TODO: determine a method to make the input const but still get the color later
    // This will likely require making the getColor function const as well so that I can call
    // it on const instances of the texture class 
    void setTexture(Texture::BaseTexture* t_texture);
                                
    // Counter for the number of relection rays.
    inline static int maxReflectionRays;
    inline static int currentReflectionRay;
    
    // The ambient lighting conditions.
    inline static Vector3 ambientColor { 1.0, 1.0, 1.0 };
    inline static double ambientIntensity = 0.2;
    
    // List of texures assigned to this material.
    std::vector<Texture::BaseTexture*> textureList;
    
    // Flat to indicate whether at least one texture has been assigned.
    bool hasTexture = false;
};