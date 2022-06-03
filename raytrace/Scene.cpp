#pragma once
#include "./Scene.hpp"
#include "Materials/SimpleMaterial.hpp"
#include "Objects/CylinderObject.hpp"
#include "Objects/ConeObject.hpp"
#include "Textures/FlatTexture.hpp"
#include "Textures/CheckerboardTexture.hpp"
qbRT::Scene::Scene() {
    //Create some materials
    //TODO: Created pointer without freeing it
    //TODO: Create constructors to avoid this hellscape
    auto firstTexture = new Texture::CheckerboardTexture();
    auto yellowDiffuse = new SimpleMaterial();
    yellowDiffuse->color = Vector3 { 0.8, 0.8, 0.3 };
    yellowDiffuse->reflectivity = 0.0;
    yellowDiffuse->shininess = 5.0;
    yellowDiffuse->addTexture(*firstTexture);
    auto blueDiffuse = new SimpleMaterial();
    blueDiffuse->color = Vector3 { 0.2, 0.2, 1.0 };
    blueDiffuse->reflectivity = 0.0;
    blueDiffuse->shininess = 5.0;
    blueDiffuse->addTexture(*firstTexture);
    //TODO allow classes to take advantage of the builder pattern
    auto floorMaterial = new SimpleMaterial();
    floorMaterial->color = Vector3 { 1.0, 1.0, 1.0 };
    floorMaterial->reflectivity = 0.5;
    floorMaterial->shininess = 0.0;
    floorMaterial->addTexture(*firstTexture);
    auto floor = new PlaneObject();
    floor->setTransformMatrix (
        GeometricTransform {
            Vector3 { 0.0, 0.0, 1.0},
            Vector3 { 0.0, 0.0, 0.0},
            Vector3 { 16.0, 16.0, 1.0 }
        }
    );
    floor->setMaterial(floorMaterial);
    objectList.push_back(floor);
    
    auto cylinder = new CylinderObject();
    cylinder->setTransformMatrix (
        GeometricTransform {
            Vector3 { -1.0, 0.0, 0.0},
            Vector3 { -M_PI/4.0, 0.0, 0.0},
            Vector3 { 0.5, 0.5, 1.0 }
        }
    );
    cylinder->setMaterial(blueDiffuse);
    objectList.push_back(cylinder);
    auto cone1 = new ConeObject();
    cone1->setTransformMatrix (
        GeometricTransform {
            Vector3 { 1.0, 0.0, 0.0},
            Vector3 { M_PI/4.0, 0.0, 0.0},
            Vector3 { 0.5, 0.5, 1.0 }
        }
    );
    cone1->setMaterial(yellowDiffuse);
    objectList.push_back(cone1);
    auto sphere = new SphereObject();
    sphere->setTransformMatrix (
        GeometricTransform {
            Vector3 { 0.0, 0.0, 0.0},
            Vector3 { M_PI/4.0, 0.0, 0.0},
            Vector3 { 1.0, 1.0, 1.0 }
        }
    );
    sphere->setMaterial(yellowDiffuse);
    objectList.push_back(sphere);
    //std::cout << cylinder->geometricTransform.getForwardMatrix();
    /*
    auto testMaterial = new SimpleMaterial();
    testMaterial->color = Vector3 { 0.25, 0.5, 0.8 };
    testMaterial->reflectivity = 0.1;
    testMaterial->shininess = 10.0;
    auto testMaterial2 = new SimpleMaterial();
    testMaterial2->color = Vector3 { 1.0, 0.5, 0.0 };
    testMaterial2->reflectivity = 0.75;
    testMaterial2->shininess = 10.0;
    auto testMaterial3 = new SimpleMaterial();
    testMaterial3->color = Vector3 { 1.0, 0.8, 0.0 };
    testMaterial3->reflectivity = 0.25;
    testMaterial3->shininess = 10.0;
    auto floorMaterial = new SimpleMaterial();
    floorMaterial->color = Vector3 { 1.0, 1.0, 1.0 };
    floorMaterial->reflectivity = 0.5;
    floorMaterial->shininess = 0.0;
	*/
    // Configure the camera.
	camera.setPositionVector  (Vector3{0.0, -10.0, -2.0});
	camera.setLookAtVector     (Vector3{0.0, 0.0, 0.0});
	camera.setUpVector	     (Vector3{0.0, 0.0, 1.0});
	camera.setWidth            (0.25);
	camera.setAspectRatio      (16.0 / 9.0);
	camera.updateCameraGeometry();
    // Make objects
    /*
    objectList.push_back(new SphereObject());
    objectList.push_back(new SphereObject());
    objectList.push_back(new SphereObject());
    // Create plane
    objectList.push_back(new PlaneObject());
    objectList.at(3)->baseColor = Vector3 { 0.5, 0.5, 0.5 };
    GeometricTransform planeMatrix;
    planeMatrix.setTransform(
        Vector3 { 0.0, 0.0, 0.75},
        Vector3 { 0.0, 0.0, 0.0},
        Vector3 { 4.0, 4.0, 1.0 }
    );
    objectList.at(3)->setTransformMatrix(planeMatrix);
    // modify spheres
    GeometricTransform testTransform1, testTransform2, testTransform3;
    testTransform1.setTransform(
        Vector3 { -1.5, 0.0, 0.0},
        Vector3 { 0.0, 0.0, 0.0},
        Vector3 { 0.5, 0.5, 0.5 }
    );
    testTransform2.setTransform(
        Vector3 { 0.0, 0.0, 0.0 },
        Vector3 { 0.0, 0.0, 0.0 },
        Vector3 { 0.5, 0.5, 0.5 }
    );
    testTransform3.setTransform(
        Vector3 { 1.5, 0.0, 0.0},
        Vector3 { 0.0, 0.0, 0.0},
        Vector3 { 0.5, 0.5, 0.5 }
    );
    objectList.at(0)->setTransformMatrix(testTransform1);
    objectList.at(1)->setTransformMatrix(testTransform2);
    objectList.at(2)->setTransformMatrix(testTransform3);

    objectList.at(0)->baseColor = Vector3 { 0.25, 0.5, 0.8 };
    objectList.at(1)->baseColor = Vector3 { 1.0, 0.5, 0.0 };
    objectList.at(2)->baseColor = Vector3 { 1.0, 0.8, 0.0 };
    //Assign materials
    objectList.at(0)->setMaterial(testMaterial3);
    objectList.at(1)->setMaterial(testMaterial);
    objectList.at(2)->setMaterial(testMaterial2);
    objectList.at(3)->setMaterial(floorMaterial);
    */
    // Make test light
    lightList.push_back(new PointLight());
    lightList.at(0)->positionVector = Vector3(5.0, -10.0, -5.0);
    lightList.at(0)->color = Vector3(0.0, 0.0, 1.0);
    lightList.push_back(new PointLight());
    lightList.at(1)->positionVector = Vector3(-5.0, -10.0, -5.0);
    lightList.at(1)->color = Vector3(1.0, 0.0, 0.0);
    lightList.push_back(new PointLight());
    lightList.at(2)->positionVector = Vector3(0.0, -10.0, -5.0);
    lightList.at(2)->color = Vector3(0.0, 1.0, 0.0);
    
};
void qbRT::Scene::update() {
    //camera.positionVector.x += 0.001;
}
bool qbRT::Scene::render(qbImage &outputImage) {
    int xSize = outputImage.getXSize();
    int ySize = outputImage.getYSize();
    double xFactor = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFactor = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    for (int x = 0; x < xSize; x++) {
        if (x % 150 == 0) std::cout << "drawing row " << x + 1 << " of " << xSize << "\n";
        for (int y = 0; y < ySize; y++) {
            qbRT::Ray cameraRay;
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
            BaseMaterial::maxReflectionCount = 3;
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
                    closestLocalNormal, cameraRay,
                    closestObject->baseColor
                );
                outputImage.setPixel(x, y, color.x, color.y, color.z);
            }
            BaseMaterial::reflectionCount = 0;
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
bool qbRT::Scene::castRay(
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