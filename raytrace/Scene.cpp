#pragma once
#include "./Scene.hpp"
#include "Materials/SimpleMaterial.hpp"
#include "Materials/RefractiveMaterial.hpp"
#include "Objects/CylinderObject.hpp"
#include "Objects/ConeObject.hpp"
#include "Textures/FlatTexture.hpp"
#include "Textures/CheckerboardTexture.hpp"
Scene::Scene() {
	camera.setPositionVector  (Vector3{2.0, -5.0, -0.25});
	camera.setLookAtVector     (Vector3{0.0, 0.0, 0.0});
	camera.setUpVector	     (Vector3{0.0, 0.0, 1.0});
	camera.setWidth            (1.00);
	camera.setAspectRatio      (16.0 / 9.0);
	camera.updateCameraGeometry();
    //Create some materials
    //TODO: Created pointer without freeing it
    //TODO: Create constructors to avoid this hellscape
    auto firstTexture = new Texture::CheckerboardTexture();
    auto floorTexture = new Texture::CheckerboardTexture();
    floorTexture -> setTransform(
        Vector3 { 0.0, 0.0, 0.0},
        0.0,
        Vector3{ 16.0, 16.0, 1.0} 
    );
    // **************************************************************************************
	// Create some materials.
	// **************************************************************************************
	auto floorMaterial = new SimpleMaterial();
	auto imageMaterial = new SimpleMaterial();
	auto sphereMaterial = new SimpleMaterial();
	auto sphereMaterial2 = new SimpleMaterial();
	auto sphereMaterial3 = new SimpleMaterial();
	auto glassMaterial = new SimpleRefractiveMaterial();
// **************************************************************************************	
	// Setup the materials.
	// **************************************************************************************
	floorMaterial -> color = Vector3{ 1.0, 1.0, 1.0 };
	floorMaterial -> reflectivity = 0.25;
	floorMaterial -> shininess = 0.0;
	floorMaterial -> setTexture(floorTexture);
	
	imageMaterial -> color = Vector3 { 1.0, 0.125, 0.125 };
	imageMaterial -> reflectivity = 0.0;
	imageMaterial -> shininess = 0.0;
	
	sphereMaterial -> color = Vector3{ 1.0, 0.2, 0.2 };
	sphereMaterial -> reflectivity = 0.8;
	sphereMaterial -> shininess = 32.0;
	
	sphereMaterial2 -> color = Vector3{0.2, 1.0, 0.2};
	sphereMaterial2 -> reflectivity = 0.8;
	sphereMaterial2 -> shininess = 32.0;
	
	sphereMaterial3 -> color = Vector3{0.2, 0.2, 1.0};
	sphereMaterial3 -> reflectivity = 0.8;
	sphereMaterial3 -> shininess = 32.0;	
	
	glassMaterial -> color = Vector3{0.7, 0.7, 0.2};
	glassMaterial -> reflectivity = 0.25;
	glassMaterial -> shininess = 32.0;
	glassMaterial -> transluncy = 0.75;
	glassMaterial -> refractiveIndex = 1.333;	
    // **************************************************************************************	
	// Create and setup objects.
	// **************************************************************************************
	auto floor =  new PlaneObject();
	floor -> setTransformMatrix(GeometricTransform {	Vector3{0.0, 0.0, 1.0},
                                                Vector3{0.0, 0.0, 0.0},
                                                Vector3{16.0, 16.0, 1.0} 
    });
	floor -> setMaterial(floorMaterial);

	// **************************************************************************************
	auto imagePlane = new PlaneObject();
	imagePlane -> setTransformMatrix(GeometricTransform {	Vector3{0.0, 5.0, -0.75},
                                                    Vector3{-M_PI/2.0, 0.0, 0.0},
                                                    Vector3{1.75, 1.75, 1.0}}	);
	imagePlane -> setMaterial(imageMaterial);

	// **************************************************************************************	
	auto sphere = new SphereObject();
	sphere -> setTransformMatrix(GeometricTransform	{	Vector3{-2.0, -2.0, 0.25},
                                                    Vector3{0.0, 0.0, 0.0},
                                                    Vector3{0.75, 0.75, 0.75}});
	sphere -> setMaterial(sphereMaterial);
	
	// **************************************************************************************	
	auto sphere2 =  new SphereObject();
	sphere2 -> setTransformMatrix(GeometricTransform	{	Vector3{-2.0, -0.5, 0.25},
                                                    Vector3{0.0, 0.0, 0.0},
                                                    Vector3{0.75, 0.75, 0.75} });
	sphere2 -> setMaterial(sphereMaterial2);
	
	// **************************************************************************************	
	auto sphere3 = new SphereObject();
	sphere3 -> setTransformMatrix(GeometricTransform	{	Vector3{-2.0, -1.25, -1.0},
                                                    Vector3{0.0, 0.0, 0.0},
                                                    Vector3{0.75, 0.75, 0.75}	});
	sphere3 -> setMaterial(sphereMaterial3);		
	
	// **************************************************************************************	
	auto sphere4 = new SphereObject();
	sphere4 -> setTransformMatrix(GeometricTransform	{	Vector3{2.0, -1.25, 0.25},
                                                    Vector3{0.0, 0.0, 0.0},
                                                    Vector3{0.75, 0.75, 0.75} });
	sphere4 -> setMaterial(glassMaterial);		

	// **************************************************************************************
	// Put the objects into the scene.	
	// **************************************************************************************
	objectList.push_back(floor);
	objectList.push_back(imagePlane);
	objectList.push_back(sphere);
	objectList.push_back(sphere2);	
	objectList.push_back(sphere3);	
	objectList.push_back(sphere4);
	
	lightList.push_back(new PointLight());
	lightList.at(0) -> positionVector = Vector3 {3.0, -10.0, -5.0};
	lightList.at(0) -> color = Vector3 { 1.0, 1.0, 1.0 };
	lightList.at(0) -> intensity = 4.0;
	
	lightList.push_back(new PointLight());
	lightList.at(1) -> positionVector = Vector3 {0.0, -10.0, -5.0};
	lightList.at(1) -> color = Vector3 {1.0, 1.0, 1.0};
	lightList.at(1) -> intensity = 2.0;
    lightList.push_back(new PointLight());
};
void Scene::update() {
    //camera.positionVector.x += 0.001;
}
bool Scene::render(qbImage &outputImage) {
    int xSize = outputImage.getXSize();
    int ySize = outputImage.getYSize();
    double xFactor = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFactor = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    for (int x = 0; x < xSize; x++) {
        if (x % 150 == 0) std::cout << "drawing row " << x + 1 << " of " << xSize << "\n";
        for (int y = 0; y < ySize; y++) {
            Ray cameraRay;
            double normX = (static_cast<double>(x) * xFactor) - 1.0;
            double normY = (static_cast<double>(y) * yFactor) - 1.0;
            camera.generateRay(normX, normY, cameraRay);
            BaseObject* closestObject;
            Vector3 closestIntersectionPoint;
            Vector3 closestLocalNormal;
            Vector3 closestLocalColor;
            bool intersectionFound = castRay (
                cameraRay,
                closestObject,
                closestIntersectionPoint,
                closestLocalNormal,
                closestLocalColor
            );
            //TODO All transformed vectors will be prefaced with local valid
            if (!intersectionFound) continue;
            BaseMaterial::maxReflectionRays = 3;
            SimpleRefractiveMaterial::castat = 0;
            if (closestObject->hasMaterial()) {
                Vector3 color = closestObject->p_material->computeColor(
                    objectList,
                    lightList,
                    closestObject,
                    closestIntersectionPoint, 
                    closestLocalNormal, cameraRay
                );
                outputImage.setPixel(x, y, color.x, color.y, color.z);
            } else {
                Vector3 color = BaseMaterial::computeDiffuseColor(
                    objectList,
                    lightList,
                    closestObject,
                    closestIntersectionPoint,
                    closestLocalNormal,
                    closestObject->baseColor
                );
                outputImage.setPixel(x, y, color.x, color.y, color.z);
            }
            BaseMaterial::currentReflectionRay = 0;
            /*
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            bool illuminationFound = false;
            for (auto currentLight: lightList) {
                double intensity { 1.0 };
                Vector3 color;
                if (!currentLight->computeIllumination(
                    closestIntersectionPoint,
                    closestLocalNormal,
                    objectList,
                    closestObject,
                    color,
                    intensity
                )) continue;
                illuminationFound = true;
                red += color.x * intensity;
                green += color.y * intensity;
                blue += color.z * intensity;
            }
            if (!illuminationFound) continue; 
            outputImage.setPixel(x, y, 
                closestLocalColor.x * red,
                closestLocalColor.y * green, 
                closestLocalColor.z * blue
            );*/
        }
    }
    return true;
}
bool Scene::castRay(
    Ray t_ray, 
    BaseObject* &o_closestObject,
    Vector3 &o_closestIntersectionPoint,
    Vector3 &o_closestNormal,
    Vector3 &o_closestColor
) {
    double minimumDistance = 1e6;
    bool intersectionFound = false;
    for (auto currentObject: objectList) {
        Vector3 intersectionPoint;
        Vector3 localNormal;
        Vector3 localColor;
        bool validIntersection = currentObject->testForIntersections(
            t_ray,
            intersectionPoint,
            localNormal,
            localColor
        );
        if (!validIntersection) continue;
        intersectionFound = true;
        double dist = (intersectionPoint - t_ray.aVector).getMagnitude();
        if (dist < minimumDistance) {
            minimumDistance = dist;
            o_closestObject = currentObject;
            o_closestIntersectionPoint = intersectionPoint;
            o_closestNormal = localNormal;
            o_closestColor = localColor;
        }
    }
    return intersectionFound;
};