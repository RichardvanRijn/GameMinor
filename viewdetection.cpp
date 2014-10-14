#include "viewdetection.h"

ViewDetection::ViewDetection(Ogre::SceneManager* manager, gkVector3 origin, gkVector3 direction) :
	viewManager(manager)
{
	detection = new Ogre::Ray(origin, direction);
}

ViewDetection::~ViewDetection()
{
	delete detection;
}

void ViewDetection::setViewDistance(float maxDistance) {
	viewDistance = maxDistance;
}

void ViewDetection::setExcludedObjects(const char* *objectNames) {

}

std::pair<DetectionResult, DetectionIterator&> ViewDetection::detectObjects() {
	//Ogre::ResourceGroupManager::getSingletonPtr();
	//Ogre::OverlayManager* mg = Ogre::OverlayManager::getSingletonPtr();
	//Ogre::Overlay* ov = mg->getByName("TestScriptOverlay");

	Ogre::RaySceneQuery* rayQuery = viewManager->createRayQuery(*detection);
	rayQuery->setSortByDistance(true);

	DetectionResult result = rayQuery->execute();
	DetectionIterator& endOfResult = filterObjects(result);

	return std::make_pair(result, endOfResult);
}

//extra comment

DetectionIterator& ViewDetection::filterObjects(DetectionResult& result) {	
	return result.begin();
	//return(std::remove_if(result.begin(), result.end(), positionedInDistance));
}

bool ViewDetection::positionedInDistance(Ogre::RaySceneQueryResultEntry& object) const {
	return(object.distance != 0 && object.distance <= viewDistance);
}
