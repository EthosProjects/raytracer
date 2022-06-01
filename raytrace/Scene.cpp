#pragma once
#include "./Scene.hpp"
qbRT::Scene::Scene() {
	// Configure the camera.
	camera.setPositionVector  (Vector3{0.0, -10.0, -1.0});
	camera.setLookAtVector     (Vector3{0.0, 0.0, 0.0});
	camera.setUpVector	     (Vector3{0.0, 0.0, 1.0});
	camera.setWidth            (0.25);
	camera.setAspectRatio      (16.0 / 9.0);
	camera.updateCameraGeometry();
    // Make objects
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
        Vector3 { 0.5, 0.5, 0.75 }
    );
    testTransform2.setTransform(
        Vector3 { 0.0, 0.0, 0.0 },
        Vector3 { 0.0, 0.0, 0.0 },
        Vector3 { 0.75, 0.5, 0.5 }
    );
    testTransform3.setTransform(
        Vector3 { 1.5, 0.0, 0.0},
        Vector3 { 0.0, 0.0, 0.0},
        Vector3 { 0.75, 0.75, 0.75 }
    );
    objectList.at(0)->setTransformMatrix(testTransform1);
    objectList.at(1)->setTransformMatrix(testTransform2);
    objectList.at(2)->setTransformMatrix(testTransform3);

    objectList.at(0)->baseColor = Vector3 { 0.25, 0.5, 0.8 };
    objectList.at(1)->baseColor = Vector3 { 1.0, 0.5, 0.0 };
    objectList.at(2)->baseColor = Vector3 { 1.0, 0.8, 0.0 };
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
    camera.positionVector.x += 0.001;
}
bool qbRT::Scene::render(qbImage &outputImage) {
    int xSize = outputImage.getXSize();
    int ySize = outputImage.getYSize();

    qbRT::Ray cameraRay;
    Vector3 intersectionPoint;
    Vector3 localNormal;
    Vector3 localColor;
    double xFactor = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFactor = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            double normX = (static_cast<double>(x) * xFactor) - 1.0;
            double normY = (static_cast<double>(y) * yFactor) - 1.0;
            camera.generateRay(normX, normY, cameraRay);
            BaseObject* closestObject;
            Vector3 closestIntersectionPoint;
            Vector3 closestLocalNormal;
            Vector3 closestLocalColor;
            double minimumDistance = 1e6;
            bool intersectionFound = false;
            for (auto currentObject: objectList) {
                bool validIntersection = currentObject->testForIntersections(
                    cameraRay,
                    intersectionPoint,
                    localNormal,
                    localColor
                );
                if (!validIntersection) continue;
                intersectionFound = true;
                double dist = (intersectionPoint - cameraRay.aVector).getMagnitude();
                if (dist < minimumDistance) {
                    minimumDistance = dist;
                    closestObject = currentObject;
                    closestIntersectionPoint = intersectionPoint;
                    closestLocalColor = localColor;
                    closestLocalNormal = localNormal;
                }
            }
            if (!intersectionFound) continue;
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
            );
        }
    }
    return true;
}