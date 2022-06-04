#pragma once
#include "RefractiveMaterial.hpp"

Vector3 SimpleRefractiveMaterial::computeColor (
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    BaseObject* &t_closestObject,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const Ray &t_cameraRay
) {
    //if (castat == 1) std::cout << "yeah\n";
    if (castat == 1) return Vector3 {};
    castat = 1;
    // Define initial material colors
    Vector3 materialColor;
    Vector3 reflectionColor;
    Vector3 diffuseColor;
    Vector3 specularColor;
    Vector3 translucentColor;
    //Compute diffuse color
    //NOTE: the way that this functions, if there is a material with a texture then
    //color picking is processed by the texture and then evyrthing else is cutely handled
    //by the material
    if (!hasTexture) {
      diffuseColor = computeDiffuseColor(
            t_objectList,
            t_lightList,
            t_closestObject,
            t_closestIntersectionPoint,
            t_closestLocalNormal,
            color
        );
    } else {
        Vector4 color4 = textureList.at(0)->getColor(
            t_closestObject->getUVCoordinates(
                t_closestObject->geometricTransform.apply(t_closestIntersectionPoint, false)
            ));
        diffuseColor = computeDiffuseColor(
            t_objectList,
            t_lightList,
            t_closestObject,
            t_closestIntersectionPoint,
            t_closestLocalNormal,
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
    // NOTE: lighting does not pass through translucent objects in current setup
    // Compute the refractive component
    if (transluncy > 0.0) {
        translucentColor = computeTranslucencyColor (
            t_objectList,
            t_lightList,
            t_closestObject,
            t_closestIntersectionPoint,
            t_closestLocalNormal,
            t_cameraRay
        );
    };
    diffuseColor = reflectionColor * reflectivity + diffuseColor * (1 - reflectivity);
    diffuseColor = translucentColor * transluncy + diffuseColor * (1 - transluncy);
    return diffuseColor + specularColor;
};
Vector3 SimpleRefractiveMaterial::computeSpecularColor (
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const Ray &t_cameraRay
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
        Ray lightRay { startPoint, startPoint + lightDirection };
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
// TODO: implement true translucence, where light rays can pass through translucent objects
// I should implement an object that functions as both a light and a plane. I could calculate the 
// Plane's diffuse color to by default be equal to the lighting of whatever light itself. I've
// considered the possibility of having a light inside a fully translucent
Vector3 SimpleRefractiveMaterial::computeTranslucencyColor (
    const std::vector<BaseObject*> &t_objectList,
    const std::vector<BaseLight*> &t_lightList,
    BaseObject* &t_closestObject,
    const Vector3 &t_closestIntersectionPoint,
    const Vector3 &t_closestLocalNormal, 
    const Ray &t_incidentRay
) {
    BaseObject* closestObject { nullptr };
    Vector3 closestIntersectionPoint;
    Vector3 closestLocalNormal;
    Vector3 closestColor;

    
    Vector3 vhat = t_incidentRay.labVector.getNormalized();
    Vector3 temporaryNormal = t_closestLocalNormal;
    double r = 1.0/refractiveIndex;
    double c = -Vector3::dot(temporaryNormal, vhat);
    if (c < 0.0) {
        temporaryNormal *= -1;
        c = -Vector3::dot(temporaryNormal, vhat);
    }
    Vector3 refractedVector = r * vhat + (r * c - sqrtf(1.0 - (r * r) * (1 - c * c))) * temporaryNormal;
    Ray refractedRay = { 
        t_closestIntersectionPoint + refractedVector * 0.1, 
        t_closestIntersectionPoint + refractedVector
    };
    Vector3 newIntersectionPoint;
    Vector3 newLocalNormal;
    Vector3 newColor;
    bool test = t_closestObject->testForIntersections(
        refractedRay,
        newIntersectionPoint,
        newLocalNormal,
        newColor
    );
    bool intersectionFound = false;
    Ray finalRay;
    if (test) {
        // Compute the refracted vector.
        Vector3 p2 = refractedRay.labVector;
        p2.normalize();
        Vector3 tempNormal2 = newLocalNormal;
        double r2 = refractiveIndex;
        double c2 = -Vector3::dot(tempNormal2, p2);
		if (c2 < 0.0) {
			tempNormal2 = tempNormal2 * -1.0;
            c2 = -Vector3::dot(tempNormal2, p2);
		}
        Vector3 refractedVector2 = r2*p2 + (r2*c2 - sqrtf(1.0-pow(r2,2.0) * (1.0-pow(c2,2.0)))) * tempNormal2;
		//Vector3 refractedVector2 = r * vhat + (r * c - sqrtf(1.0 - (r * r) * (1 - c * c))) * newLocalNormal;
        Ray refractedRay2 = {
            newIntersectionPoint + refractedVector2 * 0.01, 
            newIntersectionPoint + refractedVector2
        };
        intersectionFound = castRay(
            refractedRay2,
            t_objectList,
            t_closestObject,
            closestObject,
            closestIntersectionPoint,
            closestLocalNormal,
            closestColor
        );
        finalRay = refractedRay2;
    } else {
        intersectionFound = castRay(
            refractedRay,
            t_objectList,
            t_closestObject,
            closestObject,
            closestIntersectionPoint,
            closestLocalNormal,
            closestColor
        );
        finalRay = refractedRay;
    }
    // Color 
    if (intersectionFound) {
        if (closestObject->hasMaterial()) {
            // Using material
            return closestObject->p_material->computeColor(
                t_objectList,
                t_lightList,
                closestObject,
                closestIntersectionPoint,
                closestLocalNormal,
                finalRay
            );
        
        } else {
            return computeDiffuseColor(
                t_objectList,
                t_lightList,
                closestObject,
                closestIntersectionPoint,
                closestLocalNormal,
                closestObject->baseColor
            );
        }
    }
    return Vector3 {};
/*
    Vector3 translucencyColor;
    Vector3 p = t_incidentRay.labVector;
    p.normalize();
    Vector3 temporaryNormal = t_closestLocalNormal;
    double r = 1.0/(refractiveIndex);
    double c = -Vector3::dot(temporaryNormal, p);
    if (c < 0.0) {
        temporaryNormal *= -1;
        c = -Vector3::dot(temporaryNormal, p);
    }
    Vector3 refractedVector = r * p + (r * c - sqrtf(1.0 - (r * r) * (1 - c * c))) * temporaryNormal;
    Ray refractedRay { 
        t_closestIntersectionPoint + refractedVector * 0.001, 
        refractedVector
    };
    BaseObject* closestObject { nullptr };
    Vector3 closestIntersectionPoint;
    Vector3 closestLocalNormal;
    Vector3 closestColor;
    Vector3 newIntersectionPoint;
    Vector3 newLocalNormal;
    Vector3 newColor;
    bool test = t_closestObject->testForIntersections(
        refractedRay,
        newIntersectionPoint,
        newLocalNormal,
        newColor
    );
    bool intersectionFound { false };
    Ray finalRay;
    if (test) {
        Vector3 p2 = refractedRay.labVector;
        p2.normalize();
        Vector3 temporaryNormal2 = newLocalNormal;
        double r2 = refractiveIndex;
        double c2 = -Vector3::dot(temporaryNormal2, p2);
        if (c2 < 0.0) {
            temporaryNormal2 *= -1;
            c2 = -Vector3::dot(temporaryNormal2, p2);
        };
        Vector3 refractedVector2 = r2 * p2 + (r2 * c2 - sqrtf(1.0 - (r2 * r2) * (1 - c2 * c2))) * temporaryNormal;
        Ray refractedRay2  {
            newIntersectionPoint + refractedVector2 * 0.001,
            refractedVector2
        };
        intersectionFound = castRay(
            refractedRay2,
            t_objectList,
            t_lightList,
            t_closestObject,
            closestObject,
            closestIntersectionPoint,
            closestLocalNormal,
            closestColor
        );
        finalRay = refractedRay2;
    } else {
        intersectionFound = castRay(
            refractedRay,
            t_objectList,
            t_lightList,
            t_closestObject,
            closestObject,
            closestIntersectionPoint,
            closestLocalNormal,
            closestColor
        );
        finalRay = refractedRay;
    }
    
   
    Vector3 materialColor;
    if (intersectionFound) {
        if (closestObject->hasMaterial()) {
            // Using material
            materialColor = closestObject->p_material->computeColor(
                t_objectList,
                t_lightList,
                closestObject,
                closestIntersectionPoint,
                closestLocalNormal,
                finalRay
            );
        
        } else {
            materialColor = computeDiffuseColor(
                t_objectList,
                t_lightList,
                closestObject,
                closestIntersectionPoint,
                closestLocalNormal,
                finalRay,
                closestObject->baseColor
            );
        }
    }
    return materialColor;*/
}