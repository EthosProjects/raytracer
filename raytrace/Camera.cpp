#pragma once
#include "Camera.hpp"
qbRT::Camera::Camera(): 
    positionVector(0.0, -10, 0.0),
    lookAtVector(0.0, 0.0, 0.0),
    upVector(0.0, 0.0, 1.0),
    length(1.0),
    width(1.0),
    aspectRatio(1.0) {};
// Setters
// Vector setters
void qbRT::Camera::setPositionVector(const Vector3 &newPositionVector) { positionVector = newPositionVector; }
void qbRT::Camera::setLookAtVector(const Vector3 &newLookAtVector) { lookAtVector = newLookAtVector; }
void qbRT::Camera::setUpVector(const Vector3 &newUpVector) { upVector = newUpVector; }
// double setters
void qbRT::Camera::setLength(double newLength) { length = newLength; }
void qbRT::Camera::setWidth(double newWidth) { width = newWidth; }
void qbRT::Camera::setAspectRatio(double newAspectRatio) { aspectRatio = newAspectRatio; }
// Getters
// Vector getters
Vector3 qbRT::Camera::getPositionVector() { return positionVector; }
Vector3 qbRT::Camera::getLookAtVector() { return lookAtVector; }
Vector3 qbRT::Camera::getUpVector() { return upVector; }
// double getters
double qbRT::Camera::getLength() { return length; }
double qbRT::Camera::getWidth() { return width; }
double qbRT::Camera::getAspectRatio(){ return aspectRatio; }
// Calculated getters
Vector3 qbRT::Camera::getUVector() { return UVector; }
Vector3 qbRT::Camera::getVVector() { return VVector; }
Vector3 qbRT::Camera::getProjectionScreenCenterVector() { return projectionScreenCenterVector; }
// Geoemtry calculator
// Utility functions
void qbRT::Camera::updateCameraGeometry() {
	// First, compute the vector from the camera position to the LookAt position.
	alignmentVector = lookAtVector - positionVector;
	alignmentVector.normalize();
	// Second, compute the U and V vectors.
	UVector = Vector3::cross(alignmentVector, upVector);
	UVector.normalize();
	VVector = Vector3::cross(UVector, alignmentVector);
	VVector.normalize();
	// Thirdly, compute the positon of the centre point of the screen.
	projectionScreenCenterVector = positionVector + (alignmentVector * length);
	// Modify the U and V vectors to match the size and aspect ratio.
	UVector = UVector * width;
	VVector = VVector * (width / aspectRatio);
}
bool qbRT::Camera::generateRay(float projectionScreenX, float projectionScreenY, qbRT::Ray &cameraRay) {
	// Compute the location of the screen point in world coordinates.
	Vector3 screenWorldPart1 = projectionScreenCenterVector + (UVector * projectionScreenX);
	Vector3 screenWorldCoordinate = screenWorldPart1 + (VVector * projectionScreenY);
	
	// Use this point along with the camera position to compute the ray.
	cameraRay.aVector = positionVector;
	cameraRay.bVector = screenWorldCoordinate;
	cameraRay.labVector = screenWorldCoordinate - positionVector;
	
	return true;
}
/**
 * 
 *
void qbRT::Camera::updateGeometry() {
    //First compute the vector form the position to the lookAt vector
    alignmentVector = (lookAt - position).getNormalized();
    //Second compute the U and V vectors
    U = Vector3::cross(alignmentVector, Up).getNormalized();
    V = Vector3::cross(U, alignmentVector).getNormalized();
    //Thirdly, compute center
    screenCenter = position + (alignmentVector * length);
    //Lastly modify U and V to match screen
    U = U * horizontalSize;
    V = V * (horizontalSize/aspectRatio);
};  
bool qbRT::Camera::generateRay(float projectionScreenX, float projectionScreenY, qbRT::Ray &cameraRay) {
    Vector3 screenWorldPartial = screenCenter + (U * projectionScreenX);
    Vector3 screenWorldFinal = screenWorldPartial + (V * projectionScreenY);
    cameraRay.a = position;
    cameraRay.b = screenWorldFinal;
    cameraRay.lab = screenWorldFinal - position; 
    return true;
}
*/