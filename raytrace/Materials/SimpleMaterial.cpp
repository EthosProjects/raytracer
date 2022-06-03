#pragma once
#include "SimpleMaterial.hpp"
Vector3 SimpleMaterial::computeColor (
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    const BaseObject* t_closestObject,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const qbRT::Ray t_cameraRay
) {
    // Define initial material colors
    Vector3 materialColor;
    Vector3 reflectionColor;
    Vector3 diffuseColor;
    Vector3 specularColor;
    //Compute diffuse color
    if (!hasTexture) {
      diffuseColor = computeDiffuseColor(
            t_objectList,
            t_lightList,
            t_closestObject,
            t_closestIntersectionPoint,
            t_closestLocalNormal,
            t_cameraRay,
            color
        );
    } else {
        Vector4 color4 = textureList.at(0)->getColor(t_closestObject->UVCoordinates);
        diffuseColor = computeDiffuseColor(
            t_objectList,
            t_lightList,
            t_closestObject,
            t_closestIntersectionPoint,
            t_closestLocalNormal,
            t_cameraRay,
            Vector3 { color4.x, color4.y, color4.z }
        );
    }
    //Compute shininess
    if (shininess > 0.0) {
        specularColor = computeSpecularColor(
            t_objectList,
            t_lightList,
            t_closestIntersectionPoint,
            t_closestLocalNormal,
            t_cameraRay
        );
    }
    // Compute the reflection
    if (reflectivity > 0.0) {
        reflectionColor = computeReflectionColor (
            t_objectList,
            t_lightList,
            t_closestObject,
            t_closestIntersectionPoint,
            t_closestLocalNormal,
            t_cameraRay
        );
    }
    diffuseColor = reflectionColor * reflectivity + diffuseColor * (1 - reflectivity);
    return diffuseColor + specularColor;
};
Vector3 SimpleMaterial::computeSpecularColor (
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const qbRT::Ray t_cameraRay
) {
    Vector3 specularColor;
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    for (auto currentLight : t_lightList) {
        //Check for intersections with all lights in the scene except current one
        double intensity = 0.0;
        //Construct a ray pointing from the intersection  to the light
        Vector3 lightDirection = (currentLight->positionVector - t_closestIntersectionPoint).getNormalized();
        //Compute a start point
        Vector3 startPoint = t_closestIntersectionPoint + 0.0001 * lightDirection;
        //Construct a ray from the point of intersection+
        qbRT::Ray lightRay { startPoint, startPoint + lightDirection };
        //Loop through all objects in scene
       
       //TODO: Notice that this function is the same as the shadow function. I'm just making sure no object obstructs the thing

        Vector3 poi;
        Vector3 poiNormal;
        Vector3 poiColor;
        bool validIntersection = false;
        for ( auto currentObject : t_objectList ) {
            validIntersection = currentObject->testForIntersections(
                lightRay,
                poi,
                poiNormal,
                poiColor
            );
            if (validIntersection) break;
        }
        if (validIntersection) continue;
        //if (validIntersection) break;
        //Compute the reflectionvector
        Vector3 d = lightRay.labVector;
        // TODO: Notice we are computing potentially expensive expression twice
        Vector3 reflectionVector = d - (2.0 * Vector3::dot(d, t_closestLocalNormal) * t_closestLocalNormal);
        reflectionVector.normalize();
        //Compute the dot product
        Vector3 v = t_cameraRay.labVector;
        v.normalize();
        double dotProduct = Vector3::dot(reflectionVector, v);
        // Onyl proceed if the dot product is positive
        if (dotProduct > 0.0) {
            intensity = reflectivity * std::pow(dotProduct, shininess);
        }
        red += currentLight->color.x * intensity;
        green += currentLight->color.y * intensity;
        blue += currentLight->color.z * intensity;
    };
    specularColor.x = red;
    specularColor.y = green;
    specularColor.z = blue;
    return specularColor;
}
