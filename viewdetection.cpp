#include "viewdetection.h"

ViewDetection::ViewDetection(Ogre::SceneManager* manager, gkVector3 origin, gkVector3 direction) :
	viewManager(manager),
	detectedObjects(DetectionResult())
{
	detection = new Ogre::Ray(origin, direction);
}

ViewDetection::~ViewDetection()
{
	delete detection;

	for (auto iterator = detectedObjects.begin(); iterator != detectedObjects.end(); ++iterator)
		delete &iterator;
}

void ViewDetection::setViewDistance(float maxDistance) {
	viewDistance = maxDistance;
}

void ViewDetection::addExcludedObject(const char *objectName) {
	excludedObjects.push_back(objectName);
}

void ViewDetection::detectObjects() {
	//Ogre::ResourceGroupManager::getSingletonPtr();
	//Ogre::OverlayManager* mg = Ogre::OverlayManager::getSingletonPtr();
	//Ogre::Overlay* ov = mg->getByName("TestScriptOverlay");

	Ogre::RaySceneQuery* rayQuery = viewManager->createRayQuery(*detection);
	rayQuery->setSortByDistance(true);

	DetectionResult& result = rayQuery->execute();
	DetectionIterator& endOfResult = filterObjects(result);

	result.erase(endOfResult, result.end() - 1);
	detectedObjects = result;
}

DetectionResult& ViewDetection::getDetectedObjects() const {
	return detectedObjects;
}

DetectionIterator& ViewDetection::filterObjects(DetectionResult& result) {	
	DetectionIterator& endOfResult = std::remove_if(result.begin(), result.end(), std::bind1st(std::mem_fun(&ViewDetection::isInvalidObject), this));
	
	return endOfResult;
}

bool ViewDetection::objectsSpotted() const {
	return(detectedObjects.size() != 0);
}

bool ViewDetection::isInvalidObject(DetectedObject object) const {
	return(!positionedInDistance(object) && isExcludedObject(object));
}

bool ViewDetection::positionedInDistance(DetectedObject object) const {
	return(object.distance != 0 && object.distance <= viewDistance);
}

bool ViewDetection::isExcludedObject(DetectedObject object) const {
	return(std::find(excludedObjects.begin(), excludedObjects.end(), object.movable->getName().c_str()) != excludedObjects.end());
}
