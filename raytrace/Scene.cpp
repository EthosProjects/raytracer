#pragma once
#include "./Scene.hpp"
qbRT::Scene::Scene() {
	// Configure the camera.
	camera.setPositionVector  (Vector3{0.0, -10.0,  -1.0});
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
    objectList.at(3)->baseColor = Vector3 { 128.0, 128.0, 128.0 };
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

    objectList.at(0)->baseColor = Vector3 { 64.0, 128.0, 200.0 };
    objectList.at(1)->baseColor = Vector3 { 255.0, 128.0, 0.0 };
    objectList.at(2)->baseColor = Vector3 { 255.0, 255.0, 0.0 };
    // Make test light
    lightList.push_back(new PointLight());
    lightList.at(0)->positionVector = Vector3(5.0, -10.0, -5.0);
    lightList.at(0)->color = Vector3(255.0, 255.0, 255.0);
};
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
            for (auto currentObject: objectList) {
                bool validIntersection = currentObject->testForIntersections(
                    cameraRay,
                    intersectionPoint,
                    localNormal,
                    localColor
                );
                if (validIntersection) {
                    double intensity;
                    Vector3 color;
                    bool validIllumination;
                    for (auto currentLight: lightList) {
                        validIllumination = currentLight->computeIllumination(
                            intersectionPoint,
                            localNormal,
                            objectList,
                            currentObject,
                            color,
                            intensity
                        );
                    }
                    double dist = (intersectionPoint - cameraRay.aVector).getMagnitude();
                    if (validIllumination) {
                        outputImage.setPixel(x, y, 
                            localColor.x * intensity,
                            localColor.y * intensity, 
                            localColor.z * intensity
                        );
                    }
                    /*outputImage.setPixel(x, y, 
                        0.0, 
                        0.0, 
                        255.0 - (dist - 9.0) / 0.94605 * 255.0
                    );*/
                } 
            }
        }
    }
    return true;
}